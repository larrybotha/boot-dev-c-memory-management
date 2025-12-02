#include "exercise.h"

void swap_ints(int *x, int *y) {
  if (!x || !y) {
    return;
  }

  int tmp = *x;

  *x = *y;
  *y = tmp;
}
