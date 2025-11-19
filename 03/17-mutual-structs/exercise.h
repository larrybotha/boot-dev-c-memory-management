#pragma once

typedef struct Employee employee_t;
typedef struct Department department_t;

typedef struct Employee {
  char *name;
  department_t *department;
} employee_t;

typedef struct Department {
  char *name;
  employee_t *manager;
} department_t;

employee_t new_employee(char *name);
void assign_department(employee_t *emp, department_t *dept);

department_t new_department(char *name, employee_t *manager);
void assign_manager(department_t *dept, employee_t *emp);
