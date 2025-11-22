#include "../../munit/munit.h"

#include "exercise.h"

MunitResult test_formats_int1(const MunitParameter params[],
                              void *user_data_or_fixture) {
  char buffer[100];
  snek_object_t i = new_integer(5);

  format_object(i, buffer);

  munit_assert_string_equal(buffer, "int:5");

  return MUNIT_OK;
}

MunitResult test_formats_string1(const MunitParameter params[],
                                 void *user_data_or_fixture) {
  char buffer[100];
  snek_object_t i = new_string("foo");

  format_object(i, buffer);

  munit_assert_string_equal(buffer, "string:foo");

  return MUNIT_OK;
}

MunitResult test_formats_string2(const MunitParameter params[],
                                 void *user_data_or_fixture) {
  char buffer[100];
  snek_object_t i = new_string("foo bar");

  format_object(i, buffer);

  munit_assert_string_equal(buffer, "string:foo bar");

  return MUNIT_OK;
}

int main(int argc, char *argv[]) {
  MunitTest tests[] = {
      {
          "/test_formats_int1",
          test_formats_int1,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/test_formats_string1",
          test_formats_string1,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/test_formats_string2",
          test_formats_string2,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
  };

  MunitSuite suite = {
      "non-default-enum-values",
      tests,
      NULL,
      1,
      (MunitSuiteOptions)MUNIT_TEST_OPTION_NONE,
  };

  return munit_suite_main(&suite, NULL, argc, (char *const *)argv);
}
