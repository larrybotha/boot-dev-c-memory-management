#include <stdio.h>

#include "exercise.h"

int main() {
  printMessageOne();

  return 0;
}

void printMessageOne() {
  const char *message = "Dark mode?\n";
  printStackPointerDiff();
  printf("%s\n", message);
  printMessageTwo();
  printStackPointerDiff();
}

void printMessageTwo() {
  const char *message = "More like...\n";
  printStackPointerDiff();
  printf("%s\n", message);
  printMessageThree();
  printStackPointerDiff();
}

void printMessageThree() {
  const char *message = "dark roast.\n";
  printStackPointerDiff();
  printf("%s\n", message);
  printStackPointerDiff();
}

void printStackPointerDiff() {
  static void *last_sp = NULL;
  void *current_sp;
  current_sp = __builtin_frame_address(0);
  long diff = (char *)last_sp - (char *)current_sp;

  if (last_sp == NULL) {
    last_sp = current_sp;
    diff = 0;
  }

  printf("--------------------------------------\n");
  printf("stack pointer offset: %ld bytes\n", diff);
  printf("last_sp:    %p \n", last_sp);
  printf("current_sp: %p \n", current_sp);
  printf("--------------------------------------\n");
}
