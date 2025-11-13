#include <stdio.h>

int main() {
  int xs[4] = {1, 2, 3, 4};
  const int *ptr = xs;
  int *ptr2 = xs;
  int len = sizeof(xs) / sizeof(int);

  printf("sizeof(ptr): %zu\n", sizeof(ptr));
  printf("address of pointer moves by size of type: %zu\n\n", sizeof(int));

  // items in array are allocated addresses in memory contiguously
  for (int i = 0; i < len; i++) {
    printf("     value at xs[%d] == %d\n", i, xs[i]);
    printf("value at *(ptr + %d) == %d\n", i, *ptr2);
    printf("address of xs at %d == %p\n", i, &xs[i]);
    printf("        (ptr2 + %d) == %p\n\n", i, ptr2);

    // increment the pointer for the next iteration
    if (i < len - 1) {
      ptr2 += 1;
    }
  }

  printf("---\n\n");

  printf(" address of xs == %p\n", xs);
  printf("address of ptr == %p\n\n", ptr);

  printf("---\n\n");

  printf("     value of xs[2] == %d\n", xs[2]);
  printf("value at *(ptr + 2) == %d\n", *(ptr + 2));
}
