# boot.dev C Memory Management

Learnings and annotations from boot.dev's
[C Memory Management course](https://www.boot.dev/lessons/44a4421c-cc49-4472-bbad-a14f81f860b4)

## [01 - C Basics](./01/)

- `void`:
  - as a function parameter, signifies explicitly that no arguments are taken
  - as a return type, signifies there is no return type
- [`.c` and `.h` files](https://utat-ss.readthedocs.io/en/master/c-programming/c_h_files.html)

  - `.c` - implementation file
  - `.h` - header file, required for defining interfaces and making functions,
    globals, and macros available to other files

    - using the `#pragma once` directive prevents header files from being
      imported multiple times, which can cause issues with redefinition of
      structs
    - another way to avoid importing headers multiple times is to use
      _include guards_ in the header file to check if it has already been
      included:

      ```c
      #ifndef MY_HEADER_H
      #define MY_HEADER_H
      // code
      #endif
      ```

      The guard will prevent the header from being processed multiple times

      This method relies on a unique
      [`macro`](https://gcc.gnu.org/onlinedocs/cpp/Macros.html) for the
      header file

      Prefer the `#pragma once`, though, as it's less error-prone and quicker
      to use

- Javascript's ternary is the same as in C
- the size of types is system-dependant. e.g. on a 32-bit system `int` is usually
  4 bytes, while on a 64-bit system it's 8 bytes
  - `sizeof` is used to get the size of types
- some types have guaranteed sizes:
  - `char` - 1 byte, signed or unsigned
  - `float` - 4 bytes; single-precision floating-point number
  - `double` - 8 bytes; double-precision floating-point number
- `sizeof` returns a type of `size_t`
  - [01/19-sizeof/main](./01/19-sizeof/main.c)
  - `size_t` is guaranteed to be able to represent the size of the current
    system's largest non-struct type
  - `%zu` is used for printing the result from `sizeof`

## [02 - Structs](./02/)

- structs may be initialised in a number of ways:
  - with a zero initialiser
    - i.e. providing a single zero-value for the entire struct
  - with a positional initialiser
    - i.e. providing each value as a positional
      argument
  - with a designated initialiser
    - i.e. providing the names of the values to assign explicitly
- multiple values cannot be returned from a function in C; use a struct
- `typedef` allows for writing structs with an alias, allowing one to drop the
  `struct` keyword when referencing it. The convention in C is to append
  the name with a `_t` to indicate that it is a type

  - using `typedef` makes the name of the struct optional

    ```c
    struct Cat {
        char *name;
    };

    typedef struct {
        char *name;
    } dog_t;

    int main() {
        struct Cat c = {.name = "Meowser"};
        dog_t d = {.name = "Beowser"};
    }
    ```

- the `sizeof` a struct is the sum of sizes of its parts
- structs are stored contiguously in memory:

  ```c
  struct Coord {
      int x;
      int y;
      int z;
  }
  ```

  ```text
  |           Coord       |
   <-         12B       ->
  |   x   |   y   |   z   |
  |. . . .|. . . .|. . . .|
   < 4B  > < 4B  > < 4B  >
  ```

- reads and writes are performed when data is naturally
  [aligned](https://en.wikipedia.org/wiki/Data_structure_alignment)

  i.e. the data is stored in multiples of its data size. In a 32-bit
  system this may mean consecutively in 4-byte boundaries, starting
  at the beginning of a 4-byte boundary

  e.g. for mixed types, we may have the following:

  ```c
  struct Thing {
      char c; // 1 byte
      int x; // 4 bytes
  }
  ```

  ```text
  |           Thing       |
   <-         8B        ->
  | c | (padding) |   x   |
  | . |  .  .  .  |. . . .|
   1B       3B        4B
  ```

  The resulting alignment is compiler and architecture dependent

- due to padding, structs can vary in size based on the order of their
  properties
  - prefer ordering struct properties from largest to smallest to
    assist the compiler in minimising padding

## [03 - Pointers](./03/)

- the size of pointers is determined by the architecture of the system the
  process is running on, but it is always consistent within the process
- variables are human-readable names that refer to data in memory
- memory is a contiguous array of bytes assigned to a process, where
  the data is stored
- the `%p` [format specifier](https://en.cppreference.com/w/c/io/fprintf#:~:text=The%20following%20format%20specifiers%20are%20available%3A)
  is used for printing addresses
- [`long long`](https://en.wikipedia.org/wiki/C_data_types) is a potentially very
  large integer - at least 64 bytes
- memory addresses are always written in hexadecimal
- `&` gets the address of a value, which is a pointer type
- pointers are declared using `*`
- values are obtained from pointers by dereferencing, using `*`
- in C, structs are passed by value
  - modifying a struct passed into a function will leave the original intact
  - a struct returned from a function will have a different address to
    the one passed in
- to modify a struct using a function, one needs to pass a _pointer_ to the struct
- accessing a struct's properties via a pointer can be done in two ways:
  - using the arrow syntax: `ptr->x`
  - by dereferencing the ptr: `(*ptr).x`
- arrays have a fixed size in C, have contiguous memory locations for values, and
  are homogeneous
- arrays in C act as pointers to the first value in the array

  - e.g.

    ```c
    int xs[3] = {1,2,3};
    int *p1 = xs; // NOTE: no '&' - xs and p1 are equivalent
    int *p2_a = &xs[1];
    int *p2_b = (xs + 1); // p2_a and p2_b reference the same address
    ```

  - see [./03/09-arrays-as-pointers/test.c](./03/09-arrays-as-pointers/test.c)

- one can advance a pointer `n` memory addresses using pointer arithmetic:

  ```c
  int xs[3] = {1,2,3};
  int *ptr = xs;

  printf("%d\n", *ptr); // 1

  ptr += 1;

  printf("%d\n", *ptr); // 2
  ```

  - the addresses of pointers move by the size of the data type they point to
  - see [./03/09-arrays-as-pointers/example.c](./03/09-arrays-as-pointers/example.c)

- values in arrays can be accessed in a number of ways:
  - using `[n]` indexing
    - `xs[2]`
  - derefering a pointer pointing to the `n`th value in the array
    - `*xs_ptr`
  - be dereferencing the pointer `n` memory units from the pointer to the first
    value in the array
    - `*(xs + 2)`
- an array of structs containing only integers can be cast to an array of
  integers
  - see [./03/11-array-casting/main.c](./03/11-array-casting/main.c)
- an array is not only a pointer to the first value in the array, it is also
  a block of memory that holds all the elements of that array
- [arrays decay to pointers](https://port70.net/~nsz/c/c11/n1570.html#6.3.2.1)
  i.e. arrays 'become' a pointer to the first item in the array
- arrays decay to pointers when used in expressions containing pointers:

  ```c
  int xs[3];              // when declared but not initialised
  int *ptr = xs;          // no need to use the address operator
  int value = *(xs + 2);  // using pointer arithmetic results in decay
  ```

- arrays decay to pointers when passed as arguments to functions

  ```c
  #include <stdio.h>

  func implicit_sig(const int xs[]) {
    // xs is an array of ints... but because it _decays_ to a pointer,
    // the signature for do_y is more representative of that decay

    printf("sizeof(xs): %zu\n" sizeof(xs)); // => 8 (size of pointer)
  }

  func explicit_sig(const int *xs) {
    // xs is a pointer to an int

    printf("sizeof(xs): %zu\n" sizeof(xs)); // => 8 (size of pointer)
  }

  func main() {
    int xs[] = {1,2,3};

    printf("sizeof(xs): %zu\n" sizeof(xs)); // => 3

    implicit_sig(xs);
    explicit_sig(xs);
  }
  ```

  - see [./03/13-arrays-decay-to-pointers/main.c](./03/13-arrays-decay-to-pointers/main.c)

- arrays do not decay when:
  - using `sizeof`
  - using the `&` address-of operator - this is a pointer to the whole array,
    not the first item in the array
  - when initialised - it is fully allocated in memory and doesn't decay
- the pointers for an array and the first item in an array point to the same
  address, but they behave differently:

  ```c
  #include <stdio.h>
  #include <assert.h>

  int main() {
    int xs[] = {1,2,3};

    // address of first item using & operator and pointer arithmetic
    // is the same
    for (int i = 0; i < len; i++) {
      assert(&xs[i] == (xs + i));
    }

    // address at xs is same as &xs[0]
    assert((void *)xs == (void *)&xs[0]);

    // address at &xs is same as &xs[0]
    assert((void *)(&xs) == (void *)&xs[0]);
  }
  ```

- a C-string, i.e. `char *msg = "foo";`:
  - is how text is represented in C
  - is a pointer to the first character in an element array
  - is terminated by the `NUL` byte, `\0`
- strings do not store their length - the length is determined by the position of
  the null terminator
  - `strlen` iterates over the strings until it gets to the null terminator
  - due to the lack of a stored length, working with strings must be done
    with care in order to avoid buffer overflows and off-by-one errors
  - the null terminator does not count towards the length of a string
- strings can be declared either using arrays or pointers:

  ```c
  char *str1 = "foo";
  char str1[] = "bar";
  ```

- given the following:

  ```c
  char str1[50] = "foo";
  char *str2 = "bar";

  strcat(str1, str2); // foobar
  ```

  - The initial memory representation of `str1` would be 50 bytes
  - `strcat` doesn't have the length of `str1`, but the null terminator
    indicates _where_ the string ends
  - the null terminator is used to ensure that only the characters up to
    the null terminator are used for concatenation

- string methods:
  - `strlen` - get the length of a string up until and excluding the null terminator
  - `strcat` - append src onto dest
    - _do not use on uninitialised string_; undefined behaviour
  - `strncat` - append n chars from src onto dest
  - `strcpy` - copy a src into a destination - safe for uninitialised strings
  - `strncpy` - copy n chars from src to dest
  - `strcmp` - compares two strings
  - `strchr` - returns a pointer to the first occurrence of char in string
  - `strstr` - returns a pointer to the first occurrence of substring in string

### Forward declarations

A forward declaration allows one to define types that reference themselves, or to
be used recursively

They are composed of 2 parts - the forward declaration itself, which
is a struct without any fields, and the struct that references itself:

```c
typedef struct Node node_t;

typedef struct Node {
  int value;
  next *next;
}
```

### Mutual structs

Structs may have circular dependencies, in which multiple forward declarations can
allow for the references

```c
typedef struct A a_t;
typedef struct B b_t;

typedef struct A {
  b_t *b;
} a_t;
typedef struct B {
  a_t *a;
} b_t;
```

## [04 - Enums](./04/)

Go seems to have been inspired by C's approach for enums:

```c
typedef enum State {
  A,
  B,
  C
} state_t;

// A => 1
// B => 2
// C => 3
```

Non-default values can be provided:

```c
typedef enum HttpStatus {
  HTTP_OK = 200,
  HTTP_CREATED, // incremented value == 201
  HTTP_NOT_FOUND = 404,
} http_status_t;
```

`sizeof` works on enums as with other types. It's _generally_ equivalent to
`sizeof(int)`, but if enum values are too large to be represented by `int`,
`unsigned long` or `long` may be used

## [05 - Unions](./05/)

Unions are somewhat like sum-types - they can represent different types,
but unlike structs, can only hold one of those types at a time.

The C compiler uses all the fields in the union to determine the maximum size
of the type.

- when working with unions, it's important to access only the fields for the
  union that were set for that union. Accessing fields that were not set when
  initialised is undefined behaviour.

  e.g. for the following union:

  ```c
  typedef union {
    int age;
    char *name;
  } age_or_name_t;
  ```

  If `.name` was set at init, one should stick to accessing `.name`.

- all fields in a union share the same allocated memory - for this reason,
  accessing any field in a union which is not the value that was set is
  generally a bad idea
- for values that are composed of discrete parts of known sizes, a union can
  be used to represent both the full value and its components

  e.g.

  ```c
  typedef union RgbaColor {
    struct { // 32 bits
      uint8_t r;
      uint8_t g;
      uint8_t b;
      uint8_t a;
    } components;
    uint32_t value; // 32 bits
  }
  ```

_side note_: `sprintf` takes a buffer that can be written to, a string with
format specifiers, and the values to insert into the
format specifiers.

## [06 - Stack and heap](./06/)

### The Stack

- the stack is composed of memory frames - the memory allocated for each function call
- each frame contains the following information:
  - the return address
  - the memory allocations for arguments to the function
  - the memory allocations for variables local to the function
- each time a function is called, a _stack pointer_ is moved forward the appropriate
  distance in memory from its current address to accommodate the stack frame
- each successive function call pushes a stack frame onto the stack, and each
  time a function returns, that function's frame is popped off of the stack

e.g. for the following function:

```c
void create_typist(int uses_nvim) { // 4 bytes
  int wpm = 150; // 4 bytes
  char name[4] = {'s', 'p', 'a', 'm'}; // 4 * 1 byte
}
```

with the next allocatable memory address at `0x0004` we have:

```text
| address | name      | value | type  | size |
| ---     | ---       | ---   | ---   | ---  |
| ...     |           |       |       |      |
| 0x0004  |           |       | int * | 4    | ┐ ← return address
| 0x0008  | uses_nvim | n     | int   | 4    | │
| 0x000c  | wpm       | 150   | int   | 4    | │
| 0x0010  | name[0]   | 's'   | char  | 1    | │ stack frame
| 0x0011  | name[0]   | 'p'   | char  | 1    | │
| 0x0012  | name[0]   | 'a'   | char  | 1    | │
| 0x0013  | name[0]   | 'm'   | char  | 1    | ┘ ← stack pointer
| ...     |           |       |       |      |
```

From this we can see:

- memory is allocated contiguously
- moving the stack pointer means incrementing or decrementing it by the size of the stack frame

Stack allocations have a few performance benefits over heap allocations:

- due to the increment / decrement nature of moving the stack pointer it
  is much cheaper than the heap having to resolve and manage addresses
- contiguous addresses for related data makes for spatial locality, resulting in
  faster CPU lookups for that data
- memory is managed automatically - memory is allocated for each new frame, memory
  is deallocated when each function returns
- thread-safe - each thread has its own stack, whereas the heap is shared across
  threads, requiring synchronisation

The Go compiler uses escape analysis to determine when stack allocation is appropriate,
which helps make Go fast. Python, on the other hand, tends to allocate most objects to
the heap.

A limitation of allocating to the stack is its limited size - if the number of stack
frames grows beyond the amount of memory allocated to a process's stack, you'll
get a stack overflow

The stack size limit for a system can be found using `ulimit`:

```shell
# soft stack size limit
$ ulimit -s
8176 # +-8Mb

# hard stack size limit
ulimit -sH
65520 # +-64Mb
```

A single stack frame can blow the limit using too large an allocation:

```c
void do_it(int size) {
  char chars[size]; // triggers stack overflow when compiled with gcc

  chars[0] = 'a';
}

int main() {
  // safe
  do_it(1024 * 1024 * 7); // +- 7Mb

  // causes stack overflow when compiled with gcc
  do_it(1024 * 1024 * 10); // +- 10Mb
}
```

### Pointers to the stack

Returning pointers to values created within functions results in undefined behaviour -
those pointers end up pointing to locations in memory that have been deallocated

i.e.

- define a variable
- value is assigned memory location in stack frame
- return pointer to value
- function exits, popping stack frame, deallocating memory
- call-site receives address to memory that is no longer allocated

See [./06/04-pointers-to-the-stack/main.c](./06/04-pointers-to-the-stack/main.c)

### The Heap

With C, we always need to do describe 2 things:

- how large is the thing we're working with?
- where do we put it? i.e. stack vs heap

Generally, if we don't need dynamically allocated memory, the stack will be used.
If we don't know upfront how much memory will be required, it usually indicates that
we need to allocate memory on the heap.

It's important to remember that arguments to functions is that they are _copied_.

- Stack
  - size is known ahead of time, _and_
  - value exists only within the function in which it is defined
- Heap
  - size is unknown ahead of time, _or_
  - return value isn't limited to one function

When the life of a value exceeds that of the function that created it, it belongs,
it needs to be allocated to the heap.

To allocate to the heap:

- we need `stdlib.h` to have access to `malloc`
- `malloc` takes a size to determine how much memory to allocate to the heap
- `malloc` returns a `void *` - a pointer to the memory location
- we cast that pointer to the type we expect for the data type we're allocating
  memory for
- we use `free` to deallocate the memory when it's no longer required. Assignments to
  the heap occupy OS resources, and failing to free prevents other processes running on
  the OS to assign to that memory until the process that assigned the memory is
  exited
- once freed, although the pointer still exists, it should never be referenced.
  It is a _dangling pointer_, pointing to now deallocated memory

#### Malloc

[./06/06-malloc/test.c](./06/06-malloc/test.c)

- returns a pointer to an uninitialised memory location, or `NULL` if the allocation
  failed
- that memory location contains whatever data was previously written to it
- it is the programmer's responsibility to deallocate the memory allocated via `malloc`
- `calloc` allows for allocating memory _and_ assigning a zero value to the memory
  location

  - zeroing is not always free; `calloc` can be more expensive than `malloc`,
    _but not always_

  - `calloc` is the equivalent of allocating memory, and then zeroing:

    ```c
    int *xs = malloc(n * sizeof(int));

    memset(xs, 0, n * sizeof(int));
    ```

    In this case, use `calloc`

  - `calloc` does overflow checking that `malloc` doesn't
  - `calloc` is required if the memory needs to zero-initialised
  - in general, favour `calloc` over `malloc`, unless there are specific
    performance requirements that justify using `malloc`, or you know you'll
    immediately overwrite the data

- the workflow for manual memory assignment is the following:
  - assign using `malloc` or `calloc`
  - check that the returned pointer is not `NULL`
  - use the variable
  - `free` the memory to make it available to the OS again

#### Free

[./06/06-free/test.c](./06/06-free/main.c)

`free` does one thing: it tells the OS that the memory that was previously allocated
(i.e. reserved) for a variable is now available to be used again.

It does not change the data at that memory location, and it doesn't change the
address.

Forgetting to free memory is where memory leaks come from.

#### Big Endian Little Endian

Endianness is the order in which bytes are stored in memory. If the most significant
value is on the left, it is Big Endian, other it is Little Endian.

e.g. for the hex value `0x12345678`

```text
Big Endian

| address | value |
| ---     | ---   |
| ...     |       | ← lower addresses
| 0x0004  | 0x12  | ┐ ← most significant bit
| 0x0008  | 0x34  | │
| 0x000c  | 0x56  | │
| 0x0010  | 0x78  | ┘
| ...     |       | ← higher addresses


Little Endian

| address | value |
| ---     | ---   |
| ...     |       | ← lower addresses
| 0x0004  | 0x78  | ┐ ← least significant bit
| 0x0008  | 0x56  | │
| 0x000c  | 0x34  | │
| 0x0010  | 0x12  | ┘
| ...     |       | ← higher addresses
```

Most modern systems store values using the little-endian
ordering

## Advanced pointers

### Pointer pointers

- [./07/01-pointer-pointers/test.c](./07/01-pointer-pointers/test.c)
- [./07/01-pointer-pointers/main.c](./07/01-pointer-pointers/main.c)

A pointer can point to another pointer:

```c
int main() {
  int x = 42;
  int *ptr_x = &x;
  int **ptr_ptr_x = &ptr_x;
}
```

It's important to think of pointer pointers using the fundamental data types:

```c
#include <stdlib.h>
#include <stdio.h>

int main() {
  int *ptr = NULL; // address is 0x0

  // pass the address of ptr to the function
  alloc_int(&ptr, 10);
}

// We receive a pointer to a pointer. In this example:
//  - ptr_ptr is the address of a pointer to an int
//  - in this example, that address is 0x0 - the NULL pointer
void alloc_int(int **ptr_ptr, int value) {
  // We want the original pointer to point to a new value without affecting
  // the value its location currently points to
  // To do this, we
  // 1. dereference ptr_ptr to get the original pointer
  // 2. using malloc:
  //    - allocate enough memory to store an int
  //    - assign the pointer the return value of malloc, a new pointer
  *ptr_ptr = malloc(sizeof(int));

  // malloc may return NULL if the system is out of memory - bail if so
  if (*ptr_ptr == NULL) {
    fprintf(stderr, "unable to allocate memory\n");

    return;
  }

  // At this point we know we can assign a value
  //  - the original pointer now has a different address in memory
  //  - we double-dereference ptr_ptr to 'access the value' in memory
  //  - we assign the provided value
  **ptr_ptr = n;
}
```

_NOTE_: `size_t is useful when working with when to use `size_t` vs other numeric types:

1. Representing sizes or counts of objects
   in memory

   - Array lengths, buffer sizes, element

counts - Return values from sizeof() operator - Parameters to memory functions:
malloc(), calloc(), memcpy(), etc. 2. Array indexing and iteration - Loop counters when iterating over
arrays (as in your lines 14, 21) - Prevents comparison warnings with array
bounds 3. Working with standard library functions
that use size_t - strlen(), memcpy(), fread(), etc. all
use size_t - Matching types prevents implicit
conversions

Why: size_t is guaranteed to hold the
maximum size of any object. It's unsigned,
so negative values are impossible (which
makes sense for sizes).

_SIDENOTE_:

`size_t` gives us two guarantees

- it's unsigned, so negative values are impossible
- it will hold the maximum size of any object

It's useful in the following scenarios:

- representing counts of objects in memory, i.e.
  - array lengths, buffer sizes, element counts
  - the return value of `sizeof`
  - parameters to `malloc`, `calloc`, `memcpy`
- array indexing and loop counters
- working with standard lib functions, such as `strlen`, `fread`

When to use `size_t`:

```text
Can the value be negative?
├─ YES → Use a signed type (int, ssize_t, ptrdiff_t)
└─ NO → Is it a size/count/index?
    ├─ YES → Use size_t
    └─ NO → Consider uint32_t, uint64_t, or an int based on range/semantics
```

### Void pointers

- [./07/03-void-pointers/exercise.c](./07/03-void-pointers/exercise.c)
- [./07/03-void-pointers/main.c](./07/03-void-pointers/main.c)

Void pointers, `void *`, are also known as generic pointers - they
can point to any value.

They are a mechanism for polymorphism in C.

Where a function expects a concrete type, a void pointer needs to be cast
to the correct type:

```c
#include <stdio.h>

int main() {
  int x = 42;
  void *ptr = &x;

  // not allowed
  printf("x is %d\n", *ptr);

  // will work
  printf("x is %d\n", *(int *)ptr);
}
```

### Swapping

- [./07/04-swapping-integers/](./07/04-swapping-integers/exercise.c)
- [./07/05-swapping-strings/](./07/05-swapping-strings/exercise.c)
- [./07/06-generic-swap/exercise.c](./07/06-generic-swap/exercise.c)
- [./07/06-generic-swap/main.c](./07/06-generic-swap/main.c)

`<string.h>`'s `memcpy` allows for generically copying values to other locations
in memory without knowing the type, e.g. when working with `void *`:

````c
#include <string.h>

int main() {
  int x = 1;
  int y = 2;
  void *ptr_y = &y;

  memcpy(&x, ptr_y, sizeof(int));
}
## Stack data structure```

- every allocation of memory requires a free in the reverse order
  e.g. function `alloc_x` returns a pointer containing a pointer, then it
  should be accompanied by `free_x` which frees first the contained pointer,
  followed by the containing pointer
- to free a pointer, a pointer to that pointer should be passed to the utility.
  When mutating a struct, we pass a pointer to the struct - the same applies
  with pointers - to mutate the pointer, i.e. free it, we pass a pointer to the
  pointer, and dereference it within the `free`
````
