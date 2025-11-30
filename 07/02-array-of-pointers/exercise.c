#include "exercise.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

token_t **create_token_pointer_array(const token_t *tokens, size_t count) {
  /*token_t **xs = calloc(count, sizeof(token_t *));*/
  token_t **xs = calloc(count, sizeof(*xs));

  if (xs == NULL) {
    return NULL;
  }

  for (size_t i = 0; i < count; i++) {
    // allocate space for token on heap
    /*xs[i] = malloc(sizeof(token_t));*/
    xs[i] = malloc(sizeof(*xs[i]));

    // unwind the allocations if memory cannot be allocated
    if (xs[i] == NULL) {
      for (size_t j = 0; j < i; j++) {
        free(xs[j]);
        free(xs);
      }

      return NULL;
    }

    /**xs[i] = (token_t){*/
    /*    .literal = tokens[i].literal,*/
    /*    .line = tokens[i].line,*/
    /*    .column = tokens[i].column,*/
    /*};*/
    *xs[i] = tokens[i];
  }

  return xs;
}
