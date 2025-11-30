#include "exercise.h"
#include <stdlib.h>

int *alloc_scalar_list(int size, int multiplier) {
  int *xs = calloc(size, sizeof(int));

  if (xs == NULL) {
    return NULL;
  }

  for (int i = 0; i < size; i++) {
    xs[i] = i * multiplier;
  }

  return xs;
}
