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

void free_stack(snek_stack_t **stack) {
  if (!*stack) {
    return;
  }

  free((*stack)->data);
  (*stack)->data = NULL;

  free(*stack);
  *stack = NULL;
}

void push_stack(snek_stack_t *stack, const void *x) {
  if (!stack) {
    return;
  }

  size_t cap = stack->capacity;
  size_t count = stack->count;

  if (count == cap && cap > 0) {
    stack->capacity = GROWTH_FACTOR * cap;
    stack->data = realloc(stack->data, stack->capacity * sizeof(*stack->data));

    if (!stack->data) {
      stack->capacity = cap;

      return;
    }
  }

  stack->data[count] = (void *)x;
  stack->count += 1;
}

void pop_stack(snek_stack_t *stack) {
  if (!stack) {
    return;
  }

  size_t count = stack->count;
  size_t cap_orig = stack->capacity;

  if (count == 0) {
    return;
  }

  stack->data[count - 1] = NULL;
  stack->count -= 1;

  if (stack->count > cap_orig / GROWTH_FACTOR) {
    return;
  }

  if (cap_orig > 1) {
    stack->capacity /= GROWTH_FACTOR;
    stack->data = realloc(stack->data, stack->capacity * sizeof(*stack->data));

    if (!stack->data) {
      stack->capacity = cap_orig;
    }
  }
}
