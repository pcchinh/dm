 
 
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
int fd ,buf ;
int32_t  number,value ;
#define mem_size        1024
int8_t *kernel_buffer;
// Test Case #1
TEST(testDriver, Creatingdevice)
{
 
  fd = open("/dev/etx_device", O_RDWR);	
  EXPECT_GT(fd,0);
 
}
 //  TEST(testDriver, Creatingstructclass)
 // {
 
 //   fd = open("/dev/etx_class", O_RDWR);	
 //   EXPECT_LT(0,fd);
 
 // }
 // TEST(testDriver, AllocatingMajornumber)
 // {
 
 //   fd = open("/dev/etx_etx_Dev", O_RDWR);	
 //   EXPECT_LT(0,fd);
 
 // }
 // TEST(testDriver, etxioctl)
 // {

 //  EXPECT_GT(ioctl(fd, WR_VALUE, (int32_t*) &number),0);
 
 // }
//TEST(testDriver, etxread)
//{
 
//  EXPECT_GT(0,read(buf, kernel_buffer, mem_sizef));
 
//}
 //TEST(testDriver, etxwrite)
 //{
 
 //  EXPECT_GT(0,write(kernel_buffer, buf, len));
 
//}
// Test case #2
// TEST(testDriver, testEmployeeName2)
// {

  
//  EXPECT_GT(0,ioctl(fd, WR_VALUE, (int32_t*) &number));
// }
// Test case #3
// TEST(testDriver, testEmployeeName3)
// {

  
//  EXPECT_LT(ioctl(fd, RD_VALUE, (int32_t*) &value),0);
// }


// Main Function
int main(int argc, char* *argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
