 
#include "gtest/gtest.h" 
#include "string" 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <sys/ioctl.h>
 
#define WR_VALUE _IOW('a','a',int32_t*)
#define RD_VALUE _IOR('a','b',int32_t*)
int fd  ;
   int32_t  number=2,value=2 ;
// Test Case #1
TEST(testDriver, testEmployeeName)
{
 
  fd = open("/dev/etx_device", O_RDWR);	
  EXPECT_GT(fd,0);
 
}
// Test case #2
TEST(testDriver, testEmployeeName2)
{

  
  EXPECT_EQ(ioctl(fd, WR_VALUE, (int32_t*) &number),0);
}
// Test case #3
TEST(testDriver, testEmployeeName3)
{

  
  EXPECT_ET(ioctl(fd, RD_VALUE, (int32_t*) &value),0);
}


// Main Function
int main(int argc, char* *argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
