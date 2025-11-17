#include <assert.h>
#include <stdio.h>

// arrays decay to pointers when passed as values to functions
/*void some_func(const int xs[]) {*/
void some_func(const int *xs // this more accurately describes the array
                             // decaying to a pointer
) {
  printf("-----------------------------------------\n");
  printf("after decaying when passed into function:\n");
  printf("-----------------------------------------\n");

  printf("*xs:        %d\n", *xs);
  // size of the _pointer_ to xs
  printf("sizeof(xs): %zu (size of pointer!)\n\n", sizeof(xs));

  printf("xs:         %p\n", xs);
  printf("&xs:        %p (address of pointer!)\n", &xs);
  printf("&xs[0]:     %p\n", &xs[0]);
}

int main() {
  int xs[] = {43, 67, 89, 92, 71, 43, 85};
  int len = sizeof(xs) / sizeof(xs[0]);

  printf("len of xs:     %d\n", len);
  printf("sizeof(xs[0]): %zu\n", sizeof(xs[0]));
  // xs does not decay when passed to sizeof, otherwise we'd get the
  // size of the pointer
  printf("sizeof(xs):    %zu (i.e. len(xs) * size(xs[0]))\n", sizeof(xs));
  printf("*xs:           %d\n", *xs);
  printf("xs[0]:         %d\n", xs[0]);

  printf("\n");

  // address at index is same whether via & operator or pointer arithmetic
  for (int i = 0; i < len; i++) {
    printf("&xs[%d] == (xs + %d) == %p\n", i, i, &xs[i]);
    assert(&xs[i] == (xs + i));
  }

  printf("\n");

  // xs decays to a pointer, as if we used xs&
  printf("xs:            %p (xs points to 1st element in array)\n", xs);
  printf("&xs:           %p (explicit address of array)\n", &xs);

  printf("\narray address is the same as &xs[0]:\n");

  printf("xs:            %p (array address)\n", xs);
  printf("(&xs + 0):     %p (with pointer arithmetic)\n", (&xs + 0));

  printf("\nbut array arithmetic gt 0 shows that xs is not the same pointer as "
         "&xs[0]\n");
  printf("(&xs + 1):     %p (address _after_ array)\n", (&xs + 1));
  printf("&xs[1]:        %p (address at xs[1])\n", &xs[1]);

  printf("\n");

  // array points to same address as index 0
  assert((void *)xs == (void *)&xs[0]);
  // memory address _after_ array is not the same as index 1
  assert((void *)(&xs + 1) != (void *)&xs[1]);

  // xs decays to a pointer here
  some_func(xs);
  return 0;
}
