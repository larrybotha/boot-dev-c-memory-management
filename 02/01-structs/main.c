#include "../../munit/munit.h"

#include "coord.h"

MunitResult test_new_coord(const MunitParameter params[],
                           void *user_data_or_fixture) {
  struct Coordinate c;

  c.x = 1;
  c.y = 2;
  c.z = 3;

  munit_assert_int(c.x, ==, 1);
  munit_assert_int(c.y, ==, 2);
  munit_assert_int(c.z, ==, 3);

  return MUNIT_OK;
}

int main(int argc, const char *argv[]) {
  MunitTest tests[] = {{
      "/test_new_coord",
      test_new_coord,
      NULL,
      NULL,
      MUNIT_TEST_OPTION_NONE,
      NULL,
  }};

  MunitSuite suite = {
      "/structs", tests, NULL, 1, (MunitSuiteOptions)MUNIT_TEST_OPTION_NONE,

  };

  return munit_suite_main(&suite, NULL, argc, (char *const *)argv);
}
