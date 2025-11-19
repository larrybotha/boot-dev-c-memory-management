#include "exercise.h"
#include <stdlib.h>

employee_t new_employee(char *name) {
  employee_t employee = {
      .name = name,
      .department = NULL,
  };

  return employee;
}

void assign_department(employee_t *emp, department_t *dept) {
  if (emp != NULL) {
    emp->department = dept;
  }
}

department_t new_department(char *name, employee_t *manager) {
  department_t d = {
      .name = name,
      .manager = manager,
  };

  return d;
}

void assign_manager(department_t *dept, employee_t *emp) {
  if (dept != NULL) {
    dept->manager = emp;
  }
}
