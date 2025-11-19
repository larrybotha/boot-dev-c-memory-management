#include "../../munit/munit.h"
#include <stdio.h>

#include "exercise.h"

MunitResult test_colors(const MunitParameter params[],
                        void *user_data_or_fixture) {
  munit_assert_int(RED, ==, 0);
  munit_assert_int(GREEN, ==, 1);
  munit_assert_int(BLUE, ==, 2);

  return MUNIT_OK;
}

MunitResult test_traffic_light(const MunitParameter params[],
                               void *user_data_or_fixture) {
  traffic_light_t *t = new_traffic_light();

  munit_assert_int(t->state, ==, RED);

  return MUNIT_OK;
}

int main(int argc, const char *argv[]) {
  MunitTest tests[] = {
      {
          "/test_colors",
          test_colors,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/test_traffic_light",
          test_traffic_light,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
  };

  MunitSuite suite = {
      "mutual-structs",
      tests,
      NULL,
      1,
      (MunitSuiteOptions)MUNIT_TEST_OPTION_NONE,
  };

  return munit_suite_main(&suite, NULL, argc, (char *const *)argv);
}
