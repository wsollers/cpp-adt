#ifndef LIST_H
#define LIST_H

#include <iostream>

#include "../node/node.h"

struct oogabooga {
  int a;
  int b;
};

template <typename T> class SinglyLinkedList {
private:
  SingleLinkNode<T> *head;
  int size;

public:
  SinglyLinkedList();
  ~SinglyLinkedList();
  void add(T data);
  void remove(T data);
  void print();
  int getSize();
};


template <typename T> SinglyLinkedList<T>::SinglyLinkedList() : head(nullptr), size(0) {}

template <typename T> SinglyLinkedList<T>::~SinglyLinkedList() {
  SingleLinkNode<T> *current = head;
  SingleLinkNode<T> *next = nullptr;
  while (current != nullptr) {
    next = current->getNext();
    delete current;
    current = next;
  }
}


//force compiler to generate the class for the types we need
//template class SinglyLinkedList<int>;
//template class SinglyLinkedList<std::string>;

template <typename T> void SinglyLinkedList<T>::add(T data) {
  SingleLinkNode<T> *newNode = new SingleLinkNode<T>(data);
  if (head == nullptr) {
    head = newNode;
  } else {
    SingleLinkNode<T> *current = head;
    while (current->getNext() != nullptr) {
      current = current->getNext();
    }
    current->setNext(newNode);
  }
  size++;
}

template <typename T> void SinglyLinkedList<T>::remove(T data) {
  SingleLinkNode<T> *current = head;
  SingleLinkNode<T> *prev = nullptr;
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

template <typename T> void SinglyLinkedList<T>::print() {
  SingleLinkNode<T> *current = head;
  while (current != nullptr) {
    std::cout << current->getData() << " ";
    current = current->getNext();
  }
  std::cout << std::endl;
}

template <typename T> int SinglyLinkedList<T>::getSize() {
  return size;
}

template <typename T> class DoublyLinkedList {
private:
  DoubleLinkNode<T> *head;
  int size;

public:
  DoublyLinkedList();
  ~DoublyLinkedList();
  void add(T data);
  void remove(T data);
  void print();
  int getSize();
};

template <typename T> DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), size(0) {}

template <typename T> DoublyLinkedList<T>::~DoublyLinkedList() {
  DoubleLinkNode<T> *current = head;
  DoubleLinkNode<T> *next = nullptr;
  while (current != nullptr) {
    next = current->getNext();
    delete current;
    current = next;
  }
}

template <typename T> void DoublyLinkedList<T>::add(T data) {
  DoubleLinkNode<T> *newNode = new DoubleLinkNode<T>(data);
  if (head == nullptr) {
    head = newNode;
  } else {
    DoubleLinkNode<T> *current = head;
    while (current->getNext() != nullptr) {
      current = current->getNext();
    }
    current->setNext(newNode);
    newNode->setPrev(current);
  }
  size++;
}

template <typename T> void DoublyLinkedList<T>::remove(T data) {
  DoubleLinkNode<T> *current = head;
  DoubleLinkNode<T> *prev = nullptr;
  while (current != nullptr) {
    if (current->getData() == data) {
      if (prev == nullptr) {
        head = current->getNext();
      } else {
        prev->setNext(current->getNext());
        current->getNext()->setPrev(prev);
      }
      delete current;
      size--;
      return;
    }
    prev = current;
    current = current->getNext();
  }
}

template <typename T> void DoublyLinkedList<T>::print() {
  DoubleLinkNode<T> *current = head;
  while (current != nullptr) {
    std::cout << current->getData() << " ";
    current = current->getNext();
  }
  std::cout << std::endl;
}

template <typename T> int DoublyLinkedList<T>::getSize() {
  return size;
}

#endif // LIST_H
