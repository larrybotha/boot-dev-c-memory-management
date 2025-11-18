#include "../../munit/munit.h"
#include "exercise.h"
#include <string.h>

MunitResult test_new_node_simple(const MunitParameter params[],
                                 void *user_data_or_fixture) {
  snekobject_t node = new_node("root");
  munit_assert_string_equal(node.name, "root");
  munit_assert_null(node.child);

  return MUNIT_OK;
}

MunitResult test_new_node_empty(const MunitParameter params[],
                                void *user_data_or_fixture) {
  snekobject_t node = new_node("");
  munit_assert_string_equal(node.name, "");
  munit_assert_null(node.child);

  return MUNIT_OK;
}

MunitResult test_new_node_with_child(const MunitParameter params[],
                                     void *user_data_or_fixture) {
  snekobject_t parent = new_node("parent");
  snekobject_t child = new_node("child");

  parent.child = &child;

  munit_assert_not_null(parent.child);
  munit_assert_null(parent.child->child);
  munit_assert_string_equal(parent.child->name, "child");

  return MUNIT_OK;
}

int main(int argc, const char *argv[]) {
  MunitTest tests[] = {

      {
          "/test_new_node_simple",
          test_new_node_simple,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/test_new_node_empty",
          test_new_node_empty,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/test_new_node_with_child",
          test_new_node_with_child,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
  };

  MunitSuite suite = {
      "forward-declarations",
      tests,
      NULL,
      1,
      (MunitSuiteOptions)MUNIT_TEST_OPTION_NONE,
  };

  return munit_suite_main(&suite, NULL, argc, (char *const *)argv);
}
