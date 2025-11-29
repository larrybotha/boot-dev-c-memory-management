#include <stdio.h>

void do_snek(int pool_size) {
  printf("Size of pool: %d\n", pool_size);

  char snek_pool[pool_size];

  snek_pool[0] = 's';
  snek_pool[1] = 'n';
  snek_pool[2] = 'e';
  snek_pool[3] = 'k';
  snek_pool[4] = '\0';

  printf("Initial string: %s\n\n", snek_pool);
}

int main() {
  // will run when compiled with either gcc or zig - 7Mb < $(ulimit -s)
  do_snek(1024 * 1024 * 7);

  // will segfault when compiled with gcc, but not zig
  do_snek(1024 * 1024 * 10);

  // will segfault when compiled with zig
  do_snek(1024 * 1024 * 70);

  return 0;
}
