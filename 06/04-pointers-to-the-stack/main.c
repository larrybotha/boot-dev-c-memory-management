#include <stdio.h>

typedef struct {
  int x;
  int y;
} coord_t;

coord_t *invalid_new_coord(int x, int y) {
  coord_t coord = {
      .x = x,
      .y = y,
  };

  // Returning a pointer to a value results in undefined behaviour.
  // This is because the value it points to is allocated on the
  // stack within the function call's stack frame - once the function
  // has been executed, the frame is popped off of the stack, and the
  // value is deallocated
  // We end up returning a pointer to a location in memory that no longer
  // has memory that we intended for it to point to
  printf("coord address in stack frame: %p\n", &coord);
  return &coord;
}

coord_t new_coord(int x, int y) {
  coord_t coord = {
      .x = x,
      .y = y,
  };

  // instead of returning a pointer, we force the compiler to copy this
  // value to the calling function's stack frame
  printf("coord address in stack frame: %p\n", &coord);
  return coord;
}

int main() {
  coord_t *ic1 = invalid_new_coord(10, 20);
  coord_t *ic2 = invalid_new_coord(30, 40);
  coord_t *ic3 = invalid_new_coord(50, 60);

  printf("invalid c1: %d, %d\n", ic1->x, ic1->y);
  printf("invalid c2: %d, %d\n", ic2->x, ic2->y); // prints garbage
  printf("invalid c3: %d, %d\n", ic3->x, ic3->y); // prints garbage

  printf("\n");

  coord_t c1 = new_coord(10, 20);
  coord_t c2 = new_coord(30, 40);
  coord_t c3 = new_coord(50, 60);

  printf("c1: (%d, %d)               at %p\n", c1.x, c1.y, &c1);
  printf("c2: (%d, %d)               at %p\n", c2.x, c2.y, &c2);
  printf("c3: (%d, %d)               at %p\n", c3.x, c3.y, &c3);
}
