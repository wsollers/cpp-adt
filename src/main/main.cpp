#include <cstdlib>
#include <iostream>

#include "../adt/include/adt.h"
#include "../log/include/log.h"

int main(int argc, char *argv[]) {

  for ( int i = 0; i < argc; i++ ) {
    std::cout << "argv[" << i << "] = " << argv[i] << std::endl;
  }

  std::cout << "Hello, World!" << std::endl;

  print_adt_message();

  print_log_message();

  Lists::SinglyLinkedList<int> list;
  list.add(1);
  std::cout << "List size: " << list.getSize() << std::endl;

  return EXIT_SUCCESS;
}
