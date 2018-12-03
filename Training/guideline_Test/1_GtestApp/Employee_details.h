#ifndef EMPLOYEE_DETAILS_H
#define EMPLOYEE_DETAILS_H

#include "string"

using std::string;

class Employee
{
  string employee_name;
  int employee_id;
  int salary;

  public:

  Employee();

  // Set functions
  void setEmployeeName(string name);
  void setEmployeeId(int employee_id);
  void setEmployeeSalary(int salary);

  // Get functions
  string getEmployeeName();
  int getEmployeeId();
  int getEmployeeSalary();

};

#endif /* EMPLOYEE_DETAILS_H */
