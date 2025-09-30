#include <stdio.h>

// arrays decay to pointers when passed as values to functions
void some_func(int xs_as_arg[]) {
  printf("xs as arg to func:\n");
  printf("&xs_as_arg: %p\n",
         &xs_as_arg);                   // address of the _pointer_ to xs_as_arg
  printf("xs_as_arg: %p\n", xs_as_arg); // address of xs_as_arg

  // size of the _pointer_ to xs_as_arg
  printf("sizeof xs_as_arg in some_func: %zu\n", sizeof(*xs_as_arg));
}

int main() {
  int xs[] = {43, 67, 89, 92, 71, 43, 56, 12};
  int len = sizeof(xs) / sizeof(xs[0]);

  // xs decays to a pointer, as if we used xs&
  printf("&xs: %p\n", &xs);
  printf("xs: %p\n", xs);

  // xs does not decay when passed to sizeof, otherwise we'd get the
  // size of the pointer
  printf("sizeof of xs: %zu\n", sizeof(xs));
  printf("len of xs: %d\n", len);

  printf("\n");

  // xs decays to a pointer here
  some_func(xs);

  return 0;
}
