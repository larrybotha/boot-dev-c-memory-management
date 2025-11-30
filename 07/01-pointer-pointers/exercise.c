#include "exercise.h"
#include <stdio.h>
#include <stdlib.h>

void alloc_int(int **ptr_ptr, int n) {
  // before we can assign a value to the original pointer, we need to
  // allocate memory for the pointer pointer
  *ptr_ptr = malloc(sizeof(int));

  // malloc may return NULL if out of memory
  // If we _don't_ have NULL, then it's safe for us to assign
  // the value to that location in memory
  if (*ptr_ptr == NULL) {
    fprintf(stderr, "Unable to allocate integer\n");

    return;
  }

  **ptr_ptr = n;
}
