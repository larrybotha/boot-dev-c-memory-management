#include "../../munit/munit.h"

#include "exercise.h"

MunitResult test_http_to_str(const MunitParameter params[],
                             void *user_data_or_fixture) {

  munit_assert_string_equal(http_to_str(HTTP_NOT_FOUND), "404 Not found");
  munit_assert_string_equal(http_to_str(HTTP_IM_A_TEAPOT), "218 I'm a teapot");
  munit_assert_string_equal(http_to_str(HTTP_OK), "200 Ok");
  munit_assert_null(http_to_str(0));

  return MUNIT_OK;
}

int main(int argc, const char *argv[]) {

  MunitTest tests[] = {{
      "/test_http_to_str",
      test_http_to_str,
      NULL,
      NULL,
      MUNIT_TEST_OPTION_NONE,
      NULL,
  }};

  MunitSuite suite = {
      "non-default-enum-values",
      tests,
      NULL,
      1,
      (MunitSuiteOptions)MUNIT_TEST_OPTION_NONE,
  };

  return munit_suite_main(&suite, NULL, argc, (char *const *)argv);
}
