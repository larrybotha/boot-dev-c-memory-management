#include <stdio.h>

#include "../../munit/munit.h"

MunitResult test_change_cpp_to_python(const MunitParameter params[],
                                      void *user_data_or_fixture) {
  int xs[5] = {1, 2, 3, 4, 5};
  int *xs_ptr = xs;

  printf("xs: %p\n", xs);
  printf("xs_ptr: %p\n", xs_ptr);
  /*munit_assert_int(xs, ==, xs_ptr);*/

  return MUNIT_OK;
}

int main(int argc, char *argv[]) {
  MunitTest tests[] = {
      {
          "/test_change_cpp_to_python",
          test_change_cpp_to_python,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
  };

  MunitSuite suite = {
      "/arrays-as-pointers",
      tests,
      NULL,
      1,
      (MunitSuiteOptions)MUNIT_TEST_OPTION_NONE,
  };

  return munit_suite_main(&suite, NULL, argc, (char *const *)argv);
};
