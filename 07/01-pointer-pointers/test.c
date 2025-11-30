#include "../../munit/munit.h"
#include <stdio.h>
#include <stdlib.h>

#include "exercise.h"

MunitResult test_allocate(const MunitParameter params[],
                          void *user_data_or_fixture) {
  int *ptr = NULL;
  int value = 8;
  alloc_int(&ptr, value);

  munit_assert_ptr_not_null(ptr);
  munit_assert_int(*ptr, ==, value);

  free(ptr);

  return MUNIT_OK;
}

MunitResult test_does_not_overwrite(const MunitParameter params[],
                                    void *user_data_or_fixture) {
  int value = 5;
  int *ptr = &value;

  alloc_int(&ptr, 20);

  munit_assert_int(value, ==, 5);

  munit_assert_ptr_not_null(ptr);
  munit_assert_int(*ptr, ==, 20);

  free(ptr);

  return MUNIT_OK;
}

int main(int argc, const char *argv[]) {
  MunitTest tests[] = {
      {
          "/test_allocate",
          test_allocate,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/test_does_not_overwrite",
          test_does_not_overwrite,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
  };

  MunitSuite suite = {
      "pointer-pointers",
      tests,
      NULL,
      1,
      (MunitSuiteOptions)MUNIT_TEST_OPTION_NONE,
  };

  return munit_suite_main(&suite, NULL, argc, (char *const *)argv);
}
