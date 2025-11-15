#include <stdio.h>

// arrays decay to pointers when passed as values to functions
/*void some_func(const int xs[]) {*/
void some_func(const int *xs // this more accurately describes the array
                             // decaying to a pointer
) {
  printf("xs as arg to func:\n\n");

  printf("*xs:        %d\n\n", *xs);

  printf("xs:         %p\n", xs);
  printf("&xs:        %p (address of pointer!)\n", &xs);
  printf("&xs[0]:     %p\n", &xs[0]);

  // size of the _pointer_ to xs
  printf("sizeof(xs): %zu (size of pointer!)\n", sizeof(xs));
}

int main() {
  int xs[] = {43, 67, 89, 92, 71, 43, 85};
  int len = sizeof(xs) / sizeof(xs[0]);

  printf("len of xs:     %d\n", len);
  printf("sizeof(xs[0]): %zu\n", sizeof(xs[0]));
  printf("*xs:           %d\n", *xs);
  printf("xs[0]:         %d\n", xs[0]);

  printf("\nxs where defined:\n\n");

  // xs decays to a pointer, as if we used xs&
  printf("xs:            %p\n", xs);
  printf("&xs:           %p\n", &xs);
  printf("&xs[0]:        %p\n", &xs[0]);

  // xs does not decay when passed to sizeof, otherwise we'd get the
  // size of the pointer
  printf("sizeof(xs):    %zu (i.e. len(xs) * size(xs[0]))\n", sizeof(xs));

  printf("\n");

  // xs decays to a pointer here
  some_func(xs);

  return 0;
}
