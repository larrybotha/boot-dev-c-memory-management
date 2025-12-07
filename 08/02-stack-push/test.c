#include "../../munit/munit.h"
#include <stdio.h>

#include "snekstack.h"

MunitResult test_create_stack() {
  snek_stack_t *s = alloc_stack(10);

  munit_assert_int(s->capacity, ==, 10);
  munit_assert_int(s->count, ==, 0);
  munit_assert_ptr_not_null(s->data);

  free_stack(&s);

  return MUNIT_OK;
}

MunitResult test_push_stack() {
  snek_stack_t *s = alloc_stack(2);

  int xs[2] = {1, 2};
  size_t len = sizeof(xs) / sizeof(int);

  for (size_t i = 0; i < len; i++) {
    push_stack(s, &xs[i]);

    munit_assert_int(s->count, ==, i + 1);
    munit_assert_int(*(int *)s->data[i], ==, xs[i]);
  }

  free_stack(&s);

  return MUNIT_OK;
}

MunitResult test_stack_resize() {
  snek_stack_t *s = alloc_stack(2);

  int xs[3] = {1, 2, 3};
  size_t len = sizeof(xs) / sizeof(int);

  for (size_t i = 0; i < len; i++) {
    push_stack(s, &xs[i]);

    munit_assert_int(*(int *)s->data[i], ==, xs[i]);
  }

  munit_assert_int(s->capacity, ==, 4);
  munit_assert_int(s->count, ==, len);

  free_stack(&s);

  return MUNIT_OK;
}

int main(int argc, const char *argv[]) {
  MunitTest tests[] = {
      {
          "/test_create_stack",
          test_create_stack,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/test_push_stack",
          test_push_stack,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/test_stack_resize",
          test_stack_resize,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
  };

  MunitSuite suite = {
      "stack-push", tests, NULL, 1, (MunitSuiteOptions)MUNIT_TEST_OPTION_NONE,
  };

  return munit_suite_main(&suite, NULL, argc, (char *const *)argv);
}
