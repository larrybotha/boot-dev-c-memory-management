#include <assert.h>
#include <string.h>

int main() {
  int x = 5;
  int y = 6;
  int *ptr_y = &y;

  memcpy(&x, ptr_y, sizeof(int));

  assert(x == 6 && "x is 6");
}
