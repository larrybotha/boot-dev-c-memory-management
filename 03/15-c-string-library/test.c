#include "../../munit/munit.h"
#include "exercise.h"
#include <stdio.h>
#include <string.h>

MunitResult test_null_src(const MunitParameter params[],
                          void *user_data_or_fixture) {
  TextBuffer dest;
  strcpy(dest.buffer, "");
  dest.length = 0;

  const char *src = NULL;
  int result = smart_append(&dest, src);
  munit_assert_int(result, ==, 1);
  munit_assert_int(dest.length, ==, 0);

  return MUNIT_OK;
}

MunitResult test_smart_append_empty_buffer(const MunitParameter params[],
                                           void *user_data_or_fixture) {
  TextBuffer dest;
  strcpy(dest.buffer, "");
  dest.length = 0;

  const char *src = "hello";
  int result = smart_append(&dest, src);
  munit_assert_int(result, ==, 0);
  munit_assert_string_equal(dest.buffer, "hello");
  munit_assert_int(dest.length, ==, 5);

  return MUNIT_OK;
}

MunitResult test_smart_append_full_buffer(const MunitParameter params[],
                                          void *user_data_or_fixture) {
  TextBuffer dest;
  strcpy(dest.buffer,
         "This is a very long string that will fill up the entire buffer.");
  dest.length = 63;

  const char *src = " foo";
  int result = smart_append(&dest, src);

  munit_assert_int(result, ==, 1);
  munit_assert_string_equal(
      dest.buffer,
      "This is a very long string that will fill up the entire buffer.");
  munit_assert_int(dest.length, ==, 63);

  return MUNIT_OK;
}

MunitResult test_smart_append_overflow(const MunitParameter params[],
                                       void *user_data_or_fixture) {
  TextBuffer dest;
  strcpy(dest.buffer, "This is a long string");
  dest.length = 21;
  const char *src = " that will fill the whole buffer and leave no space for "
                    "some of the chars.";
  int result = smart_append(&dest, src);

  munit_assert_int(result, ==, 1);
  munit_assert_string_equal(
      dest.buffer,
      "This is a long string that will fill the whole buffer and leave");
  munit_assert_int(dest.length, ==, 63);

  return MUNIT_OK;
}

int main(int argc, const char *argv[]) {
  MunitTest tests[] = {{
                           "/test_null_src",
                           test_null_src,
                           NULL,
                           NULL,
                           MUNIT_TEST_OPTION_NONE,
                           NULL,
                       },
                       {
                           "/test_smart_append_empty_buffer",
                           test_smart_append_empty_buffer,
                           NULL,
                           NULL,
                           MUNIT_TEST_OPTION_NONE,
                           NULL,
                       },
                       {
                           "/test_smart_append_full_buffer",
                           test_smart_append_full_buffer,
                           NULL,
                           NULL,
                           MUNIT_TEST_OPTION_NONE,
                           NULL,
                       },
                       {
                           "/test_smart_append_overflow",
                           test_smart_append_overflow,
                           NULL,
                           NULL,
                           MUNIT_TEST_OPTION_NONE,
                           NULL,
                       }};

  MunitSuite suite = {
      "c-string-library",
      tests,
      NULL,
      1,
      (MunitSuiteOptions)MUNIT_TEST_OPTION_NONE,
  };

  return munit_suite_main(&suite, NULL, argc, (char *const *)argv);
}
