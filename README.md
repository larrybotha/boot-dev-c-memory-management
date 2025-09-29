# boot.dev C Memory Management

Learnings and annotations from boot.dev's
[C Memory Management course](https://www.boot.dev/lessons/44a4421c-cc49-4472-bbad-a14f81f860b4)

## Chapter 1 - C Basics

- `void`:
    * as a function parameter, signifies explicitly that no arguments are taken
    * as a return type, signifies there is no return type
- [`.c` and `.h` files](https://utat-ss.readthedocs.io/en/master/c-programming/c_h_files.html)
    * `.c` - implementation file
    * `.h` - header file, required for defining interfaces and making functions,
        globals, and macros available to other files
        + using the `#pragma once` directive prevents header files from being
            imported multiple times, which can cause issues with redefinition of
            structs
        + another way to avoid importing headers multiple times is to use
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
    * `sizeof` is used to get the size of types
- some types have guaranteed sizes:
    * `char` - 1 byte, signed or unsigned
    * `float` - 4 bytes; single-precision floating-point number
    * `double` - 8 bytes; double-precision floating-point number
- `sizeof` returns a type of `size_t`
    - [01/19-sizeof/main](./01/19-sizeof/main.c)
    * `size_t` is guaranteed to be able to represent the size of the current
        system's largest non-struct type
    * `%zu` is used for printing the result from `sizeof`

## Chapter 2 - Structs

- structs may be initialised in a number of ways:
    * with a zero initialiser
        - i.e. providing a single zero-value for the entire struct
    * with a positional initialiser
        - i.e. providing each value as a positional
            argument
    * with a designated initialiser
        - i.e. providing the names of the values to assign explicitly
- multiple values cannot be returned from a function in C; use a struct
- `typedef` allows for writing structs with an alias, allowing one to drop the
    `struct` keyword when referencing it. The convention in C is to append
    the name with a `_t` to indicate that it is a type
    * using `typedef` makes the name of the struct optional

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

    ```
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

    ```
    |           Thing       |
     <-         8B        ->
    | c | (padding) |   x   |
    | . |  .  .  .  |. . . .|
     1B       3B        4B
    ```

    The resulting aligment is compiler and architecture dependant
- due to padding, structs can vary in size based on the order of their
    properties
    * prefer ordering struct properties from largest to smallest to
        assist the compiler in minimising padding

## Chapter 3 - pointers

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
- to modify a struct using a function, on needs to pass a _pointer_ to the struct
- accessing a struct's properties via a pointer can be done in two ways:
    * using the arrow syntax: `ptr->x`
    * by dereferencing the ptr: `(*ptr).x`
- arrays have a fixed size in C, have contiguous memory locations for values, and
    are homogenous
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
    - see [./03/09-arrays-as-pointers/example.c](./03/09-arrays-as-pointers/example.c)
- values in arrays can be accessed in a number of ways:
    * using `[n]` indexing
        - `xs[2]`
    - derefering a pointer pointing to the `n`th value in the array
        * `*xs_ptr`
    * be dereferencing the pointer `n` memory units from the pointer to the first
        value in the array
        + `*(xs + 2)`
- an array of structs containing only integers can be cast to an array of
    integers
    * see [./03/11-array-casting/main.c](./03/11-array-casting/main.c)
- an array is not only a pointer to the first value in the array, it is also
    a block of memory that holds all the elements of that array
- [arrays decay to pointers](https://port70.net/~nsz/c/c11/n1570.html#6.3.2.1)
    i.e. arrays 'become' a pointer to the first item     in the array
- arrays decay to pointers when used in expressions containing pointers:

    ```c
    int xs[3];              // declared but not initialised
    int *ptr = xs;          // no need to use the address operator
    int value = *(xs + 2);  // using pointer arithmetic results in decay
    ```
- arrays do not decay when:
    - using `sizeof`
    - using the `&` address-of operator - this is a pointer to the whole array,
        not the first item in the array
    - when initialised - it is fully allocated in memory and doesn't decay


