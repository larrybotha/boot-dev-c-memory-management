#include "../../munit/munit.h"

#include "exercise.h"

MunitResult test_concat_empty_strings(const MunitParameter params[],
                                      void *user_data_or_fixture) {
  char x1[100] = "";
  const char *x2 = "";

  concat_strings(x1, x2);

  munit_assert_string_equal(x1, "");

  return MUNIT_OK;
}

MunitResult test_concat_empty_to_nonempty(const MunitParameter params[],
                                          void *user_data_or_fixture) {
  char x1[100] = "foo";
  const char *x2 = "";

  concat_strings(x1, x2);

  munit_assert_string_equal(x1, "foo");

  return MUNIT_OK;
}

MunitResult test_concat_nonempty_to_empty(const MunitParameter params[],
                                          void *user_data_or_fixture) {
  char x1[100] = "";
  const char *x2 = "foo";

  concat_strings(x1, x2);

  munit_assert_string_equal(x1, "foo");

  return MUNIT_OK;
}

MunitResult test_concat_small_strings(const MunitParameter params[],
                                      void *user_data_or_fixture) {
  char x1[100] = "foo";
  const char *x2 = "bar";

  concat_strings(x1, x2);

  munit_assert_string_equal(x1, "foobar");

  return MUNIT_OK;
}

MunitResult test_concat_long_strings(const MunitParameter params[],
                                     void *user_data_or_fixture) {
  char str1[200] = "This is a longer string that ";
  const char *str2 = "will be concatenated with another long string.";
  concat_strings(str1, str2);
  munit_assert_string_equal(str1, strcat(str1, str2));

  return MUNIT_OK;
}

int main(int argc, const char *argv[]) {
  MunitTest tests[] = {
      {
          "/test_concat_empty_strings",
          test_concat_empty_strings,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/test_concat_empty_to_nonempty",
          test_concat_empty_to_nonempty,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/test_concat_small_strings",
          test_concat_small_strings,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/test_concat_long_strings",
          test_concat_long_strings,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
  };

  MunitSuite suite = {
      "c-strings", tests, NULL, 1, (MunitSuiteOptions)MUNIT_TEST_OPTION_NONE,
  };

  return munit_suite_main(&suite, NULL, argc, (char *const *)argv);
}
