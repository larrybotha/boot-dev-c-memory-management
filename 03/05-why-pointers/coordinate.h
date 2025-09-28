typedef struct coordinate {
 int x;
 int y;
 int z;
} coordinate_t;

void coordinate_update_x(coordinate_t coord, int new_x);
coordinate_t return_coordinate_update_x(coordinate_t coord, int new_x);
