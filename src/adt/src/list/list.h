#ifndef LIST_H
#define LIST_H

#include "../node/node.h"
#include "../common/common.h"
#include <cstddef> // For std::ptrdiff_t
#include <ios>
#include <iostream>
#include <iterator> // For std::forward_iterator_tag
#include <ranges>
#include <stdexcept> // std::out_of_range
#include <optional>
//#include <experimental/source_location>
//#include <expected>



struct oogabooga {
  int a;
  int b;
};


/*
 */
namespace Lists {

template <typename T>
requires Common::stl_container_storable<T>
class ListAdt {
public:
  ListAdt() {}
  virtual ~ListAdt() {}

  virtual bool add(T data) = 0;
  virtual bool add(size_t index, T data) = 0;

  virtual std::optional<T> remove(size_t index) = 0;
  virtual bool remove(T data) = 0;

  virtual bool contains(T data) const = 0;

  virtual std::optional<T> get(size_t index) const = 0;
  virtual std::optional<T> set(size_t index, T data) = 0;

  virtual size_t indexOf(T data) const = 0;
  virtual size_t lastIndexOf(T data) const = 0;

  virtual bool isEmpty() const = 0;
  virtual size_t getSize() const = 0;
  virtual void clear() = 0;
};
// Forward Declaration
// template <typename T> class SinglyLinkedListForwardIterator;

// forward declaration
template <typename T> class SinglyLinkedListForwardIterator;
template <typename T> class SinglyLinkedListRandomAccessIterator;

template <typename T> class SinglyLinkedList : public ListAdt<T> {
private:
  Nodes::SingleLinkNode<T> *head;
  size_t size;

public:
  SinglyLinkedList();
  explicit SinglyLinkedList(std::ranges::input_range auto &&range);

  ~SinglyLinkedList();

  bool add(T data) override;
  bool add(size_t index, T data) override;

  std::optional<T> remove(size_t index) override;
  bool remove(T data) override;

  bool contains(T data) const override;

  std::optional<T> get(size_t index) const override;
  std::optional<T> set(size_t index, T data) override;

  size_t indexOf(T data) const override;
  size_t lastIndexOf(T data) const override;

  bool isEmpty() const override;
  size_t getSize() const override;
  void clear() override;

  friend class SinglyLinkedListForwardIterator<T>;
  friend class SinglyLinkedListRandomAccessIterator<T>;

  SinglyLinkedListForwardIterator<T> begin() {
    return SinglyLinkedListForwardIterator<T>(head);
  }

  SinglyLinkedListForwardIterator<T> end() {
    return SinglyLinkedListForwardIterator<T>(nullptr);
  }

  SinglyLinkedListRandomAccessIterator<T> rand_begin() {
    return SinglyLinkedListRandomAccessIterator<T>(head, head);
  }

  SinglyLinkedListRandomAccessIterator<T> rand_end() {
    return SinglyLinkedListRandomAccessIterator<T>(nullptr, head);
  }

  // XXX
  void printList() {
    Nodes::SingleLinkNode<T> *current = head;
    std::cout << "List: this: " << std::hex << this << " Head: " << std::hex
              << head << std::endl;
    while (current != nullptr) {
      std::cout << "Data: " << current->getData() << " current: " << std::hex
                << current << " next " << std::hex << current->getNext()
                << std::endl;
      current = current->getNext();
    }
  }
};

template <typename T> ListAdt<T> *createSingleLinkList() {
  test_common();
  return new SinglyLinkedList<T>();
}

// Constructor
template <typename T>
SinglyLinkedList<T>::SinglyLinkedList() : head(nullptr), size(0) {}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(std::ranges::input_range auto &&range)
    : head(nullptr), size(0) {
  for (auto &&item : range) {
    // process the item
    this->add(item);
  }
}

// Destructor
template <typename T> SinglyLinkedList<T>::~SinglyLinkedList() {
  Lists::SinglyLinkedList<T>::clear();
}

// Add an element to the end of the list
template <typename T> bool SinglyLinkedList<T>::add(T data) {
  Nodes::SingleLinkNode<T> *newNode = new Nodes::SingleLinkNode<T>(data);

  if (isEmpty()) {
    head = newNode;
  } else {
    Nodes::SingleLinkNode<T> *current = head;
    while (current->getNext() != nullptr) {
      // std::cout << "current: " << std::hex << current << std::endl;
      current = current->getNext();
    }
    current->setNext(newNode);
  }

  size++;
  return true;
}

// Add an element at a specific index
template <typename T> bool SinglyLinkedList<T>::add(size_t index, T data) {
  if (index > size) {
    //throw std::out_of_range("Index out of bounds"); // maybe not do this
    //Error e = {"Index out of bounds", std::experimental::source_location::current()};
    Error e = {"Index out of bounds", __FILE__, __FUNCTION__, __LINE__};
    report_error(e);
    return false;
  }

  Nodes::SingleLinkNode<T> *newNode = new Nodes::SingleLinkNode<T>(data);

  if (index == 0) {
    newNode->setNext(head);
    head = newNode;
  } else {
    Nodes::SingleLinkNode<T> *current = head;
    for (size_t i = 0; i < index - 1; ++i) {
      current = current->getNext();
    }
    newNode->setNext(current->getNext());
    current->setNext(newNode);
  }

  size++;
  return true;
}

// Remove an element at a specific index
template <typename T> std::optional<T> SinglyLinkedList<T>::remove(size_t index) {
  if (index >= size) {
    //throw std::out_of_range("Index out of bounds");
    return std::nullopt;
  }

  std::cout << " destructor: " << std::endl;
  Nodes::SingleLinkNode<T> *nodeToRemove = head;
  T data;

  if (index == 0) {
    data = head->getData();
    head = head->getNext();
  } else {
    Nodes::SingleLinkNode<T> *current = head;
    for (size_t i = 0; i < index - 1; ++i) {
      current = current->getNext();
    }
    nodeToRemove = current->getNext();
    data = nodeToRemove->getData();
    current->setNext(nodeToRemove->getNext());
  }

  delete nodeToRemove;
  size--;
  return data;
}

// Remove the first occurrence of an element
template <typename T> bool SinglyLinkedList<T>::remove(T data) {
  if (isEmpty()) {
    return false;
  }

  if (head->getData() == data) {
    Nodes::SingleLinkNode<T> *temp = head;
    head = head->getNext();
    delete temp;
    size--;
    return true;
  }

  Nodes::SingleLinkNode<T> *current = head;
  while (current->getNext() != nullptr &&
         current->getNext()->getData() != data) {
    current = current->getNext();
  }

  if (current->getNext() != nullptr) {
    Nodes::SingleLinkNode<T> *nodeToRemove = current->getNext();
    current->setNext(nodeToRemove->getNext());
    delete nodeToRemove;
    size--;
    return true;
  }

  return false; // Element not found
}

// Check if the list contains an element
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

// Get the element at a specific index
template <typename T> std::optional<T> SinglyLinkedList<T>::get(size_t index) const {
  if (index >= size) {
    //throw std::out_of_range("Index out of bounds");o
    Error e = {"Index out of bounds", __FILE__, __FUNCTION__, __LINE__};
    report_error(e);
    return std::nullopt;
  }

  Nodes::SingleLinkNode<T> *current = head;
  for (size_t i = 0; i < index; ++i) {
    current = current->getNext();
  }

  return current->getData();
}

// Set the element at a specific index and return the old value
template <typename T> std::optional<T> SinglyLinkedList<T>::set(size_t index, T data) {
  if (index >= size) {
    //throw std::out_of_range("Index out of bounds");
    Error e = {"Index out of bounds", __FILE__, __FUNCTION__, __LINE__};
    report_error(e);
    return std::nullopt;
  }

  Nodes::SingleLinkNode<T> *current = head;
  for (size_t i = 0; i < index; ++i) {
    current = current->getNext();
  }

  T oldData = current->getData();
  current->setData(data);
  return oldData;
}

// Get the index of the first occurrence of an element
template <typename T> size_t SinglyLinkedList<T>::indexOf(T data) const {
  Nodes::SingleLinkNode<T> *current = head;
  size_t index = 0;

  while (current != nullptr) {
    if (current->getData() == data) {
      return index;
    }
    current = current->getNext();
    index++;
  }

  return -1; // Element not found
}

// Get the index of the last occurrence of an element
template <typename T> size_t SinglyLinkedList<T>::lastIndexOf(T data) const {
  Nodes::SingleLinkNode<T> *current = head;
  size_t lastIndex = -1;
  size_t index = 0;

  while (current != nullptr) {
    if (current->getData() == data) {
      lastIndex = index;
    }
    current = current->getNext();
    index++;
  }

  return lastIndex;
}

// Check if the list is empty
template <typename T> bool SinglyLinkedList<T>::isEmpty() const {
  return size == 0;
}

// Get the size of the list
template <typename T> size_t SinglyLinkedList<T>::getSize() const {
  return size;
}

// Clear the list
template <typename T> void SinglyLinkedList<T>::clear() {
  //  Loop through the list and delete each node
  while (head != nullptr) {
    Nodes::SingleLinkNode<T> *current = head;
    head = head->getNext(); // Move head to the next node
    delete current;         // Delete the current node
  }
  size = 0; // Reset the size to 0
}

/*
 * DoublyLinkedList
 */
template <typename T> class DoublyLinkedList : public ListAdt<T> {
private:
  Nodes::DoubleLinkNode<T> *head;
  Nodes::DoubleLinkNode<T> *tail;
  size_t size;

public:
  DoublyLinkedList();
  ~DoublyLinkedList();

  bool add(T data) override;
  bool add(size_t index, T data) override;

  std::optional<T> remove(size_t index) override;
  bool remove(T data) override;

  bool contains(T data) const override;

  std::optional<T> get(size_t index) const override;
  std::optional<T> set(size_t index, T data) override;

  size_t indexOf(T data) const override;
  size_t lastIndexOf(T data) const override;

  bool isEmpty() const override;
  size_t getSize() const override;
  void clear() override;
};

template <typename T> ListAdt<T> *createDoublyLinkedList() {
  return new DoublyLinkedList<T>();
}

// Constructor
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList()
    : head(nullptr), tail(nullptr), size(0) {}

// Destructor
template <typename T> DoublyLinkedList<T>::~DoublyLinkedList() {
  Lists::DoublyLinkedList<T>::clear();
}

// Add an element to the end of the list
template <typename T> bool DoublyLinkedList<T>::add(T data) {
  Nodes::DoubleLinkNode<T> *newNode = new Nodes::DoubleLinkNode<T>(data);

  if (isEmpty()) {
    head = newNode;
    tail = newNode;
  } else {
    tail->setNext(newNode);
    newNode->setPrev(tail);
    tail = newNode;
  }

  size++;
  return true;
}

// Add an element at a specific index
template <typename T> bool DoublyLinkedList<T>::add(size_t index, T data) {
  if (index > size) {
    throw std::out_of_range("Index out of bounds");
  }

  Nodes::DoubleLinkNode<T> *newNode = new Nodes::DoubleLinkNode<T>(data);

  if (index == 0) {
    newNode->setNext(head);
    if (head) {
      head->setPrev(newNode);
    }
    head = newNode;
    if (size == 0) {
      tail = newNode; // If list was empty
    }
  } else if (index == size) {
    add(data); // Adding at the end
    return true;
  } else {
    Nodes::DoubleLinkNode<T> *current = head;
    for (size_t i = 0; i < index; ++i) {
      current = current->getNext();
    }
    newNode->setNext(current);
    newNode->setPrev(current->getPrev());
    if (current->getPrev()) {
      current->getPrev()->setNext(newNode);
    }
    current->setPrev(newNode);
  }

  size++;
  return true;
}

// Remove an element at a specific index
template <typename T> std::optional<T> DoublyLinkedList<T>::remove(size_t index) {
  if (index > size) {
    //throw std::out_of_range("Index out of bounds");
    Error e = {"Index out of bounds", __FILE__, __FUNCTION__, __LINE__};
    report_error(e);
    return std::nullopt;
  }

  Nodes::DoubleLinkNode<T> *nodeToRemove = head;

  if (index == 0) {
    T data = head->getData();
    head = head->getNext();
    if (head) {
      head->setPrev(nullptr);
    } else {
      tail = nullptr; // List is now empty
    }
    delete nodeToRemove;
    size--;
    return data;
  }

  nodeToRemove = head;
  for (size_t i = 0; i < index; ++i) {
    nodeToRemove = nodeToRemove->getNext();
  }

  T data = nodeToRemove->getData();
  if (nodeToRemove->getPrev()) {
    nodeToRemove->getPrev()->setNext(nodeToRemove->getNext());
  }
  if (nodeToRemove->getNext()) {
    nodeToRemove->getNext()->setPrev(nodeToRemove->getPrev());
  }
  if (nodeToRemove == tail) {
    tail = nodeToRemove->getPrev();
  }
  delete nodeToRemove;
  size--;
  return data;
}

// Remove the first occurrence of an element
template <typename T> bool DoublyLinkedList<T>::remove(T data) {
  Nodes::DoubleLinkNode<T> *current = head;

  while (current != nullptr) {
    if (current->getData() == data) {
      if (current == head) {
        head = current->getNext();
        if (head) {
          head->setPrev(nullptr);
        } else {
          tail = nullptr;
        }
      } else if (current == tail) {
        tail = current->getPrev();
        tail->setNext(nullptr);
      } else {
        current->getPrev()->setNext(current->getNext());
        current->getNext()->setPrev(current->getPrev());
      }

      delete current;
      size--;
      return true;
    }
    current = current->getNext();
  }
  return false; // Element not found
}

// Check if the list contains an element
template <typename T> bool DoublyLinkedList<T>::contains(T data) const {
  Nodes::DoubleLinkNode<T> *current = head;
  while (current != nullptr) {
    if (current->getData() == data) {
      return true;
    }
    current = current->getNext();
  }
  return false;
}

// Get the element at a specific index
template <typename T> std::optional<T> DoublyLinkedList<T>::get(size_t index) const {
  if (index >= size) {
    //throw std::out_of_range("Index out of bounds");
    Error e = {"Index out of bounds", __FILE__, __FUNCTION__, __LINE__};
    report_error(e);
    return std::nullopt;
  }

  Nodes::DoubleLinkNode<T> *current = head;
  for (size_t i = 0; i < index; ++i) {
    current = current->getNext();
  }

  return current->getData();
}

// Set the element at a specific index and return the old value
template <typename T> std::optional<T> DoublyLinkedList<T>::set(size_t index, T data) {
  if (index >= size) {
    //throw std::out_of_range("Index out of bounds");
    Error e = {"Index out of bounds", __FILE__, __FUNCTION__, __LINE__};
    report_error(e);
    return std::nullopt;
  }

  Nodes::DoubleLinkNode<T> *current = head;
  for (size_t i = 0; i < index; ++i) {
    current = current->getNext();
  }

  T oldData = current->getData();
  current->setData(data);
  return oldData;
}

// Get the index of the first occurrence of an element
template <typename T> size_t DoublyLinkedList<T>::indexOf(T data) const {
  Nodes::DoubleLinkNode<T> *current = head;
  size_t index = 0;

  while (current != nullptr) {
    if (current->getData() == data) {
      return index;
    }
    current = current->getNext();
    index++;
  }

  return -1; // Element not found
}

// Get the index of the last occurrence of an element
template <typename T> size_t DoublyLinkedList<T>::lastIndexOf(T data) const {
  Nodes::DoubleLinkNode<T> *current = tail;
  size_t index = size - 1;

  while (current != nullptr) {
    if (current->getData() == data) {
      return index;
    }
    current = current->getPrev();
    index--;
  }

  return -1; // Element not found
}

// Check if the list is empty
template <typename T> bool DoublyLinkedList<T>::isEmpty() const {
  return size == 0;
}

// Get the size of the list
template <typename T> size_t DoublyLinkedList<T>::getSize() const {
  return size;
}

// Clear the list
template <typename T> void DoublyLinkedList<T>::clear() {
  // Loop through the list and delete each node
  while (head != nullptr) {
    Nodes::DoubleLinkNode<T> *current = head;
    head = head->getNext(); // Move head to the next node
    delete current;         // Delete the current node
  }
  size = 0; // Reset the size to 0
}

/*
 * CircularLinkedList
 */

template <typename T> class CircularLinkedList : public ListAdt<T> {
private:
  Nodes::SingleLinkNode<T> *head;
  size_t size;

public:
  CircularLinkedList();
  virtual ~CircularLinkedList();

  bool add(T data) override;
  bool add(size_t index, T data) override;

  std::optional<T> remove(size_t index) override;
  bool remove(T data) override;

  bool contains(T data) const override;

  std::optional<T> get(size_t index) const override;
  std::optional<T> set(size_t index, T data) override;

  size_t indexOf(T data) const override;
  size_t lastIndexOf(T data) const override;

  bool isEmpty() const override;
  size_t getSize() const override;
  void clear() override;
};

template <typename T> ListAdt<T> *createCircularLinkedList() {
  return new CircularLinkedList<T>();
}

// Constructor
template <typename T>
CircularLinkedList<T>::CircularLinkedList() : head(nullptr), size(0) {}

// Destructor
template <typename T> CircularLinkedList<T>::~CircularLinkedList() {
  Lists::CircularLinkedList<T>::clear();
}

// Add an element to the end of the list
template <typename T> bool CircularLinkedList<T>::add(T data) {
  Nodes::SingleLinkNode<T> *newNode = new Nodes::SingleLinkNode<T>(data);

  if (isEmpty()) {
    head = newNode;
    newNode->setNext(head); // Circular link
  } else {
    Nodes::SingleLinkNode<T> *current = head;
    while (current->getNext() != head) {
      current = current->getNext();
    }
    current->setNext(newNode);
    newNode->setNext(head); // Complete the circle
  }

  size++;
  return true;
}

// Add an element at a specific index
template <typename T> bool CircularLinkedList<T>::add(size_t index, T data) {
  if (index > size) {
    throw std::out_of_range("Index out of bounds");
  }

  Nodes::SingleLinkNode<T> *newNode = new Nodes::SingleLinkNode<T>(data);

  if (index == 0) {
    if (isEmpty()) {
      head = newNode;
      newNode->setNext(head); // Point to itself
    } else {
      newNode->setNext(head);
      Nodes::SingleLinkNode<T> *current = head;
      while (current->getNext() != head) {
        current = current->getNext();
      }
      current->setNext(newNode);
      head = newNode; // Update the head
    }
  } else {
    Nodes::SingleLinkNode<T> *current = head;
    for (size_t i = 0; i < index - 1; ++i) {
      current = current->getNext();
    }
    newNode->setNext(current->getNext());
    current->setNext(newNode);
  }

  size++;
  return true;
}

// Remove an element at a specific index
template <typename T> std::optional<T> CircularLinkedList<T>::remove(size_t index) {
  if (index > size) {
    //throw std::out_of_range("Index out of bounds");
    Error e = {"Index out of bounds", __FILE__, __FUNCTION__, __LINE__};
    report_error(e);
    return std::nullopt;
  }

  Nodes::SingleLinkNode<T> *nodeToRemove = head;
  T data;

  if (index == 0) {
    data = head->getData();
    if (size == 1) {
      delete head;
      head = nullptr;
    } else {
      Nodes::SingleLinkNode<T> *current = head;
      while (current->getNext() != head) {
        current = current->getNext();
      }
      nodeToRemove = head;
      head = head->getNext();
      current->setNext(head); // Update circular link
      delete nodeToRemove;
    }
  } else {
    Nodes::SingleLinkNode<T> *current = head;
    for (size_t i = 0; i < index - 1; ++i) {
      current = current->getNext();
    }
    nodeToRemove = current->getNext();
    data = nodeToRemove->getData();
    current->setNext(nodeToRemove->getNext());
    delete nodeToRemove;
  }

  size--;
  return data;
}

// Remove an element by value
template <typename T> bool CircularLinkedList<T>::remove(T data) {
  if (isEmpty()) {
    return false;
  }

  if (head->getData() == data) {
    remove(0);
    return true;
  }

  Nodes::SingleLinkNode<T> *current = head;
  do {
    if (current->getNext()->getData() == data) {
      Nodes::SingleLinkNode<T> *nodeToRemove = current->getNext();
      current->setNext(nodeToRemove->getNext());
      delete nodeToRemove;
      size--;
      return true;
    }
    current = current->getNext();
  } while (current != head);

  return false; // Element not found
}

// Check if the list contains a specific element
template <typename T> bool CircularLinkedList<T>::contains(T data) const {
  if (isEmpty()) {
    return false;
  }

  Nodes::SingleLinkNode<T> *current = head;
  do {
    if (current->getData() == data) {
      return true;
    }
    current = current->getNext();
  } while (current != head);

  return false;
}

// Get the element at a specific index
template <typename T> std::optional<T> CircularLinkedList<T>::get(size_t index) const {
  if (index >= size) {
    //throw std::out_of_range("Index out of bounds");
    Error e = {"Index out of bounds", __FILE__, __FUNCTION__, __LINE__};
    report_error(e);
    return std::nullopt;
  }

  Nodes::SingleLinkNode<T> *current = head;
  for (size_t i = 0; i < index; ++i) {
    current = current->getNext();
  }

  return current->getData();
}

// Set the element at a specific index and return the old value
template <typename T> std::optional<T> CircularLinkedList<T>::set(size_t index, T data) {
  if (index >= size) {
    //throw std::out_of_range("Index out of bounds");
    Error e = {"Index out of bounds", __FILE__, __FUNCTION__, __LINE__};
    report_error(e);
    return std::nullopt;
  }

  Nodes::SingleLinkNode<T> *current = head;
  for (size_t i = 0; i < index; ++i) {
    current = current->getNext();
  }

  T oldData = current->getData();
  current->setData(data);
  return oldData;
}

// Get the index of the first occurrence of an element
template <typename T> size_t CircularLinkedList<T>::indexOf(T data) const {
  if (isEmpty()) {
    return -1;
  }

  Nodes::SingleLinkNode<T> *current = head;
  size_t index = 0;
  do {
    if (current->getData() == data) {
      return index;
    }
    current = current->getNext();
    index++;
  } while (current != head);

  return -1; // Element not found
}

// Get the index of the last occurrence of an element
template <typename T> size_t CircularLinkedList<T>::lastIndexOf(T data) const {
  if (isEmpty()) {
    return -1;
  }

  Nodes::SingleLinkNode<T> *current = head;
  size_t lastIndex = -1;
  size_t index = 0;
  do {
    if (current->getData() == data) {
      lastIndex = index;
    }
    current = current->getNext();
    index++;
  } while (current != head);

  return lastIndex;
}

// Check if the list is empty
template <typename T> bool CircularLinkedList<T>::isEmpty() const {
  return size == 0;
}

// Get the size of the list
template <typename T> size_t CircularLinkedList<T>::getSize() const {
  return size;
}

// Clear the list by removing all elements
template <typename T> void CircularLinkedList<T>::clear() {
  if (head == nullptr) {
    return; // List is already empty
  }

  // Use a pointer to traverse the list
  Nodes::SingleLinkNode<T> *current = head;
  Nodes::SingleLinkNode<T> *nextNode = nullptr;

  // Break the circular link to prevent infinite loops
  do {
    nextNode = current->getNext();
    delete current;
    current = nextNode;
  } while (current != head); // Stop when we've looped back to the head

  // After deleting all nodes, reset the list
  head = nullptr;
  size = 0;
}

/*
 *
 * Iterators
 *
 *
 */
template <typename T> class SinglyLinkedListForwardIterator {

public:
  using iterator_category = std::forward_iterator_tag;
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = T *;
  using reference = T &;

  explicit SinglyLinkedListForwardIterator(Nodes::SingleLinkNode<T> *node)
      : current(node) {}

  reference operator*() const { return current->data; }

  pointer operator->() { return &current->data; }

  SinglyLinkedListForwardIterator &operator++() {
    current = current->getNext();
    return *this;
  }

  SinglyLinkedListForwardIterator operator++(int) {
    SinglyLinkedListForwardIterator iterator = *this;
    ++(*this);
    return iterator;
  }

  bool operator==(const SinglyLinkedListForwardIterator &iterator) const {
    return current == iterator.current;
  }

  bool operator!=(const SinglyLinkedListForwardIterator &iterator) const {
    return !(*this == iterator);
  }

private:
  Nodes::SingleLinkNode<T> *current;
};

template <typename T> class SinglyLinkedListRandomAccessIterator {
public:
  using iterator_category = std::random_access_iterator_tag;
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = T *;
  using reference = T &;

  explicit SinglyLinkedListRandomAccessIterator(Nodes::SingleLinkNode<T> *node,
                                                Nodes::SingleLinkNode<T> *head)
      : current(node), head(head) {
    std::cout << "constructor: current " << std::hex << current << std::endl;
    std::cout << "constructor: head " << std::hex << head << std::endl;
  }

  // dereference operator at current position of iterator
  reference operator*() const {
    std::cout << "operator*: " << std::endl;
    if (current == nullptr) {
      std::cout << "operator*: current is nullptr" << std::endl;
      throw std::out_of_range("Index out of bounds");
    }
    std::cout << "operator*: current: " << std::hex << current << std::endl;
    std::cout << "operator*: current->data: " << current->data << std::endl;
    return current->data;
  }

  // member access operator at current position of iterator
  pointer operator->() {
    std::cout << "operator->: " << std::endl;
    if (current == nullptr) {
      std::cout << "operator->: current is nullptr" << std::endl;
      throw std::out_of_range("Index out of bounds");
    }
    std::cout << "operator->: current: " << std::hex << current << std::endl;
    std::cout << "operator->: current->data: " << current->data << std::endl;
    return &current->data;
  }

  // pre-increment operator, move iterator to next position
  SinglyLinkedListRandomAccessIterator &operator++() {
    std::cout << "operator++: " << std::endl;
    current = current->getNext();
    return *this;
  }

  // post-increment operator, store copy of iterator, move iterator to next
  // position, return copy
  SinglyLinkedListRandomAccessIterator operator++(int) {
    std::cout << "operator++(int): " << std::endl;
    SinglyLinkedListRandomAccessIterator iterator = *this;
    ++(*this);
    return iterator;
  }

  // pre-decrement operator, move iterator to previous position
  SinglyLinkedListRandomAccessIterator &operator--() {
    std::cout << "operator--[top]: " << std::endl;
    std::cout << "operator--[top] current: " << std::hex << current
              << std::endl;
    std::cout << "operator--[top] head: " << std::hex << current << std::endl;
    Nodes::SingleLinkNode<T> *temp = head;
    while (temp && temp != current) {
      temp = temp->next;
      std::cout << "operator--[loop] temp: " << std::hex << temp << std::endl;
    }
    current = temp;
    return *this;
  }

  SinglyLinkedListRandomAccessIterator operator--(int) {
    std::cout << "operator--(int)[top]: " << std::endl;
    SinglyLinkedListRandomAccessIterator iterator = *this;
    --(*this);
    std::cout << "operator--(int)[bottom]: " << std::endl;
    return iterator;
  }

  bool operator==(const SinglyLinkedListRandomAccessIterator &iterator) const {
    std::cout << "operator==: " << std::endl;
    std::cout << "operator==: current " << std::hex << current << std::endl;
    std::cout << "operator==: iterator.current " << std::hex << iterator.current
              << std::endl;
    bool result = current == iterator.current;
    std::cout << "operator==: result " << std::boolalpha << result << std::endl;
    return result;
  }

  bool operator!=(const SinglyLinkedListRandomAccessIterator &iterator) const {
    std::cout << "operator!=: " << std::endl;
    std::cout << "operator!=: current " << std::hex << current << std::endl;
    std::cout << "operator!=: iterator.current " << std::hex << iterator.current
              << std::endl;

    bool result = current != iterator.current;

    std::cout << "operator!=: result " << std::boolalpha << result << std::endl;
    return result;
  }

  bool operator<(const SinglyLinkedListRandomAccessIterator &iterator) const {
    std::cout << "operator<: " << std::endl;
    return current < iterator.current;
  }

  bool operator>(const SinglyLinkedListRandomAccessIterator &iterator) const {
    std::cout << "operator>: " << std::endl;
    return current > iterator.current;
  }

  SinglyLinkedListRandomAccessIterator &operator+=(difference_type n) {
    std::cout << "operator+=[top]: += n " << n << std::endl;
    for (difference_type i = 0; i < n; ++i) {
      current = current->getNext();
      std::cout << "operator+=[loop]: " << std::endl;
    }
    return *this;
  }

  SinglyLinkedListRandomAccessIterator operator+(difference_type n) {
    std::cout << "operator+: + n " << n << std::endl;
    for (difference_type i = 0; i < n; ++i) {
      current = current->getNext();
      std::cout << "operator+[loop]: " << std::hex << current<< std::endl;
    }
    return *this;
  }

  friend SinglyLinkedListRandomAccessIterator
  operator+(difference_type n,
            const SinglyLinkedListRandomAccessIterator &iterator) {
    std::cout << "operator+ friend: + n " << n << std::endl;
    for (difference_type i = 0; i < n; ++i) {
      iterator.current = iterator.current->getNext();
      std::cout << "operator+friend[loop]: " << std::hex << iterator.current<< std::endl;
    }
    return iterator;
  }

  SinglyLinkedListRandomAccessIterator &operator-=(difference_type n) {
    std::cout << "operator-=: Top " << std::endl;
    std::cout << "operator-=: "
              << " Difference " << n << std::endl;
    for (difference_type i = 0; i < n; ++i) {
      auto temp = head;
      while (temp->getNext() != current) {
        temp = temp->getNext();
        std::cout << "operator-=: Loop " << std::endl;
      }
      current = temp;
    }
    std::cout << "operator-=: Bottom " << std::endl;
    std::cout << "operator-=: "
              << "Current: " << std::hex << current << std::endl;
    return *this;
  }

  SinglyLinkedListRandomAccessIterator operator-(difference_type n) {
    std::cout << "operator-1: " << std::endl;
    std::cout << "operator-1: "
              << " Difference " << n << std::endl;
    for (difference_type i = 0; i < n; ++i) {
      auto temp = head;
      while (temp->getNext() != current) {
        temp = temp->getNext();
        std::cout << "operator-1: Loop " << std::endl;
      }
      current = temp;
    }
    std::cout << "operator-1: Bottom " << std::endl;
    std::cout << "operator-1: "
              << "Current: " << std::hex << current << std::endl;
    std::cout << "operator-1: "
              << "Head: " << std::hex << head << std::endl;
    return *this;
  }

  difference_type
  operator-(const SinglyLinkedListRandomAccessIterator &iterator) {
    std::cout << "operator-(refT) Top: " << std::endl;
    std::cout << "operator-(refT): current " << current << std::endl;
    std::cout << "operator-(refT): iterator.current " << iterator.current
              << std::endl;
    difference_type count = 0;
    Nodes::SingleLinkNode<T> *temp = current;
    while (temp != nullptr && temp != iterator.current) {
      std::cout << "operator-(refT) Loop: " << std::endl;
      std::cout << "operator-(refT) loop: current " << std::hex << current << std::endl;
      std::cout << "operator-(refT) loop: iterator.current " << std::hex << iterator.current
                << std::endl;
      temp = temp->getNext();
      count++;
    }
    std::cout << "operator-(refT) bottom: " << std::endl;
    std::cout << "operator-(refT) bottom: Count " << count << std::endl;
    return count;
  }

private:
  Nodes::SingleLinkNode<T> *current;
  Nodes::SingleLinkNode<T> *head;
};

} // namespace Lists
#endif // LIST_H
