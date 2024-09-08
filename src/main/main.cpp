#include <cstdlib>
#include <iostream>

#include "../adt/include/adt.h"
#include "../log/include/log.h"

int main(int argc, char *argv[]) {
  std::cout << "Hello, World!" << std::endl;

  print_adt_message();

  print_log_message();

  return EXIT_SUCCESS;
}
