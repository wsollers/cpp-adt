#ifndef LIST_H
#define LIST_H

#include "../node/node.h"
#include <stdexcept>  // std::out_of_range

struct oogabooga {
  int a;
  int b;
};

/*
*/
namespace Lists {

template <typename T> class ListAdt {
public:
  ListAdt() {}
  virtual ~ListAdt() {}

  virtual bool add(T data) = 0;
  virtual bool add(size_t index, T data) = 0;

  virtual T remove(size_t index) = 0;
  virtual bool remove(T data) = 0;

  virtual bool contains(T data) const = 0;

  virtual T get(size_t index) const = 0;
  virtual T set(size_t index, T data) = 0;

  virtual size_t indexOf(T data) const = 0;
  virtual size_t lastIndexOf(T data) const = 0;

  virtual bool isEmpty() const = 0;
  virtual size_t getSize() const = 0;
  virtual void clear() = 0;
};

template <typename T> class SinglyLinkedList : public ListAdt<T> {
private:
  Nodes::SingleLinkNode<T> *head;
  size_t size;

public:
  SinglyLinkedList();
  ~SinglyLinkedList();

  bool add(T data) override;
  bool add(size_t index, T data) override;

  T remove(size_t index) override;
  bool remove(T data) override;

  bool contains(T data) const override;

  T get(size_t index) const override;
  T set(size_t index, T data) override;

  size_t indexOf(T data) const override;
  size_t lastIndexOf(T data) const override;

  bool isEmpty() const override;
  size_t getSize() const override; 
  void clear() override;

};

template <typename T> ListAdt<T> *createSingleLinkList() {
  return new SinglyLinkedList<T>();
}

// Constructor
template <typename T>
SinglyLinkedList<T>::SinglyLinkedList() : head(nullptr), size(0) {}

// Destructor
template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
  Lists::SinglyLinkedList<T>::clear();
}

// Add an element to the end of the list
template <typename T>
bool SinglyLinkedList<T>::add(T data) {
    Nodes::SingleLinkNode<T>* newNode = new Nodes::SingleLinkNode<T>(data);

    if (isEmpty()) {
        head = newNode;
    } else {
        Nodes::SingleLinkNode<T>* current = head;
        while (current->getNext() != nullptr) {
            current = current->getNext();
        }
        current->setNext(newNode);
    }

    size++;
    return true;
}

