#include <stdio.h>

int main() {
  int xs[4] = {1, 2, 3, 4};
  const int *ptr = xs;
  int *ptr2 = xs;
  int len = sizeof(xs) / sizeof(int);

  // items in array are allocated addresses in memory contiguously
  for (int i = 0; i < len; i++) {
    printf("address of xs at %d == %p\n", i, &xs[i]);
    printf("(ptr2 + %d) == %p\n", i, ptr2);

    // increment the pointer for the next iteration
    if (i < len - 1) {
      ptr2 += 1;
    }
  }

  printf("\n");

  printf("address of xs == %p\n", xs);
  printf("address of ptr == %p\n", ptr);

  printf("\n");

  printf("value of xs[2] == %d\n", xs[2]);
  printf("value at *(ptr + 2) == %d\n", *(ptr + 2));
}
