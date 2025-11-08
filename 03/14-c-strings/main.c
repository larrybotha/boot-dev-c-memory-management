#include <stdio.h>
#include <string.h>

int main() {
  char str1[100] = "foo";

  printf("length str1: %zu\n", strlen(str1));
  printf("sizeof str1: %zu\n", sizeof(str1));
}
