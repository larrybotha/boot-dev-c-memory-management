#include "../../munit/munit.h"
#include "exercise.h"

MunitResult test_swap_integers() {
  int a = 5;
  int b = 6;

  swap(&a, &b, sizeof(int));

  munit_assert_int(a, ==, 6);
  munit_assert_int(b, ==, 5);

  return MUNIT_OK;
}

MunitResult test_swap_strings() {
  char *a = "foo";
  char *b = "bar";

  swap(&a, &b, strlen(a));

  munit_assert_string_equal(a, "bar");
  munit_assert_string_equal(b, "foo");

  return MUNIT_OK;
}

MunitResult test_swap_same() {
  char *a = "foo";
  int x = 42;

  swap(&a, &a, strlen(a));
  swap(&x, &x, sizeof(int));

  munit_assert_string_equal(a, "foo");
  munit_assert_int(x, ==, 42);

  return MUNIT_OK;
}

MunitResult test_swap_via_stack_integers() {
  int a = 5;
  int b = 6;

  swap_via_stack(&a, &b, sizeof(int));

  munit_assert_int(a, ==, 6);
  munit_assert_int(b, ==, 5);

  return MUNIT_OK;
}

MunitResult test_swap_via_stack_strings() {
  char *a = "foo";
  char *b = "bar";

  swap_via_stack(&a, &b, strlen(a));

  munit_assert_string_equal(a, "bar");
  munit_assert_string_equal(b, "foo");

  return MUNIT_OK;
}

MunitResult test_swap_via_stack_same() {
  char *a = "foo";
  int x = 42;

  swap_via_stack(&a, &a, strlen(a));
  swap_via_stack(&x, &x, sizeof(int));

  munit_assert_string_equal(a, "foo");
  munit_assert_int(x, ==, 42);

  return MUNIT_OK;
}

int main(int argc, char **argv) {
  MunitTest tests[] = {
      {
          "/test_swap_integers",
          test_swap_integers,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/test_swap_strings",
          test_swap_strings,
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
      {
          "/test_swap_via_stack_integers",
          test_swap_via_stack_integers,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/test_swap_via_stack_strings",
          test_swap_via_stack_strings,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/test_swap_via_stack_same",
          test_swap_via_stack_same,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
  };

  MunitSuite suite = {
      "generic-swap", tests, NULL, 1, (MunitSuiteOptions)MUNIT_TEST_OPTION_NONE,
  };

  return munit_suite_main(&suite, NULL, argc, (char *const *)argv);
}
