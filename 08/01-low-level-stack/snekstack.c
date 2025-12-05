#include "snekstack.h"
#include <stdlib.h>

snek_stack_t *alloc_stack(size_t cap) {
  snek_stack_t *result = calloc(1, sizeof(*result));

  // malloc / calloc -> null check
  if (!result) {
    return NULL;
  }

  result->capacity = cap;
  result->count = 0;
  // allocate capacity * pointers available memory
  result->data = calloc(cap, sizeof(void *));

  // malloc / calloc -> null check
  if (!result->data) {
    // free any memory previously allocated
    free(result);

    return NULL;
  }

  return result;
}

void free_stack(snek_stack_t **ptr) {
  if (!*ptr) {
    return;
  }

  // dereference the pointer _before_ accessing its field
  free((*ptr)->data);
  (*ptr)->data = NULL;

  free(*ptr);

  *ptr = NULL;
}
