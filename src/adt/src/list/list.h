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





/*
 * DoublyLinkedList
 */
template <typename T> class DoublyLinkedList : public ListAdt<T> {
private:
  Nodes::DoubleLinkNode<T> *head;
  size_t size;

public:
  DoublyLinkedList();
  ~DoublyLinkedList();

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

//template <typename T> ListAdt<T> *createDoublyLinkedList();

template <typename T> ListAdt<T> *createDoublyLinkedList() {
  return new DoublyLinkedList<T>();
}

template <typename T> 
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), size(0) {}

template <typename T> 
DoublyLinkedList<T>::~DoublyLinkedList() {
  Lists::DoublyLinkedList<T>::clear();
}

template <typename T> 
void DoublyLinkedList<T>::add(T data) {
  insertAtEnd(data);
}

template <typename T> 
void DoublyLinkedList<T>::insertAtFront(T data) {
  Nodes::DoubleLinkNode<T>* newNode = new Nodes::DoubleLinkNode<T>(data);

  if (isEmpty()) {
    head = newNode;
  } else {
    newNode->setNext(head);
    head->setPrev(newNode);
    head = newNode;
  }
  size++;
}

template <typename T> 
void DoublyLinkedList<T>::insertAtEnd(T data) {
  Nodes::DoubleLinkNode<T>* newNode = new Nodes::DoubleLinkNode<T>(data);

  if (isEmpty()) {
    head = newNode;
  } else {
    Nodes::DoubleLinkNode<T>* tail = head;
    while (tail->getNext() != nullptr) {
      tail = tail->getNext();
    }
    tail->setNext(newNode);
    newNode->setPrev(tail);
  }
  size++;
}

template <typename T> 
void DoublyLinkedList<T>::remove(T data) {
  if (isEmpty()) {
    return;
  }

  Nodes::DoubleLinkNode<T>* current = head;
  while (current != nullptr) {
    if (current->getData() == data) {
      Nodes::DoubleLinkNode<T>* prev = current->getPrev();
      Nodes::DoubleLinkNode<T>* next = current->getNext();

      if (prev != nullptr) {
        prev->setNext(next);
      } else {
        head = next; // Removing the head
      }

      if (next != nullptr) {
        next->setPrev(prev);
      }

      delete current;
      size--;
      return;
    }
    current = current->getNext();
  }
}

template <typename T> 
void DoublyLinkedList<T>::removeFromFront(T data) {
  if (!isEmpty()) {
    remove(head->getData());
  }
}

template <typename T> 
void DoublyLinkedList<T>::removeFromEnd(T data) {
  if (isEmpty()) {
    return;
  }

  Nodes::DoubleLinkNode<T>* tail = head;
  while (tail->getNext() != nullptr) {
    tail = tail->getNext();
  }
  remove(tail->getData());
}

template <typename T> 
bool DoublyLinkedList<T>::contains(T data) const {
  if (isEmpty()) {
    return false;
  }

  Nodes::DoubleLinkNode<T>* current = head;
  while (current != nullptr) {
    if (current->getData() == data) {
      return true;
    }
    current = current->getNext();
  }
  return false;
}

template <typename T> 
void DoublyLinkedList<T>::print() const {
  if (isEmpty()) {
    std::cout << "List is empty." << std::endl;
    return;
  }

  Nodes::DoubleLinkNode<T>* current = head;
  while (current != nullptr) {
    std::cout << current->getData() << " ";
    current = current->getNext();
  }
  std::cout << std::endl;
}

template <typename T> 
size_t DoublyLinkedList<T>::getSize() const {
  return size;
}

template <typename T> 
bool DoublyLinkedList<T>::isEmpty() const {
  return size == 0;
}

template <typename T> 
void DoublyLinkedList<T>::clear() {
  while (!isEmpty()) {
    removeFromFront(head->getData());
  }
}














/*
 * CircularLinkedList
 */
