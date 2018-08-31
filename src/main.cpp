#include <iostream>
#include <string>

#include "iolib.h"

int main(int argc, char *argv[])
{
  std::cout << "Hello World!" << std::endl;
  std::string str_data = "Here is some data\n";
  // std::cout << std::strlen(str_data.c_str())  << "\n";
  // cust_write(str_data.c_str(), 1);
  // cust_read();
  // console_file_write("testfile.txt");
  copy("yum.log", "copy_test.txt");
  return 0;
}
