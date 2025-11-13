#include <stdio.h>

// struct of integers
typedef struct Graphics {
  int fps;
  int height;
  int width;
} graphics_t;

void dump_graphics_unsafe(graphics_t settings[10]) {
  // cast to an array of integers
  const int *ptr = (int *)settings;

  // iterate over an arbitrary length
  for (int i = 0; i < 20; i++) {
    // once settings is consumed, we start seeing other values in memory
    printf("settings[%d] = %d\n", i, ptr[i]);
  }
}

void dump_graphics(graphics_t settings[10]) {
  // cast to an array of integers
  int *ptr = (int *)settings;
  // get the size of the array
  int len = sizeof(ptr);

  // iterate over a known length
  for (int i = 0; i < len; i++) {
    printf("settings[%d] = %d\n", i, ptr[i]);
  }
}

int main() {
  graphics_t xs[3] = {
      {1, 2, 3},
      {10, 20, 30},
      {100, 200, 300},
  };

  dump_graphics_unsafe(xs);

  printf("\n");

  dump_graphics(xs);
}
