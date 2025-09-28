#include "../../munit/munit.h"

#include "coordinate.h"

coordinate_t new_coord(int x, int y, int z) {
  return (coordinate_t){.x = x, .y = y, .z = z};
}

MunitResult test_unchanged(const MunitParameter params[],
                           void *user_data_or_fixture) {
  coordinate_t old = new_coord(1, 2, 3);
  munit_assert_int(old.x, ==, 1);

  coordinate_update_x(old, 4);
  munit_assert_int(old.x, ==, 1);

  return MUNIT_OK;
};

MunitResult test_changed(const MunitParameter params[],
                         void *user_data_or_fixture) {
  coordinate_t old = new_coord(1, 2, 3);
  munit_assert_int(old.x, ==, 1);

  coordinate_t new = return_coordinate_update_x(old, 4);
  munit_assert_int(new.x, ==, 4);
  munit_assert_int(old.x, ==, 1);

  // Notice, they have different addresses
  munit_assert_ptr_not_equal(&old, &new);

  return MUNIT_OK;
};

/*
 * Run with:
    just watch 03/05-why-pointers/main.c \
      "03/05-why-pointers/coordinate.c munit/munit.c"
 */
int main(int argc, const char *argv[]) {
  MunitTest tests[] = {
      {
          "/test_unchanged",
          test_unchanged,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/test_changed",
          test_changed,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
  };

  const MunitSuite suite = {
      "/pointers", tests, NULL, 1, (MunitSuiteOptions)MUNIT_TEST_OPTION_NONE,
  };

  return munit_suite_main(&suite, NULL, argc, (char *const *)argv);
}
