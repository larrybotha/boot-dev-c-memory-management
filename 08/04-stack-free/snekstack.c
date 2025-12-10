#include "snekstack.h"
#include <stdlib.h>

snek_stack_t *alloc_stack(size_t cap) {
  snek_stack_t *stack = calloc(1, sizeof(snek_stack_t));

  if (!stack) {
    return NULL;
  }

  stack->capacity = cap;
  stack->count = 0;
  stack->data = calloc(cap, sizeof(*stack->data));

  if (!stack->data) {
    free(stack);

    return NULL;
  }

  return stack;
}

void push_stack(snek_stack_t *stack, void *value) {
  if (!stack) {
    return;
  }

  size_t count = stack->count;
  size_t cap = stack->capacity;

  if (count == cap) {
    size_t new_cap = cap * GROWTH_FACTOR;
    void **new_data = realloc(stack->data, new_cap * sizeof(*stack->data));

    if (!new_data) {
      stack->capacity = cap;

      return;
    }

    stack->capacity = new_cap;
    stack->data = new_data;
  }

  stack->data[count] = value;
  stack->count += 1;
}

void free_stack(snek_stack_t **stack) {
  if (!stack) {
    return;
  }

  free((*stack)->data);
  (*stack)->data = NULL;

  free(*stack);
  *stack = NULL;
}

void *pop_stack(snek_stack_t *stack) {
  if (!stack || stack->count == 0) {
    return NULL;
  }

  void *x = stack->data[stack->count - 1];
  stack->count -= 1;

  if (stack->count > 0 && stack->count <= stack->capacity / 2) {
    size_t new_cap = stack->capacity / GROWTH_FACTOR;
    void **new_data = realloc(stack->data, new_cap * sizeof(*stack->data));

    if (!new_data) {
      return x;
    }

    stack->capacity = new_cap;
    stack->data = new_data;
  }

  return x;
}
