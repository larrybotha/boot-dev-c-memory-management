#include <stdio.h>

int main() {
  int x = 42;
  void *ptr = &x;

  // not allowed to dereference void pointer to integer
  /*printf("x is %d\n", *ptr);*/

  // must be explicitly cast
  printf("x is %d\n", *(int *)ptr);
}
