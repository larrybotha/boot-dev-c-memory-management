#include "../../munit/munit.h"
#include <stdbool.h>

#include "exercise.h"

MunitResult test_null_pointer() {
  snek_zero_out(NULL, 0);

  return MUNIT_OK;
}

MunitResult test_zero_out_integer() {
  snek_int_t integer;
  integer.value = 42;
  snek_zero_out(&integer, INTEGER);

  munit_assert_int(integer.value, ==, 0);

  return MUNIT_OK;
}

MunitResult test_zero_out_float() {
  snek_float_t x;
  x.value = 1.0;

  snek_zero_out(&x, FLOAT);

  munit_assert_float(x.value, ==, 0.0);

  return MUNIT_OK;
}

MunitResult test_zero_out_bool() {
  snek_bool_t x;
  x.value = 1;

  snek_zero_out(&x, BOOL);

  munit_assert_int(x.value, ==, 0);

  return MUNIT_OK;
}

MunitResult test_zero_out_nonzero_values() {
  snek_int_t i;
  snek_float_t f;
  snek_bool_t b;

  i.value = -1;
  f.value = -1.0;
  b.value = 255;

  snek_zero_out(&i, INTEGER);
  snek_zero_out(&f, FLOAT);
  snek_zero_out(&b, BOOL);

  munit_assert_int(i.value, ==, 0);
  munit_assert_float(f.value, ==, 0.0);
  munit_assert_int(b.value, ==, 0.0);

  return MUNIT_OK;
}

int main(int argc, char **argv) {
  MunitTest tests[] = {
      {
          "/test_null_pointer",
          test_null_pointer,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/test_zero_out_integer",
          test_zero_out_integer,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/test_zero_out_float",
          test_zero_out_float,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/test_zero_out_bool",
          test_zero_out_bool,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/test_zero_out_nonzero_values",
          test_zero_out_nonzero_values,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
  };

  MunitSuite suite = {
      "void-pointers",
      tests,
      NULL,
      1,
      (MunitSuiteOptions)MUNIT_TEST_OPTION_NONE,
  };

  return munit_suite_main(&suite, NULL, argc, (char *const *)argv);
}
