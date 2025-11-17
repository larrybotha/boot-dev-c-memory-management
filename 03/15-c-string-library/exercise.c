#include "exercise.h"

const int MAX_BUFFER_SIZE = 64;

int smart_append(TextBuffer *dest, const char *src) {
  if (dest == NULL) {
    return 1;
  }

  if (src == NULL) {
    return 1;
  }

  const int remaining_space = MAX_BUFFER_SIZE - dest->length;

  return 0;
}
