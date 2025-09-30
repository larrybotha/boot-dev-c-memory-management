#include <stdbool.h>

#include "exercise.h"

void concat_strings(char *str1, const char *str2) {
  int size_str1 = sizeof(str1);
  int size_str2 = sizeof(str2);
  int null_index = size_str1 + 1;

  for (int i = 0; i < size_str1; i++) {
    if (str1[i] == '\0') {
      null_index = i;
      break;
    }
  }

  for (int i = 0; i < size_str1; i++) {
    if (i > size_str2) {
      break;
    }

    if (null_index + 1 > size_str1) {
      break;
    }

    str1[null_index + i] = str2[i];

    if (str2[i] == '\0' || null_index + 1 == size_str1) {
      str1[null_index + i] = '\0';
      break;
    }
  }
}
