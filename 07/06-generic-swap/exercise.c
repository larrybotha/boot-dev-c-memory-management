#include "exercise.h"
#include <stdlib.h>
#include <string.h>

void swap(void *a, void *b, size_t size) {
  if (!a || !b) {
    return;
  }

  // use malloc instead of calloc - we know we'll immediately assign the memory
  void *tmp = malloc(size);

  if (!tmp) {
    return;
  }

  memcpy(tmp, a, size);
  memcpy(a, b, size);
  memcpy(b, tmp, size);

  free(tmp);
}

void swap_via_stack(void *a, void *b, size_t size) {
  if (!a || !b) {
    return;
  }

  // Instead of allocating to the heap, we can allocate to
  // the stack, mitigating:
  // - null check for pointer
  // - freeing the memory
  //
  // 'unsigned char' is the idiomatic way in C to indicate
  // raw bytes, which is what memcpy works with
  unsigned char tmp[size];

  memcpy(tmp, a, size);
  memcpy(a, b, size);
  memcpy(b, tmp, size);
}
