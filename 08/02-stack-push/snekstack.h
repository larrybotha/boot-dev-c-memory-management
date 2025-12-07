#pragma once

#include <stdlib.h>

typedef struct SnekStack {
  size_t capacity;
  size_t count;
  void **data;
} snek_stack_t;

snek_stack_t *alloc_stack(size_t capacity);
void free_stack(snek_stack_t **ptr);
void push_stack(snek_stack_t *stack, void *x);
