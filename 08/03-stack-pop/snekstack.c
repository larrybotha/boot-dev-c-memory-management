#include <stdlib.h>

#include "snekstack.h"

#define GROWTH_FACTOR 2

snek_stack_t *alloc_stack(size_t cap) {
  snek_stack_t *result = calloc(1, sizeof(*result));

  if (!result) {
    return NULL;
  }

  result->capacity = cap;
  result->count = 0;
  result->data = calloc(cap, sizeof(*result->data));

  if (!result->data) {
    free(result);

    return NULL;
  }

  return result;
}

void free_stack(snek_stack_t **ptr) {
  if (!*ptr) {
    return;
  }

  free((*ptr)->data);
  (*ptr)->data = NULL;

  free(*ptr);
  *ptr = NULL;
}

void push_stack(snek_stack_t *ptr, void *x) {
  if (!ptr) {
    return;
  }

  size_t cap = ptr->capacity;
  size_t count = ptr->count;

  if (count == cap && cap > 0) {
    ptr->capacity = GROWTH_FACTOR * cap;
    ptr->data = realloc(ptr->data, ptr->capacity * sizeof(*ptr->data));

    if (!ptr->data) {
      ptr->capacity = cap;

      return;
    }
  }

  ptr->data[count] = x;
  ptr->count += 1;
}

void pop_stack(snek_stack_t *ptr) {
  if (!ptr) {
    return;
  }

  size_t count = ptr->count;
  size_t cap_orig = ptr->capacity;

  if (count == 0) {
    return;
  }

  ptr->data[count - 1] = NULL;
  ptr->count -= 1;

  if (ptr->count > cap_orig / GROWTH_FACTOR) {
    return;
  }

  if (cap_orig > 1) {
    ptr->capacity /= GROWTH_FACTOR;
    ptr->data = realloc(ptr->data, ptr->capacity * sizeof(*ptr->data));

    if (!ptr->data) {
      ptr->capacity = cap_orig;
    }
  }
}
