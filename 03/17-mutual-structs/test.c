#include "../../munit//munit.h"

#include "exercise.h"
#include <string.h>

MunitResult test_employee_init(const MunitParameter params[],
                               void *user_data_or_fixture) {
  employee_t e = new_employee("jo");

  munit_assert_string_equal(e.name, "jo");
  munit_assert_null(e.department);

  return MUNIT_OK;
}
MunitResult test_department_init(const MunitParameter params[],
                                 void *user_data_or_fixture) {
  employee_t e = new_employee("jo");
  department_t d = new_department("x", &e);

  munit_assert_string_equal(d.name, "x");
  munit_assert_ptr_equal(d.manager, &e);

  return MUNIT_OK;
}

MunitResult test_employee_dept_assignable(const MunitParameter params[],
                                          void *user_data_or_fixture) {
  employee_t m = new_employee("jo");
  employee_t e = new_employee("schmoe");
  department_t d = new_department("x", &m);

  assign_department(&e, &d);

  munit_assert_ptr_equal(e.department, &d);

  return MUNIT_OK;
}

MunitResult test_department_employee_assignable(const MunitParameter *params[],
                                                void *user_data_or_fixture) {
  employee_t m1 = new_employee("jo");
  employee_t m2 = new_employee("schmoe");
  department_t d = new_department("x", &m1);

  assign_manager(&d, &m2);

  munit_assert_ptr_equal(d.manager, &m2);

  return MUNIT_OK;
}

int main(int argc, const char *argv[]) {
  MunitTest tests[] = {
      {
          "/test_employee_init",
          test_employee_init,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/test_department_init",
          test_department_init,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/test_employee_dept_assignable",
          test_employee_dept_assignable,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/test_employee_dept_assignable",
          test_employee_dept_assignable,
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
