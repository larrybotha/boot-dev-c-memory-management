#include "snekstack.h"
#include <stdio.h>
#include <stdlib.h>

snek_stack_t *alloc_stack(size_t capacity) {
  // WRONG: we do not need to assign capacity * snek_stack_t items in memory,
  // only 1
  /*snek_stack_t *result = calloc(capacity, sizeof(*result));*/
  snek_stack_t *result = calloc(1, sizeof(*result));

  if (!result) {
    return NULL;
  }

  result->capacity = capacity;
  result->count = 0;
  result->data = calloc(capacity, sizeof(*result->data));

  if (!result->data) {
    free(result);

    return NULL;
  }

  return result;
}

void free_stack(snek_stack_t **ptr) {
  free((*ptr)->data);
  (*ptr)->data = NULL;

  free(*ptr);
  *ptr = NULL;
}

void push_stack(snek_stack_t *stack, void *x) {
  // WRONG: use consistent types for fields - int != size_t
  /*int count = stack->count;*/
  /*int cap = stack->capacity;*/
  size_t count = stack->count;
  size_t cap = stack->capacity;

  if (cap == count) {
    stack->capacity *= 2;

    // WRONG: use realloc to update memory size
    /*free(stack->data);*/
    /*stack->data = calloc(cap, sizeof(*stack->data));*/
    // WRONG: we need to allocate sufficient space for 'capacity' times
    // number of pointers
    /*stack->data = realloc(stack->data, sizeof(*stack->data));*/
    stack->data = realloc(stack->data, stack->capacity * sizeof(*stack->data));

    if (!stack->data) {
      return;
    }
  }

  // WRONG: it's redundant to assign memory for the items in the
  // array:
  // - the array is already a list of pointers, and
  // - we have received x _as a pointer_
  //
  // Because of this, we can assign x directly to the index
  /*stack->data[count] = calloc(1, sizeof((void *)x));*/
  /*if (stack->data[count] == NULL) {*/
  /*  return;*/
  /*}*/

  stack->data[count] = x;
  stack->count += 1;
}
