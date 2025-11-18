#include "exercise.h"
#include <stdlib.h>

snekobject_t new_node(char *name) {
  snekobject_t node = {.name = name, .child = NULL};

  return node;
}
