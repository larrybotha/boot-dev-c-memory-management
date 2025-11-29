# Stack Overflow Investigation Findings

## The Mystery

The code in `main.c` allocates 10 MB on the stack, which should cause a stack overflow and segmentation fault. However, when compiled with `zig cc` (as used in the justfile), the program runs successfully without crashing.

## Initial Validation

The first step was to verify that a segmentation fault was actually occurring when using the system compiler:

### Check Stack Size Limit

```bash
$ ulimit -s
8176  # ~8 MB soft limit
```

### Compile and Run with GCC

```bash
$ gcc -o ./tmp/main main.c && ./tmp/main
# (No output - program crashes silently)

$ echo $?
139  # Exit code 139 = segmentation fault (128 + SIGSEGV signal 11)
```

**Conclusion**: The program crashes with a segfault when compiled with gcc, but not with zig

## Root Cause

The behavior difference is due to **stack overflow checking** and **macOS stack limits**.

### Stack Limits on macOS

```bash
$ ulimit -s    # Soft limit
8176           # ~8 MB

$ ulimit -Hs   # Hard limit
65520          # ~64 MB
```

macOS allows the stack to **grow dynamically** from the soft limit up to the hard limit.

### Compiler Differences

| Compiler                        | Version | Stack Checking                | Limit Enforced     | Result with 10 MB      |
| ------------------------------- | ------- | ----------------------------- | ------------------ | ---------------------- |
| **Apple Clang** (`gcc`/`clang`) | 17.0.0  | ✓ Includes `___chkstk_darwin` | Soft limit (8 MB)  | **Crashes** (exit 139) |
| **Homebrew Clang** (`zig cc`)   | 20.1.8  | ✗ No stack checking           | Hard limit (64 MB) | **Runs successfully**  |

## Technical Details

### Generating Assembly Output

To understand the difference in behavior, assembly files were generated using the `-S` flag:

```bash
# Generate assembly from both compilers
$ clang -S main.c -o main_apple.s
$ zig cc -S main.c -o main_zig.s

# Compare assembly file sizes
$ wc -l main_apple.s main_zig.s
      81 main_apple.s
    1010 main_zig.s
    1091 total
```

The Zig/Homebrew Clang output is **12x larger** (1010 vs 81 lines), indicating significant differences in code generation.

**Key commands for assembly analysis:**

```bash
# Search for stack checking function
$ grep "chkstk" main_apple.s
adrp    x16, ___chkstk_darwin@GOTPAGE
ldr     x16, [x16, ___chkstk_darwin@GOTPAGEOFF]

$ grep "chkstk" main_zig.s
# (No results - no stack checking)

# Search for the allocation size (10485760 = 0xa00000)
$ grep -A5 -B5 "0xa00000" main_apple.s
```

### Apple Clang Assembly

```assembly
adrp    x16, ___chkstk_darwin@GOTPAGE
ldr     x16, [x16, ___chkstk_darwin@GOTPAGEOFF]
blr     x16                              ; Check stack before allocation
sub     sp, sp, #2560, lsl #12           ; Allocate 10 MB
```

The `___chkstk_darwin` function checks if there's enough stack space against the **soft limit** (8 MB) and triggers a segfault if exceeded.

### Zig CC (Homebrew Clang) Assembly

```assembly
subs    x8, x8, #2560, lsl #12           ; Allocate 10 MB directly
mov     sp, x8
```

No stack checking - just allocates the memory. macOS allows the stack to grow from 8 MB to 10 MB because it's within the **hard limit** (64 MB).

## Test Results

### 10 MB Allocation (Between Soft and Hard Limits)

```bash
# Apple Clang
$ gcc main.c -o ./tmp/main_gcc && ./tmp/main_gcc
Exit code: 139  # Segmentation fault

# Zig CC
$ zig cc main.c -o ./tmp/main_zig && ./tmp/main_zig
Size of pool: 10485760
Initial string: snek
Exit code: 0  # Success
```

### 70 MB Allocation (Exceeds Hard Limit)

```bash
# Even Zig CC crashes
$ zig cc test_huge.c -o ./tmp/test_huge && ./test_huge
Exit code: 139  # Segmentation fault
```

## Why Zig doesn't segfault at 10Mb

The 10 MB stack allocation in `main.c` runs successfully because:

1. `zig cc` doesn't include stack overflow checking
2. 10 MB is within the hard limit (64 MB)
3. macOS dynamically grows the stack from 8 MB → 10 MB

## Solutions to See the Crash

- Use System Compiler

  ```justfile
  build in out deps="":
      gcc {{ in }} {{ deps }} -o {{ out }}
  ```

- Allocate Beyond Hard Limit

  ```c
  const int pool_size = 1024 * 1024 * 70;  // 70 MB
  ```

- Reduce Stack Soft Limit

  ```bash
  ulimit -s 4096  # Set to 4 MB
  just ch-06-03-example
  ```

## Conclusion

The code **does** demonstrate a stack overflow - the difference in behavior is:

- **Apple Clang**: Conservative, enforces soft limit for safety ✓
- **Zig CC**: Permissive, relies on OS to handle stack growth

The "intended" educational example (showing a segfault) works with the system compiler, but `zig cc` allows dynamic stack growth, making the allocation succeed.
