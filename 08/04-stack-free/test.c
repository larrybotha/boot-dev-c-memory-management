#include "../../munit/munit.h"

#include "./snekstack.h"

MunitResult test_create_stack() {
  int xs[2] = {1, 2};
  size_t len = sizeof(xs) / sizeof(xs[0]);

  for (size_t i = 0; i < len; i++) {
    int x = xs[i];
    snek_stack_t *s = alloc_stack(x);

    munit_assert_int(s->capacity, ==, x);
    munit_assert_int(s->count, ==, 0);
    munit_assert_ptr_not_null(s->data);

    free_stack(&s);

    munit_assert_ptr_null(s);
  }

  return MUNIT_OK;
}

MunitResult test_push_stack() {
  snek_stack_t *s = alloc_stack(1);
  int xs[4] = {1, 2, 3, 4};
  int len = sizeof(xs) / sizeof(xs[0]);

  for (size_t i = 0; i < len; i++) {
    int x = xs[i];
    size_t expect_cap = s->capacity;

    if (i >= expect_cap) {
      expect_cap *= GROWTH_FACTOR;
    }

    push_stack(s, &x);

    munit_assert_int(*(int *)s->data[i], ==, x);
    munit_assert_int(s->capacity, ==, expect_cap);
  }

  munit_assert_int(s->capacity, ==, len);
  munit_assert_int(s->count, ==, len);

  free_stack(&s);

  return MUNIT_OK;
}

MunitResult test_pop_stack_empty() {
  snek_stack_t *s = alloc_stack(0);

  void *x = pop_stack(s);

  munit_assert_ptr_null(x);

  return MUNIT_OK;
}

MunitResult test_pop_stack() {
  snek_stack_t *s = alloc_stack(4);
  int xs[4] = {3, 4, 5, 6};
  int len = sizeof(xs) / sizeof(xs[0]);

  for (size_t i = 0; i < len; i++) {
    push_stack(s, &xs[i]);
  }

  for (size_t i = len; i > 0; i--) {
    size_t index = i - 1;
    const int *x = (int *)pop_stack(s);

    munit_assert_int(*x, ==, xs[index]);
    munit_assert_int(s->count, ==, i - 1);
  }

  munit_assert_int(s->capacity, ==, 1);
  munit_assert_int(s->count, ==, 0);

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
          "/test_pop_stack_empty",
          test_pop_stack_empty,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/test_pop_stack",
          test_pop_stack,
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
