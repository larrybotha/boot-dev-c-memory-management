#include <stdio.h>

typedef enum {
  HTTP_OK = 200,
} http_status_t;

typedef enum {
  BIG = 123412341234,
} big_t;

int main() {
  printf("HTTP_OK:                %d\n", HTTP_OK);
  printf("sizeof(HTTP_OK):        %zu\n", sizeof(HTTP_OK));
  printf("sizeof(int):            %zu\n", sizeof(int));
  printf("\n");
  printf("BIG:                    %lu\n", (unsigned long)BIG);
  printf("sizeof(BIG):            %zu\n", sizeof(BIG));
  printf("sizeof(unsigned long):  %zu\n", sizeof(unsigned long));
}
