#include <iostream>
#include <string>

#include "iolib.h"

int main(int argc, char *argv[])
{
  copy("data/messages", "data/copy_test.txt");
  return 0;
}
