#pragma once

#include <stdbool.h>

typedef enum SnekObjectKind {
  INTEGER,
  FLOAT,
  BOOL,
} snek_object_kind_t;

typedef struct SnekInt {
  int value;
} snek_int_t;

typedef struct SnekFloat {
  float value;
} snek_float_t;

typedef struct SnekBool {
  unsigned int value;
} snek_bool_t;

void snek_zero_out(void *x, snek_object_kind_t type);
