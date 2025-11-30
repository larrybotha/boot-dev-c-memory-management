#include <stdio.h>
#include <stdlib.h>

void alloc_int(int **ptr_ptr, int value) {
  printf("\n>>>>>>>>>>>>> alloc_int start\n");
  printf("\tptr_ptr before:  %p\n", ptr_ptr);
  printf("\t&ptr_ptr before: %p\n", &ptr_ptr);
  printf("\t*ptr_ptr before: %p\n", *ptr_ptr);

  printf("\n");

  *ptr_ptr = malloc(sizeof(int));

  if (*ptr_ptr == NULL) {
    fprintf(stderr, "Unable to allocate memory\n");

    return;
  }

  **ptr_ptr = value;

  printf("\tptr_ptr after:   %p\n", ptr_ptr);
  printf("\t&ptr_ptr after:  %p\n", &ptr_ptr);
  printf("\t*ptr_ptr after:  %p (new address!!!)\n", *ptr_ptr);
  printf("\t**ptr_ptr after: %d\n", **ptr_ptr);
  printf("<<<<<<<<<<<<< alloc_int end\n\n");
}

void alloc_from_non_null() {
  printf("\n\n--------------------\n");
  printf("alloc_from_non_null\n");
  printf("--------------------\n");

  int x = 42;
  int *ptr_x = &x;

  printf("x before:      %d\n", x);
  printf("&x before:     %p\n", &x);
  printf("&ptr_x before: %p\n", &ptr_x);
  printf("ptr_x before:  %p\n", ptr_x);
  printf("*ptr_x before: %d\n", *ptr_x);

  printf("\n");

  alloc_int(&ptr_x, 43);

  printf("x after:      %d\n", x);
  printf("&x after:     %p (value address unaffected)\n", &x);
  printf("&ptr_x after: %p (pointer's address unaffectec)\n", &ptr_x);
  printf("ptr_x after:  %p (pointer's value updated)\n", ptr_x);
  printf("*ptr_x after: %d\n", *ptr_x);
}

void alloc_from_null() {
  printf("\n\n--------------------\n");
  printf("alloc_from_null\n");
  printf("--------------------\n");

  int *ptr = NULL;

  // dereferencing a NULL pointer - NOPE
  /*printf("*ptr before:    %p\n", *ptr);*/
  printf("&ptr before:    %p\n", &ptr);
  printf("ptr before:     %p\n", ptr);

  printf("\n");

  alloc_int(&ptr, 43);

  printf("&ptr after:     %p (pointer's address unaffected)\n", &ptr);
  printf("ptr after:      %p (pointer's value updated)\n", ptr);
  printf("*ptr after:     %d\n", *ptr);
}

int main() {
  alloc_from_non_null();
  alloc_from_null();
}
