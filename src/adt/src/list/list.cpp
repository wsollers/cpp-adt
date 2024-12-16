#include "list.h"

#include <iostream>
#include <string>

#include "../node/node.h"

namespace Lists {}

template <typename T>
class SinglyLinkedList {
 private:
  Nodes::SingleLinkNode<T> *head;
  int size;

 public:
  SinglyLinkedList();
  ~SinglyLinkedList();
  void add(T data);
  void remove(T data);
  void print();
  int getSize();
};

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList() : head(nullptr), size(0) {}

template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
  Nodes::SingleLinkNode<T> *current = head;
  Nodes::SingleLinkNode<T> *next = nullptr;
  while (current != nullptr) {
    next = current->getNext();
    delete current;
    current = next;
  }
}

// force compiler to generate the class for the types we need
template class SinglyLinkedList<int>;
template class SinglyLinkedList<std::string>;

template <typename T>
void SinglyLinkedList<T>::add(T data) {
  Nodes::SingleLinkNode<T> *newNode = new Nodes::SingleLinkNode<T>(data);
  if (head == nullptr) {
    head = newNode;
  } else {
    Nodes::SingleLinkNode<T> *current = head;
    while (current->getNext() != nullptr) {
      current = current->getNext();
    }
    current->setNext(newNode);
  }
  size++;
}

template <typename T>
void SinglyLinkedList<T>::remove(T data) {
  Nodes::SingleLinkNode<T> *current = head;
  Nodes::SingleLinkNode<T> *prev = nullptr;
  while (current != nullptr) {
    if (current->getData() == data) {
      if (prev == nullptr) {
        head = current->getNext();
      } else {
        prev->setNext(current->getNext());
      }
      delete current;
      size--;
      return;
    }
    prev = current;
    current = current->getNext();
  }
}

template <typename T>
void SinglyLinkedList<T>::print() {
  Nodes::SingleLinkNode<T> *current = head;
  while (current != nullptr) {
    std::cout << current->getData() << " ";
    current = current->getNext();
  }
  std::cout << std::endl;
}

template <typename T>
int SinglyLinkedList<T>::getSize() {
  return size;
}