template <typename T> class CircularLinkedList : public ListAdt<T> {
private:
  Nodes::DoubleLinkNode<T> *head;
  size_t size;
public:
  CircularLinkedList();
  virtual ~CircularLinkedList();

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

template <typename T> ListAdt<T> *createCircularLinkedList() {
  return new CircularLinkedList<T>();
}

template <typename T> 
CircularLinkedList<T>::CircularLinkedList() : head(nullptr), size(0) {}

template <typename T> 
CircularLinkedList<T>::~CircularLinkedList() {
  //Invocation of virtual destructor is ok if resolved properly
  Lists::CircularLinkedList<T>::clear();
}

template <typename T> 
void CircularLinkedList<T>::add(T data) {
  insertAtEnd(data);
}

template <typename T> 
void CircularLinkedList<T>::insertAtFront(T data) {
  Nodes::DoubleLinkNode<T>* newNode = new Nodes::DoubleLinkNode<T>(data);

  if (isEmpty()) {
    head = newNode;
    head->setNext(head);
    head->setPrev(head);
  } else {
    Nodes::DoubleLinkNode<T>* tail = head->getPrev();
    newNode->setNext(head);
    newNode->setPrev(tail);
    tail->setNext(newNode);
    head->setPrev(newNode);
    head = newNode;
  }
  size++;
}

template <typename T> 
void CircularLinkedList<T>::insertAtEnd(T data) {
  Nodes::DoubleLinkNode<T>* newNode = new Nodes::DoubleLinkNode<T>(data);

  if (isEmpty()) {
    head = newNode;
    head->setNext(head);
    head->setPrev(head);
  } else {
    Nodes::DoubleLinkNode<T>* tail = head->getPrev();
    newNode->setNext(head);
    newNode->setPrev(tail);
    tail->setNext(newNode);
    head->setPrev(newNode);
  }
  size++;
}

template <typename T> 
void CircularLinkedList<T>::remove(T data) {
  if (isEmpty()) {
    return;
  }

  Nodes::DoubleLinkNode<T>* current = head;
  do {
    if (current->getData() == data) {
      Nodes::DoubleLinkNode<T>* prev = current->getPrev();
      Nodes::DoubleLinkNode<T>* next = current->getNext();

      if (current == head && size == 1) {
        head = nullptr;
      } else {
        prev->setNext(next);
        next->setPrev(prev);
        if (current == head) {
          head = next;
        }
      }

      delete current;
      size--;
      return;
    }
    current = current->getNext();
  } while (current != head);
}

template <typename T> 
void CircularLinkedList<T>::removeFromFront(T data) {
  if (!isEmpty()) {
    remove(head->getData());
  }
}

template <typename T> 
void CircularLinkedList<T>::removeFromEnd(T data) {
  if (!isEmpty()) {
    Nodes::DoubleLinkNode<T>* tail = head->getPrev();
    remove(tail->getData());
  }
}

template <typename T> 
bool CircularLinkedList<T>::contains(T data) const {
  if (isEmpty()) {
    return false;
  }

  Nodes::DoubleLinkNode<T>* current = head;
  do {
    if (current->getData() == data) {
      return true;
    }
    current = current->getNext();
  } while (current != head);

  return false;
}

template <typename T> 
void CircularLinkedList<T>::print() const {
  if (isEmpty()) {
    std::cout << "List is empty." << std::endl;
    return;
  }

  Nodes::DoubleLinkNode<T>* current = head;
  do {
    std::cout << current->getData() << " ";
    current = current->getNext();
  } while (current != head);
  std::cout << std::endl;
}

template <typename T> 
size_t CircularLinkedList<T>::getSize() const {
  return size;
}

template <typename T> 
bool CircularLinkedList<T>::isEmpty() const {
  return size == 0;
}

template <typename T> 
void CircularLinkedList<T>::clear() {
  while (!isEmpty()) {
    removeFromFront(head->getData());
  }
}

} // namespace Lists

#endif // LIST_H
