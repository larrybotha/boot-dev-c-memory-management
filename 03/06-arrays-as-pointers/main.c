#include "../../munit/munit.h"

#include "exercise.h"

MunitResult test_change_cpp_to_python(const MunitParameter params[],
                                      void *user_data_or_fixture) {
  codefile_t orig;
  orig.lines = 100;
  orig.filetype = 1;

  codefile_t result = change_filetype(&orig, 2);

  munit_assert_int(orig.lines, ==, 100);
  munit_assert_int(orig.filetype, ==, 2);

  return MUNIT_OK;
}

MunitResult test_change_same_filetype(const MunitParameter params[],
                                      void *user_data_or_fixture) {
  codefile_t orig;
  orig.lines = 100;
  orig.filetype = 1;

  codefile_t result = change_filetype(&orig, 1);

  munit_assert_int(orig.lines, ==, 100);
  munit_assert_int(orig.filetype, ==, 1);

  return MUNIT_OK;
}

int main(int argc, char *argv[]) {
  MunitTest tests[] = {{
                           "/test_change_cpp_to_python",
                           test_change_cpp_to_python,
                           NULL,
                           NULL,
                           MUNIT_TEST_OPTION_NONE,
                           NULL,
                       },
                       {
                           "/test_change_same_filetype",
                           test_change_same_filetype,
                           NULL,
                           NULL,
                           MUNIT_TEST_OPTION_NONE,
                           NULL,
                       }};

  MunitSuite suite = {
      "/pointer-basics",
      tests,
      NULL,
      1,
      (MunitSuiteOptions)MUNIT_TEST_OPTION_NONE,
  };

  return munit_suite_main(&suite, NULL, argc, (char *const *)argv);
};
