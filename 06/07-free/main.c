#include "exercise.h"
#include <stdio.h>
#include <stdlib.h>

void never_free(int num_lists) {
  printf("\nNEVER FREE\n");

  // addresses are never recycled
  for (int i = 0; i < num_lists; i++) {
    const int *xs = alloc_scalar_list(500000, 2);

    if (xs == NULL) {
      fprintf(stderr, "Failed to allocate memory\n");

      exit(1);
    } else {
      printf("Allocated list %d at %p\n", i, xs);
    }
  }
}

void always_free(int num_lists) {
  printf("\nALWAYS FREE\n");

  // addresses are recycled
  for (int i = 0; i < num_lists; i++) {
    int *xs = alloc_scalar_list(500000, 2);

    if (xs == NULL) {
      fprintf(stderr, "Failed to allocate memory\n");

      exit(1);
    } else {
      printf("Allocated list %d at %p\n", i, xs);

      free(xs);
    }
  }
}

int main() {
  never_free(500);  // will consume memory at around 27000 lists
  always_free(500); // will consume memory at around 27000 lists
}
