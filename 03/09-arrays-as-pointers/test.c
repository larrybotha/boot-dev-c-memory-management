#include <stdio.h>

#include "../../munit/munit.h"

MunitResult test_array_as_pointer(const MunitParameter params[],
                                  void *user_data_or_fixture) {
  int xs[5] = {1, 2, 3, 4, 5};
  int *xs_ptr = xs;

  // xs is a pointer to an array
  munit_assert_ptr_equal(xs, xs_ptr);
  // the address of the first value is the same as the pointer to the array
  munit_assert_ptr_equal(&xs[0], xs_ptr);

  return MUNIT_OK;
}

MunitResult test_non_zero_index_pointer(const MunitParameter params[],
                                        void *user_data_or_fixture) {
  int xs[5] = {1, 2, 3, 4, 5};
  int *xs_ptr_a = &xs[2];
  int *xs_ptr_b = xs + 2;

  munit_assert_ptr_equal(&xs[2], xs_ptr_a);
  munit_assert_ptr_equal(xs_ptr_a, xs_ptr_b);
  munit_assert_int((*xs + 2), ==, *xs_ptr_a);

  return MUNIT_OK;
}

int main(int argc, char *argv[]) {
  MunitTest tests[] = {
      {
          "/test_array_as_pointer",
          test_array_as_pointer,
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
