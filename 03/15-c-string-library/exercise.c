#include "exercise.h"

const int MAX_BUFFER_SIZE = 64;

int smart_append(TextBuffer *dest, const char *src) {
  if (dest == NULL || src == NULL) {
    return 1;
  }

  const int remaining_space = MAX_BUFFER_SIZE - 1 - dest->length;
  const int src_len = strlen(src);

  if (src_len <= remaining_space) {
    strcat(dest->buffer, src);
    dest->length += src_len;

    return 0;
  } else {
    strncat(dest->buffer, src, remaining_space);
    dest->length = MAX_BUFFER_SIZE - 1;

    return 1;
  }
}
