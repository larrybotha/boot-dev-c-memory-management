#include <stdio.h>
#include <string.h>

int main() {
  const char *x = "foo";
  const char *y = "bar";

  // Create a buffer on the stack that is large enough to hold the
  // concatenated string.
  // "foo" is 3 chars, "bar" is 3 chars, and we need 1 for the null terminator.
  char xy[strlen(x) + strlen(y) + 1];

  strcpy(xy, x);
  strcat(xy, y);

  printf("x:  %s\n", x);
  printf("y:  %s\n", y);
  printf("xy: %s\n", xy);

  printf("\n");

  // strcmp returns:
  // < 0 if the first non-matching char in x is lower than y.
  // > 0 if the first non-matching char in x is greater than y.
  // = 0 if the strings are equal.
  printf("strcmp(x, y): %d\n", strcmp(x, y));
  printf("strcmp(y, x): %d\n", strcmp(y, x));

  printf("\n");

  printf("strchr(x, 'o'): %s\n", strchr(x, 'o'));
  printf("strchr(y, 'b'): %s\n", strchr(y, 'a'));

  printf("\n");

  printf("strstr(xy, 'oob'): %s\n", strstr(xy, "oob"));

  return 0;
}
