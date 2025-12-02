#include "../../munit/munit.h"
#include "exercise.h"
#include <stdio.h>
#include <stdlib.h>

MunitResult
test_create_token_pointer_array_single(const MunitParameter params[],
                                       void *user_data_or_fixture) {
  token_t token = {"hello", 1, 1};
  token_t **result = create_token_pointer_array(&token, 1);

  munit_assert_not_null(result);
  munit_assert_not_null(result[0]);
  munit_assert_string_equal(result[0]->literal, "hello");
  munit_assert_int(result[0]->line, ==, 1);
  munit_assert_int(result[0]->column, ==, 1);
  munit_assert_ptr_not_equal(result[0], &token);

  free(result[0]);
  free(result);

  return MUNIT_OK;
}

MunitResult
test_create_token_pointer_array_multiple(const MunitParameter params[],
                                         void *user_data_or_fixture) {
  token_t tokens[3] = {
      {"foo1", 1, 1},
      {"foo2", 2, 2},
      {"foo3", 3, 3},
  };
  token_t **result = create_token_pointer_array(tokens, 3);

  munit_assert_not_null(result);

  for (size_t i = 0; i < 3; i++) {
    int line = i + 1;
    int column = line;

    munit_assert_not_null(result[i]);
    munit_assert_string_equal(result[i]->literal, tokens[i].literal);
    munit_assert_int(result[i]->line, ==, line);
    munit_assert_int(result[i]->column, ==, column);
    munit_assert_ptr_not_equal(result[i], &tokens[i]);
  }

  for (size_t i = 0; i < 3; i++) {
    free(result[i]);
  }

  free(result);

  return MUNIT_OK;
}

int main(int argc, char **argv) {
  MunitTest tests[] = {
      {
          "/test_create_token_pointer_array_single",
          test_create_token_pointer_array_single,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/test_create_token_pointer_array_multiple",
          test_create_token_pointer_array_multiple,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
  };

  MunitSuite suite = {
      "pointer-pointers",
      tests,
      NULL,
      1,
      (MunitSuiteOptions)MUNIT_TEST_OPTION_NONE,
  };

  return munit_suite_main(&suite, NULL, argc, (char *const *)argv);
}
