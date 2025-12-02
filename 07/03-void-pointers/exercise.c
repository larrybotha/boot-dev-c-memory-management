#include "exercise.h"
#include <stdlib.h>

void snek_zero_out(void *x, snek_object_kind_t type) {
  // handle potentially NULL pointers
  if (x == NULL) {
    return;
  }

  switch (type) {
  case INTEGER: {
    snek_int_t *v = (snek_int_t *)x;
    v->value = 0;
    break;
  }
  case FLOAT: {
    snek_float_t *v = (snek_float_t *)x;
    v->value = 0.0;
    break;
  }
  case BOOL: {
    snek_bool_t *v = (snek_bool_t *)x;
    v->value = 0;
    break;
  }
  default:
    // handle unexpected types
    break;
  }
}
