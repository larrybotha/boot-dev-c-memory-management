#include "../../munit/munit.h"
#include <stdio.h>

#include "snekstack.h"

MunitResult test_free_stack() {
  snek_stack_t *result = alloc_stack(1);

  munit_assert_ptr_not_null(result);

  free_stack(&result);

  munit_assert_ptr_null(result);

  return MUNIT_OK;
}

MunitResult test_free_stack_on_null() {
  snek_stack_t *result = NULL;

  free_stack(&result);

  return MUNIT_OK;
}

MunitResult test_create_stack_small() {
  snek_stack_t *s = alloc_stack(3);

  munit_assert_int(s->capacity, ==, 3);
  munit_assert_int(s->count, ==, 0);
  munit_assert_ptr_not_null(s->data);

  free_stack(&s);

  return MUNIT_OK;
}

MunitResult test_create_stack_large() {
  snek_stack_t *s = alloc_stack(100);

  munit_assert_int(s->capacity, ==, 100);
  munit_assert_int(s->count, ==, 0);
  munit_assert_ptr_not_null(s->data);

  free_stack(&s);

  return MUNIT_OK;
}

int main(int argc, char **argv) {
  MunitTest tests[] = {
      {
          "/test_free_stack",
          test_free_stack,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/test_free_stack_on_null",
          test_free_stack_on_null,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/test_create_stack_small",
          test_create_stack_small,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/test_create_stack_large",
          test_create_stack_large,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
  };

  MunitSuite suite = {
      "low-level-stack",
      tests,
      NULL,
      1,
      (MunitSuiteOptions)MUNIT_TEST_OPTION_NONE,
  };

  return munit_suite_main(&suite, NULL, argc, (char *const *)argv);
}
