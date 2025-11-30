#include "exercise.h"
#include <stdio.h>
#include <stdlib.h>

char *get_full_greeting_invalid(const char *greeting, const char *name,
                                int size) {
  char full_greeting[size]; // assign full_greeting to the stack

  snprintf(full_greeting, size, "%s %s", greeting, name);

  // This line is invalid - we're returning a pointer to a locally defined
  // variable - variable assigned to the stack
  // When this function returns, the stack frame is deallocated, and we're
  // left with a dangling pointer
  // The lifetime of the variable is _only_ within the function
  return full_greeting;
}

// alloc_ or create_ is a convention that makes it clear that we're allocating
// memory to the heap, and that it is up to the caller to free that memory
char *alloc_full_greeting(const char *greeting, const char *name, int size) {
  // naive attempt
  /*char *result = (char *)malloc(size * sizeof(char));*/
  // 1. no need to cast malloc's (void *) here, apparently - can mask when
  //  malloc isn't properly declared
  // 2. size * sizeof(char) is redundant - char is _always_ 1
  char *result = malloc(size);

  if (result == NULL) {
    fprintf(stderr, "Memory allocation failed\n");

    return NULL;
  }

  snprintf(result, size, "%s %s", greeting, name);

  return result;
}
