#include "../../munit/munit.h"
#include "exercise.h"

MunitResult test_swapping_strings() {
  char *a = "foo";
  char *b = "bar";

  swap_strings(&a, &b);

  munit_assert_string_equal(a, "bar");
  munit_assert_string_equal(b, "foo");

  return MUNIT_OK;
}

MunitResult test_swap_same() {
  char *a = "foo";

  swap_strings(&a, &a);

  munit_assert_string_equal(a, "foo");

  return MUNIT_OK;
}

int main(int argc, char **argv) {
  MunitTest tests[] = {
      {
          "/test_swapping_strings",
          test_swapping_strings,
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
      "swapping-strings",
      tests,
      NULL,
      1,
      (MunitSuiteOptions)MUNIT_TEST_OPTION_NONE,
  };

  return munit_suite_main(&suite, NULL, argc, (char *const *)argv);
}
