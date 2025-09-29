#include <stdio.h>

// struct of integers
typedef struct Graphics {
  int fps;
  int height;
  int width;
} graphics_t;

void dump_graphis_unsafe(graphics_t settings[10]) {
  // cast to an array of integers
  int *ptr = (int *)settings;

  for (int i = 0; i < 20; i++) {
    printf("settings[%d] = %d\n", i, ptr[i]);
  }
}

void dump_graphis(graphics_t settings[10]) {
  int *ptr = (int *)settings;
  int len = sizeof(ptr);

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

  dump_graphis_unsafe(xs);

  printf("\n");

  dump_graphis(xs);
}
