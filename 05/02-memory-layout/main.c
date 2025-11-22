#include "limits.h"
#include <stdio.h>

typedef union {
  int value;
  unsigned int err;
} val_or_err_t;

int main() {
  val_or_err_t value = {
      .value = 5,
  };
  val_or_err_t err = {
      .err = UINT_MAX,
  };

  printf("value.value: %d\n", value.value);
  printf("value.err: %u\n", value.err);
  printf("\n");

  printf("err.value: %d\n", err.value);
  printf("err.err: %u\n", err.err);
}
