#include "../../munit/munit.h"
#include "exercise.h"
#include <string.h>

MunitResult test_null_buffer(const MunitParameter params[],
                             void *user_data_or_fixture) {
  TextBuffer dest;
  const char *src = "";
  int result = smart_append(&dest, src);
  munit_assert_int(result, ==, 1);

  return MUNIT_OK;
}

MunitResult test_null_src(const MunitParameter params[],
                          void *user_data_or_fixture) {
  TextBuffer dest;
  strcpy(dest.buffer, "");
  dest.length = 0;

  const char *src = NULL;
  int result = smart_append(&dest, src);
  munit_assert_int(result, ==, 1);

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
  munit_assert_int(dest.length, =, 5);

  return MUNIT_OK;
}

int main(int argc, const char *argv[]) {
  MunitTest tests[] = {{
                           "/test_null_buffer",
                           test_null_buffer,
                           NULL,
                           NULL,
                           MUNIT_TEST_OPTION_NONE,
                           NULL,
                       },
                       {
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
