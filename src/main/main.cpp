#include "../adt/include/adt.h"
#include "../log/include/log.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[]) {

  for (int i = 0; i < argc; i++) {
    std::cout << "argv[" << i << "] = " << argv[i] << std::endl;
  }

  std::cout << "Hello, World!" << std::endl;

  print_adt_message();

  print_log_message();
  Lists::SinglyLinkedList<int> list;
  list.add(3);
  list.add(2);
  list.add(1);

  std::cout << "Unsorted list: " << std::endl;

  for (auto it = list.begin(); it != list.end(); ++it) {
    std::cout << *it << std::endl;
  }


  list.printList();

  auto begin = list.rand_begin();
  auto end = list.rand_end();
  std::sort(begin, end);

  list.printList();

  std::cout << "Sorted list: " << std::endl;

  for (auto it = list.begin(); it != list.end(); ++it) {
    std::cout << *it << std::endl;
  }

  /*
  Lists::DoublyLinkedList<int> list;
  for (int i = 0; i < 100; ++i) {
    list.add(i);
  }
  */
  /*
  for (int i = 50; i > 1; --i) {
    std::cout << "Index " << i << " Value " << i << std::endl;
    list.add(i , i); // Add at the middle of the list
  }
  */
  /*
  Lists::CircularLinkedList<int> list;
  for (int i = 0; i < 100; ++i) {
    list.add(i);
  }
  for (int i = 100; i > 1; --i) {
    std::cout << "Removing element: " << i << std::endl;
    list.remove(i/2); // Remove elements from the end
  }
  */
  std::cout << "List size: " << list.getSize() << std::endl;
  /*
    Lists::SinglyLinkedList<int> list;
    list.add(1);
    list.remove(1);
    std::cout << "List size: " << list.getSize() << std::endl;
  */
  return EXIT_SUCCESS;
}
