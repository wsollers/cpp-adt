#ifndef QUEUE_H
#define QUEUE_H

#include <array>
#include <cstdlib>
#include <optional>

#include "../node/node.h"

namespace Queues {

template <typename T>
class ArrayQueue {
 public:
  ArrayQueue(size_t capacity) : capacity(capacity), size(0), front(0), rear(0) {
    queue = new T[capacity];
  }

  ~ArrayQueue() { delete[] queue; }

  std::optional<T> dequeue() {
    if (isEmpty()) {
      return std::nullopt;
    }
    T data = queue[front];
    front = (front + 1) % capacity;
    size--;
    return data;
  }

  void enqueue(T data) {
    if (isFull()) {
      return;
    }
    queue[rear] = data;
    rear = (rear + 1) % capacity;
    size++;
  }

  std::optional<T> peek() {
    if (isEmpty()) {
      return std::nullopt;
    }
    return queue[front];
  }

  bool isEmpty() { return size == 0; }

  bool isFull() { return size == capacity; }

  size_t getSize() { return size; }

 private:
  size_t capacity;
  size_t size;
  size_t front;
  size_t rear;
  T *queue;
};

template <typename T>
class LinkedQueue {
 public:
  LinkedQueue() : front(nullptr), rear(nullptr), size(0) {}

  ~LinkedQueue() {
    while (front != nullptr) {
      Nodes::SingleLinkNode<T> *temp = front;
      front = front->getNext();
      delete temp;
    }
  }

  std::optional<T> dequeue() {
    if (isEmpty()) {
      return std::nullopt;
    }
    T data = front->getData();
    Nodes::SingleLinkNode<T> *temp = front;
    front = front->getNext();
    delete temp;
    size--;
    return data;
  }

  void enqueue(T data) {
    Nodes::SingleLinkNode<T> *node = new Nodes::SingleLinkNode<T>(data);
    if (isEmpty()) {
      front = node;
    } else {
      rear->setNext(node);
    }
    rear = node;
    size++;
  }

  std::optional<T> peek() {
    if (isEmpty()) {
      return std::nullopt;
    }
    return front->getData();
  }

  bool isEmpty() { return size == 0; }

  size_t getSize() { return size; }

 private:
  Nodes::SingleLinkNode<T> *front;
  Nodes::SingleLinkNode<T> *rear;
  size_t size;
};

}  // namespace Queues

#endif  // __QUEUE_H__
