#ifndef LIST_H
#define LIST_H

#include "../node/node.h"
#include <iostream>

struct oogabooga {
  int a;
  int b;
};

namespace Lists {

template <typename T> class ListAdt {
public:
  virtual void add(T data) = 0;
  virtual void insertAtFront(T data) = 0;
  virtual void insertAtEnd(T data) = 0;

  virtual void remove(T data) = 0;
  virtual void removeFromFront(T data) = 0;
  virtual void removeFromEnd(T data) = 0;

  virtual bool contains(T data) const = 0;

  virtual void print() const = 0;

  virtual size_t getSize() const = 0;
  virtual bool isEmpty() const = 0;

  virtual void clear() = 0;
};

template <typename T> ListAdt<T> *createSingleLinkList();

template <typename T> class SinglyLinkedList : public ListAdt<T> {
private:
  Nodes::SingleLinkNode<T> *head;
  size_t size;

public:
  SinglyLinkedList();
  virtual ~SinglyLinkedList();

  // from ListAdt<T>
  void add(T data) override;
  void insertAtFront(T data) override;
  void insertAtEnd(T data) override;

  void remove(T data) override;
  void removeFromFront(T data) override;
  void removeFromEnd(T data) override;

  bool contains(T data) const override;

  void print() const override;

  size_t getSize() const override;
  bool isEmpty() const override;

  void clear() override;
};

template <typename T> ListAdt<T> *createSingleLinkList() {
  return new SinglyLinkedList<T>();
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList() : head(nullptr), size(0) {}

template <typename T> SinglyLinkedList<T>::~SinglyLinkedList() {
  Nodes::SingleLinkNode<T> *current = head;
  Nodes::SingleLinkNode<T> *next = nullptr;
  while (current != nullptr) {
    next = current->getNext();
    delete current;
    current = next;
  }
}

// force compiler to generate the class for the types we need
// template class SinglyLinkedList<int>;
// template class SinglyLinkedList<std::string>;

template <typename T> void SinglyLinkedList<T>::add(T data) {
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

template <typename T> void SinglyLinkedList<T>::insertAtFront(T data) {
  Nodes::SingleLinkNode<T> *newNode = new Nodes::SingleLinkNode<T>(data);
  if (head == nullptr) {
    head = newNode;
  } else {
    newNode->setNext(head);
    head = newNode;
  }
  size++;
}

template <typename T> void SinglyLinkedList<T>::insertAtEnd(T data) {
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
}

template <typename T> void SinglyLinkedList<T>::remove(T data) {
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

template <typename T> void SinglyLinkedList<T>::print() const {
  Nodes::SingleLinkNode<T> *current = head;
  while (current != nullptr) {
    std::cout << current->getData() << " ";
    current = current->getNext();
  }
  std::cout << std::endl;
}

template <typename T> size_t SinglyLinkedList<T>::getSize() const {
  return size;
}

template <typename T> bool SinglyLinkedList<T>::isEmpty() const {
  return head == nullptr;
}

template <typename T> void SinglyLinkedList<T>::clear() {
  Nodes::SingleLinkNode<T> *current = head;
  Nodes::SingleLinkNode<T> *next = nullptr;
  while (current != nullptr) {
    next = current->getNext();
    delete current;
    current = next;
  }
  head = nullptr;
  size = 0;
}

template <typename T> void SinglyLinkedList<T>::removeFromFront(T data) {
  remove(data);
}

template <typename T> void SinglyLinkedList<T>::removeFromEnd(T data) {
  remove(data);
}

template <typename T> bool SinglyLinkedList<T>::contains(T data) const {
  Nodes::SingleLinkNode<T> *current = head;
  while (current != nullptr) {
    if (current->getData() == data) {
      return true;
    }
    current = current->getNext();
  }
  return false;
}

template <typename T> class DoublyLinkedList {
private:
  Nodes::DoubleLinkNode<T> *head;
  size_t size;

public:
  DoublyLinkedList();
  ~DoublyLinkedList();
  void add(T data);
  void remove(T data);
  void print();
  size_t getSize() const;
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), size(0) {}

template <typename T> DoublyLinkedList<T>::~DoublyLinkedList() {
  Nodes::DoubleLinkNode<T> *current = head;
  Nodes::DoubleLinkNode<T> *next = nullptr;
  while (current != nullptr) {
    next = current->getNext();
    delete current;
    current = next;
  }
}

template <typename T> void DoublyLinkedList<T>::add(T data) {
  Nodes::DoubleLinkNode<T> *newNode = new Nodes::DoubleLinkNode<T>(data);
  if (head == nullptr) {
    head = newNode;
  } else {
    Nodes::DoubleLinkNode<T> *current = head;
    while (current->getNext() != nullptr) {
      current = current->getNext();
    }
    current->setNext(newNode);
    newNode->setPrev(current);
  }
  size++;
}

template <typename T> void DoublyLinkedList<T>::remove(T data) {
  Nodes::DoubleLinkNode<T> *current = head;
  Nodes::DoubleLinkNode<T> *prev = nullptr;
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
  Nodes::DoubleLinkNode<T> *current = head;
  while (current != nullptr) {
    std::cout << current->getData() << " ";
    current = current->getNext();
  }
  std::cout << std::endl;
}

template <typename T> size_t DoublyLinkedList<T>::getSize() const {
  return size;
}

} // namespace Lists

#endif // LIST_H
