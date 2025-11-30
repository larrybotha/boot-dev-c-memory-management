#include "../../munit/munit.h"
#include <stdlib.h>

#include "exercise.h"

MunitResult test_allocate_scalar_array_size(const MunitParameter params[],
                                            void *user_data_or_fixture) {
  int size = 5;
  int multiplier = 2;
  int *result = alloc_scalar_array(size, multiplier);

  munit_assert_not_null(result);

  free(result);

  return MUNIT_OK;
}

MunitResult test_allocate_scalar_zero_multiplier(const MunitParameter params[],
                                                 void *user_data_or_fixture) {
  int size = 5;
  int multiplier = 0;
  int *result = alloc_scalar_array(size, multiplier);

  for (int i = 0; i < size; i++) {
    munit_assert_int(result[i], ==, 0);
  }

  free(result);

  return MUNIT_OK;
}

MunitResult test_allocate_scalar_array_values(const MunitParameter params[],
                                              void *user_data_or_fixture) {
  int size = 5;
  int multiplier = 2;
  int *result = alloc_scalar_array(size, multiplier);

  const int expect[5] = {0, 2, 4, 6, 8};

  for (int i = 0; i < size; i++) {
    munit_assert_int(result[i], ==, expect[i]);
  }

  free(result);

  return MUNIT_OK;
}

int main(int argc, const char *argv[]) {
  MunitTest tests[] = {
      {
          "/test_allocate_scalar_array_size",
          test_allocate_scalar_array_size,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/test_allocate_scalar_zero_multiplier",
          test_allocate_scalar_zero_multiplier,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/test_allocate_scalar_array_values",
          test_allocate_scalar_array_values,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
  };

  MunitSuite suite = {
      "malloc", tests, NULL, 1, (MunitSuiteOptions)MUNIT_TEST_OPTION_NONE,
  };

  return munit_suite_main(&suite, NULL, argc, (char *const *)argv);
}
