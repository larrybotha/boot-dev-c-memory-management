#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../../munit/munit.h"
#include "exercise.h"

bool is_on_stack(void *ptr) {
  void *stack_top = __builtin_frame_address(0);
  uintptr_t stack_top_addr = (uintptr_t)stack_top;
  uintptr_t ptr_addr = (uintptr_t)ptr;
  uintptr_t threshold = 1024;

  return ptr_addr >= (stack_top_addr - threshold) &&
         ptr_addr <= (stack_top_addr + threshold);
}

MunitResult test_invalid_greeting_impl(const MunitParameter params[],
                                       void *user_data_or_fixture) {
  char *result = get_full_greeting_invalid("hello", "alice", 20);

  munit_assert_string_equal(result, "hello alice");
  munit_assert_true(is_on_stack(result));

  return MUNIT_OK;
}

MunitResult test_greeting_impl(const MunitParameter params[],
                               void *user_data_or_fixture) {
  char *result = alloc_full_greeting("hello", "alice", 20);

  munit_assert_string_equal(result, "hello alice");
  munit_assert_false(is_on_stack(result));

  free(result);

  return MUNIT_OK;
}

int main(int argc, const char *argv[]) {
  MunitTest tests[] = {
      {
          "/test_invalid_greeting_impl",
          test_invalid_greeting_impl,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/test_greeting_impl",
          test_greeting_impl,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
  };

  MunitSuite suite = {
      "header-helpers",
      tests,
      NULL,
      1,
      (MunitSuiteOptions)MUNIT_TEST_OPTION_NONE,
  };

  return munit_suite_main(&suite, NULL, argc, (char *const *)argv);
}
