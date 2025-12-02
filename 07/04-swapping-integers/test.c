#include "../../munit/munit.h"
#include "exercise.h"

MunitResult test_swapping_integers() {
  int x = 5;
  int y = 6;

  swap_ints(&x, &y);

  munit_assert_int(x, ==, 6);
  munit_assert_int(y, ==, 5);

  return MUNIT_OK;
}

MunitResult test_swap_same() {
  int x = 5;

  swap_ints(&x, &x);

  munit_assert_int(x, ==, 5);

  return MUNIT_OK;
}

int main(int argc, char **argv) {
  MunitTest tests[] = {
      {
          "/test_swapping_integers",
          test_swapping_integers,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/test_swap_same",
          test_swap_same,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
  };

  MunitSuite suite = {
      "swapping-integers",
      tests,
      NULL,
      1,
      (MunitSuiteOptions)MUNIT_TEST_OPTION_NONE,
  };

  return munit_suite_main(&suite, NULL, argc, (char *const *)argv);
}
