#include "exercise.h"
#include <stdio.h>
#include <stdlib.h>

int *alloc_scalar_array(int size, int multiplier) {
  int *xs = calloc(size, sizeof(int));

  if (xs == NULL) {
    fprintf(stderr, "Unable to allocate memory\n");

    return NULL;
  }

  for (int i = 0; i < size; i++) {
    xs[i] = multiplier * i;
  }

  return xs;
}
