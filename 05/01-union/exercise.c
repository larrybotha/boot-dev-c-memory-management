#include "exercise.h"
#include <stdio.h>

snek_object_t new_integer(int n) {
  return (snek_object_t){
      .data = {.v_int = n},
      .kind = INTEGER,
  };
}

snek_object_t new_string(char *x) {
  return (snek_object_t){
      .data = {.v_string = x},
      .kind = STRING,
  };
}

void format_object(snek_object_t obj, char *buf) {
  switch (obj.kind) {
  case INTEGER:
    sprintf(buf, "int:%d", obj.data.v_int);
    break;
  case STRING:
    sprintf(buf, "string:%s", obj.data.v_string);
    break;
  }
}
