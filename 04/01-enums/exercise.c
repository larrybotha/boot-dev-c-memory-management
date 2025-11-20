#include "exercise.h"
#include <stdlib.h>

traffic_light_t *new_traffic_light() {
  traffic_light_t *t = malloc(sizeof(traffic_light_t));

  t->state = RED;

  return t;
}
