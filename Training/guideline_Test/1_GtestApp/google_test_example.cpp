 
#include "gtest/gtest.h"

#include "string"

// Add the Employee details header file
#include "Employee_details.h"

// Test Case #1
TEST(Employee, testEmployeeName)
{

  string testName="muni";

  // Create emp object
  Employee *emp = new Employee();

  // Set the name
  if(emp)
     emp->setEmployeeName(testName);

  // Validate the Name
  EXPECT_EQ(emp->getEmployeeName(), testName);
  
  delete emp;
}

// Test Case #2
TEST(Employee, testEmployeeId)
{

  int id=3;

  // Create emp object
  Employee *emp = new Employee();

  // Set the name
  if(emp)
     emp->setEmployeeId(id);

  // Validate the Name
  EXPECT_EQ(emp->getEmployeeId(), id);
 
  delete emp;
}

// Test Case #3
TEST(Employee, testEmployeeSalary)
{
  int sal=100;

  // Create emp object
  Employee *emp = new Employee();

  // Set the name
  if(emp)
     emp->setEmployeeSalary(sal);

  // Validate the Salary
  EXPECT_EQ(emp->getEmployeeSalary(), sal);
  
  delete emp;
}

// Main Function
int main(int argc, char* *argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