// Add an element at a specific index
template <typename T>
bool SinglyLinkedList<T>::add(size_t index, T data) {
    if (index > size) {
        throw std::out_of_range("Index out of bounds");
    }

    Nodes::SingleLinkNode<T>* newNode = new Nodes::SingleLinkNode<T>(data);

    if (index == 0) {
        newNode->setNext(head);
        head = newNode;
    } else {
        Nodes::SingleLinkNode<T>* current = head;
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
template <typename T>
T SinglyLinkedList<T>::remove(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of bounds");
    }

    Nodes::SingleLinkNode<T>* nodeToRemove = head;
    T data;

    if (index == 0) {
        data = head->getData();
        head = head->getNext();
    } else {
        Nodes::SingleLinkNode<T>* current = head;
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
template <typename T>
bool SinglyLinkedList<T>::remove(T data) {
    if (isEmpty()) {
        return false;
    }

    if (head->getData() == data) {
        Nodes::SingleLinkNode<T>* temp = head;
        head = head->getNext();
        delete temp;
        size--;
        return true;
    }

    Nodes::SingleLinkNode<T>* current = head;
    while (current->getNext() != nullptr && current->getNext()->getData() != data) {
        current = current->getNext();
    }

    if (current->getNext() != nullptr) {
        Nodes::SingleLinkNode<T>* nodeToRemove = current->getNext();
        current->setNext(nodeToRemove->getNext());
        delete nodeToRemove;
        size--;
        return true;
    }

    return false;  // Element not found
}

// Check if the list contains an element
template <typename T>
bool SinglyLinkedList<T>::contains(T data) const {
    Nodes::SingleLinkNode<T>* current = head;
    while (current != nullptr) {
        if (current->getData() == data) {
            return true;
        }
        current = current->getNext();
    }
    return false;
}

// Get the element at a specific index
template <typename T>
T SinglyLinkedList<T>::get(size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of bounds");
    }

    Nodes::SingleLinkNode<T>* current = head;
    for (size_t i = 0; i < index; ++i) {
        current = current->getNext();
    }

    return current->getData();
}

// Set the element at a specific index and return the old value
template <typename T>
T SinglyLinkedList<T>::set(size_t index, T data) {
    if (index >= size) {
        throw std::out_of_range("Index out of bounds");
    }

    Nodes::SingleLinkNode<T>* current = head;
    for (size_t i = 0; i < index; ++i) {
        current = current->getNext();
    }

    T oldData = current->getData();
    current->setData(data);
    return oldData;
}

// Get the index of the first occurrence of an element
template <typename T>
size_t SinglyLinkedList<T>::indexOf(T data) const {
    Nodes::SingleLinkNode<T>* current = head;
    size_t index = 0;

    while (current != nullptr) {
        if (current->getData() == data) {
            return index;
        }
        current = current->getNext();
        index++;
    }

    return -1;  // Element not found
}

// Get the index of the last occurrence of an element
template <typename T>
size_t SinglyLinkedList<T>::lastIndexOf(T data) const {
    Nodes::SingleLinkNode<T>* current = head;
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
template <typename T>
bool SinglyLinkedList<T>::isEmpty() const {
    return size == 0;
}

// Get the size of the list
template <typename T>
size_t SinglyLinkedList<T>::getSize() const {
    return size;
}

// Clear the list
template <typename T>
void SinglyLinkedList<T>::clear() {
    while (!isEmpty()) {
        remove(0);  // Repeatedly remove the head node
    }
}


/*
 * DoublyLinkedList
 */
template <typename T>
class DoublyLinkedList : public ListAdt<T> {
private:
    Nodes::DoubleLinkNode<T>* head;
    Nodes::DoubleLinkNode<T>* tail;
    size_t size;

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    bool add(T data) override;
    bool add(size_t index, T data) override;

    T remove(size_t index) override;
    bool remove(T data) override;

    bool contains(T data) const override;

    T get(size_t index) const override;
    T set(size_t index, T data) override;

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
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

// Destructor
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
  Lists::DoublyLinkedList<T>::clear();
}

// Add an element to the end of the list
template <typename T>
bool DoublyLinkedList<T>::add(T data) {
    Nodes::DoubleLinkNode<T>* newNode = new Nodes::DoubleLinkNode<T>(data);

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
template <typename T>
bool DoublyLinkedList<T>::add(size_t index, T data) {
    if (index > size) {
        throw std::out_of_range("Index out of bounds");
    }

    Nodes::DoubleLinkNode<T>* newNode = new Nodes::DoubleLinkNode<T>(data);

    if (index == 0) {
        newNode->setNext(head);
        if (head) {
            head->setPrev(newNode);
        }
        head = newNode;
        if (size == 0) {
            tail = newNode;  // If list was empty
        }
    } else if (index == size) {
        add(data);  // Adding at the end
        return true;
    } else {
        Nodes::DoubleLinkNode<T>* current = head;
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
template <typename T>
T DoublyLinkedList<T>::remove(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of bounds");
    }

    Nodes::DoubleLinkNode<T>* nodeToRemove = head;

    if (index == 0) {
        T data = head->getData();
        head = head->getNext();
        if (head) {
            head->setPrev(nullptr);
        } else {
            tail = nullptr;  // List is now empty
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
template <typename T>
bool DoublyLinkedList<T>::remove(T data) {
    Nodes::DoubleLinkNode<T>* current = head;

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
    return false;  // Element not found
}

// Check if the list contains an element
template <typename T>
bool DoublyLinkedList<T>::contains(T data) const {
    Nodes::DoubleLinkNode<T>* current = head;
    while (current != nullptr) {
        if (current->getData() == data) {
            return true;
        }
        current = current->getNext();
    }
    return false;
}

// Get the element at a specific index
template <typename T>
T DoublyLinkedList<T>::get(size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of bounds");
    }

    Nodes::DoubleLinkNode<T>* current = head;
    for (size_t i = 0; i < index; ++i) {
        current = current->getNext();
    }

    return current->getData();
}

// Set the element at a specific index and return the old value
template <typename T>
T DoublyLinkedList<T>::set(size_t index, T data) {
    if (index >= size) {
        throw std::out_of_range("Index out of bounds");
    }

    Nodes::DoubleLinkNode<T>* current = head;
    for (size_t i = 0; i < index; ++i) {
        current = current->getNext();
    }

    T oldData = current->getData();
    current->setData(data);
    return oldData;
}

// Get the index of the first occurrence of an element
template <typename T>
size_t DoublyLinkedList<T>::indexOf(T data) const {
    Nodes::DoubleLinkNode<T>* current = head;
    size_t index = 0;

    while (current != nullptr) {
        if (current->getData() == data) {
            return index;
        }
        current = current->getNext();
        index++;
    }

    return -1;  // Element not found
}

// Get the index of the last occurrence of an element
template <typename T>
size_t DoublyLinkedList<T>::lastIndexOf(T data) const {
    Nodes::DoubleLinkNode<T>* current = tail;
    size_t index = size - 1;

    while (current != nullptr) {
        if (current->getData() == data) {
            return index;
        }
        current = current->getPrev();
        index--;
    }

    return -1;  // Element not found
}

// Check if the list is empty
template <typename T>
bool DoublyLinkedList<T>::isEmpty() const {
    return size == 0;
}

// Get the size of the list
template <typename T>
size_t DoublyLinkedList<T>::getSize() const {
    return size;
}

// Clear the list
template <typename T>
void DoublyLinkedList<T>::clear() {
    while (!isEmpty()) {
        remove(0);  // Remove each element starting from the head
    }
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

  T remove(size_t index) override;
  bool remove(T data) override;

  bool contains(T data) const override;

  T get(size_t index) const override;
  T set(size_t index, T data) override;

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
template <typename T>
CircularLinkedList<T>::~CircularLinkedList() {
  Lists::CircularLinkedList<T>::clear();
}

// Add an element to the end of the list
template <typename T>
bool CircularLinkedList<T>::add(T data) {
    Nodes::SingleLinkNode<T>* newNode = new Nodes::SingleLinkNode<T>(data);

    if (isEmpty()) {
        head = newNode;
        newNode->setNext(head);  // Circular link
    } else {
        Nodes::SingleLinkNode<T>* current = head;
        while (current->getNext() != head) {
            current = current->getNext();
        }
        current->setNext(newNode);
        newNode->setNext(head);  // Complete the circle
    }

    size++;
    return true;
}

// Add an element at a specific index
template <typename T>
bool CircularLinkedList<T>::add(size_t index, T data) {
    if (index > size) {
        throw std::out_of_range("Index out of bounds");
    }

    Nodes::SingleLinkNode<T>* newNode = new Nodes::SingleLinkNode<T>(data);

    if (index == 0) {
        if (isEmpty()) {
            head = newNode;
            newNode->setNext(head);  // Point to itself
        } else {
            newNode->setNext(head);
            Nodes::SingleLinkNode<T>* current = head;
            while (current->getNext() != head) {
                current = current->getNext();
            }
            current->setNext(newNode);
            head = newNode;  // Update the head
        }
    } else {
        Nodes::SingleLinkNode<T>* current = head;
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
template <typename T>
T CircularLinkedList<T>::remove(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of bounds");
    }

    Nodes::SingleLinkNode<T>* nodeToRemove = head;
    T data;

    if (index == 0) {
        data = head->getData();
        if (size == 1) {
            delete head;
            head = nullptr;
        } else {
            Nodes::SingleLinkNode<T>* current = head;
            while (current->getNext() != head) {
                current = current->getNext();
            }
            nodeToRemove = head;
            head = head->getNext();
            current->setNext(head);  // Update circular link
            delete nodeToRemove;
        }
    } else {
        Nodes::SingleLinkNode<T>* current = head;
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
template <typename T>
bool CircularLinkedList<T>::remove(T data) {
    if (isEmpty()) {
        return false;
    }

    if (head->getData() == data) {
        remove(0);
        return true;
    }

    Nodes::SingleLinkNode<T>* current = head;
    do {
        if (current->getNext()->getData() == data) {
            Nodes::SingleLinkNode<T>* nodeToRemove = current->getNext();
            current->setNext(nodeToRemove->getNext());
            delete nodeToRemove;
            size--;
            return true;
        }
        current = current->getNext();
    } while (current != head);

    return false;  // Element not found
}

// Check if the list contains a specific element
template <typename T>
bool CircularLinkedList<T>::contains(T data) const {
    if (isEmpty()) {
        return false;
    }

    Nodes::SingleLinkNode<T>* current = head;
    do {
        if (current->getData() == data) {
            return true;
        }
        current = current->getNext();
    } while (current != head);

    return false;
}

// Get the element at a specific index
template <typename T>
T CircularLinkedList<T>::get(size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of bounds");
    }

    Nodes::SingleLinkNode<T>* current = head;
    for (size_t i = 0; i < index; ++i) {
        current = current->getNext();
    }

    return current->getData();
}

// Set the element at a specific index and return the old value
template <typename T>
T CircularLinkedList<T>::set(size_t index, T data) {
    if (index >= size) {
        throw std::out_of_range("Index out of bounds");
    }

    Nodes::SingleLinkNode<T>* current = head;
    for (size_t i = 0; i < index; ++i) {
        current = current->getNext();
    }

    T oldData = current->getData();
    current->setData(data);
    return oldData;
}

// Get the index of the first occurrence of an element
template <typename T>
size_t CircularLinkedList<T>::indexOf(T data) const {
    if (isEmpty()) {
        return -1;
    }

    Nodes::SingleLinkNode<T>* current = head;
    size_t index = 0;
    do {
        if (current->getData() == data) {
            return index;
        }
        current = current->getNext();
        index++;
    } while (current != head);

    return -1;  // Element not found
}

// Get the index of the last occurrence of an element
template <typename T>
size_t CircularLinkedList<T>::lastIndexOf(T data) const {
    if (isEmpty()) {
        return -1;
    }

    Nodes::SingleLinkNode<T>* current = head;
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
template <typename T>
bool CircularLinkedList<T>::isEmpty() const {
    return size == 0;
}

// Get the size of the list
template <typename T>
size_t CircularLinkedList<T>::getSize() const {
    return size;
}

// Clear the list by removing all elements
template <typename T>
void CircularLinkedList<T>::clear() {
    while (!isEmpty()) {
        remove(0);
    }
}






}



#endif // LIST_H
