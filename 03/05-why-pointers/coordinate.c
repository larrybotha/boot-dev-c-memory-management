#include "coordinate.h"

void coordinate_update_x(coordinate_t coord, int new_x) { coord.x = new_x; }

coordinate_t return_coordinate_update_x(coordinate_t coord, int new_x) {
  coord.x = new_x;

  return coord;
}
