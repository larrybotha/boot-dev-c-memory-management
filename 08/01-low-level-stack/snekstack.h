#pragma once

#include <stdlib.h>

typedef struct SnekStack {
  size_t count;
  size_t capacity;
  void **data;
} snek_stack_t;

snek_stack_t *alloc_stack(size_t cap);
void free_stack(snek_stack_t **ptr);
