/***************************
 * Employee Details
 *
 ***************************/

#include "Employee_details.h"

  // Default constructor
  Employee :: Employee()
  {

  }

  // set the Employee Name
  void Employee :: setEmployeeName(string name)
  {
      this->employee_name = name;
  }

  // set the Employee Id
  void Employee :: setEmployeeId(int id)
  {
      this->employee_id = id;
  }

  // set the Employee Salary
  void Employee :: setEmployeeSalary(int sal)
  {
      this->salary = sal;
  }

  // get the Employee Name
  string Employee :: getEmployeeName()
  {
      return this->employee_name;
  }

  // get the Employee Id
  int Employee :: getEmployeeId()
  {
      return this->employee_id;
  }

  // get the Employee Salary
  int Employee :: getEmployeeSalary()
  {
      return this->salary;
  }
