#include "../../munit/munit.h"

#include "exercise.h"

MunitResult test_http_status_codes(const MunitParameter params[],
                                   void *user_data_or_fixture) {
  munit_assert_int(HTTP_OK, ==, 200);
  munit_assert_int(HTTP_CREATED, ==, 201);
  munit_assert_int(HTTP_IM_A_TEAPOT, ==, 218);
  munit_assert_int(HTTP_BAD_REQUEST, ==, 400);
  munit_assert_int(HTTP_UNAUTHORISED, ==, 401);
  munit_assert_int(HTTP_PAYMENT_REQUIRED, ==, 402);
  munit_assert_int(HTTP_FORBIDDEN, ==, 403);
  munit_assert_int(HTTP_NOT_FOUND, ==, 404);

  return MUNIT_OK;
}

int main(int argc, const char *argv[]) {
  MunitTest tests[] = {
      {
          "/test_http_status_codes",
          test_http_status_codes,
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
