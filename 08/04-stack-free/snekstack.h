#pragma once

#include <stdlib.h>
#define GROWTH_FACTOR 2;

typedef struct SnekStack {
  size_t capacity;
  size_t count;
  void **data;
} snek_stack_t;

snek_stack_t *alloc_stack(size_t cap);
void push_stack(snek_stack_t *stack, void *value);
void *pop_stack(snek_stack_t *stack);
void free_stack(snek_stack_t **stack);
