#ifndef PRIOIRTY_QUEUE_H
#define PRIOIRTY_QUEUE_H

#include <cstdlib>

#include <compare>
#include <concepts>
#include <optional>
#include <stdexcept>

#include "../node/node.h"

namespace PriorityQueues {

template <typename T>
concept Prioritazable = requires(T a) {
  { a.getPriority() } -> std::totally_ordered;
};

using Priority = int16_t;

template <typename T> struct PriorityContainer {

  Priority priority;
  T data;

  int getPriority() const { return priority; }

  // Define comparison operators based on priority
  auto operator<=>(const PriorityContainer &other) const {
    return priority <=> other.priority;
  }

  bool operator==(const PriorityContainer &other) const {
    return (priority == other.priority) && (data == other.data);
  }
};

template <Prioritazable T> class PriorityQueue {
public:
  virtual ~PriorityQueue() = default;

  virtual void insert(Priority p, T data) = 0;

  virtual std::optional<T> peek() const = 0;
  virtual std::optional<T> min() const = 0;
  virtual std::optional<T> removeMin() = 0;

  virtual bool isEmpty() const = 0;
  virtual size_t getSize() const = 0;
};

template <typename T> class LinkedPriorityQueue : public PriorityQueue<T> {
public:
  LinkedPriorityQueue();

  virtual ~LinkedPriorityQueue();

  LinkedPriorityQueue(const PriorityQueue<T> &other);

  PriorityQueue<T> &operator=(const LinkedPriorityQueue<T> &other);

  void insert(Priority p, T data) override;

  std::optional<T> peek() const override;
  std::optional<T> min() const override;
  std::optional<T> removeMin() override;

  bool isEmpty() const override;
  size_t getSize() const override;

private:
  size_t size;
  Nodes::BinaryTreeNode<PriorityContainer<T>> *head;

  // function to do a postorder traversal of the other tree and delete each node
  // after inserting it into this tree
  void copyTree(const Nodes::BinaryTreeNode<PriorityContainer<T>> *node);
};

template <typename T>
LinkedPriorityQueue<T>::LinkedPriorityQueue() : size(0), head(nullptr){};

template <typename T> LinkedPriorityQueue<T>::~LinkedPriorityQueue(){};

template <typename T>
LinkedPriorityQueue<T>::LinkedPriorityQueue(const PriorityQueue<T> &other)
    : size(0), head(nullptr) {
  if (other == nullptr) {
    throw std::runtime_error("Initialization with nullptr");
  }

  std::optional<PriorityContainer<T>> data;

  while ((data = other.removeMin()).has_value()) {
    insert(data->getPriority(), data->data);
    this->size++;
  }
};

template <typename T>
void LinkedPriorityQueue<T>::copyTree(
    const Nodes::BinaryTreeNode<PriorityContainer<T>> *node) {
  if (node == nullptr) {
    return;
  }
  copyTree(node->left);
  copyTree(node->right);
  insert(node->data.getPriority(), node->data.data);
};

template <typename T>
PriorityQueue<T> &
LinkedPriorityQueue<T>::operator=(const LinkedPriorityQueue<T> &other) {
  if (this == &other) {
    return *this;
  }

  copyTree(other.head);
};

template <typename T> void LinkedPriorityQueue<T>::insert(Priority p, T data) {
  auto newNode = new Nodes::BinaryTreeNode<PriorityContainer<T>>(
      PriorityContainer<T>{p, data});
  if (head == nullptr) {
    head = newNode;
    size++;
    return;
  }
  auto current = head;
  auto parent = head;
  while (current != nullptr &&
         current->data.getPriority() < newNode->data.getPriority()) {
    parent = current;
    if (newNode->data.getPriority() < current->data.getPriority()) {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  if (newNode->data.getPriority() < parent->data.getPriority()) {
    parent->left = newNode;
  } else {
    parent->right = newNode;
  }
  size++;
};

template <typename T> std::optional<T> LinkedPriorityQueue<T>::peek() const {
  if (isEmpty()) {
    return std::nullopt;
  }
  return head->data.data;
};

template <typename T> std::optional<T> LinkedPriorityQueue<T>::min() const {
  if (isEmpty()) {
    return std::nullopt;
  }
  auto current = head;
  while (current->left != nullptr) {
    current = current->left;
  }
  return current->data.data;
};

template <typename T> std::optional<T> LinkedPriorityQueue<T>::removeMin() {
  if (isEmpty()) {
    return std::nullopt;
  }
  auto current = head;
  auto parent = head;
  while (current->left != nullptr) {
    parent = current;
    current = current->left;
  }
  auto data = current->data.data;
  if (current == head) {
    head = head->right;
  } else {
    parent->left = current->right;
  }
  delete current;
  size--;
  return data;
};

template <typename T> bool LinkedPriorityQueue<T>::isEmpty() const {
  return size == 0;
};

template <typename T> size_t LinkedPriorityQueue<T>::getSize() const {
  return size;
};

template <typename T> class ArrayPriorityQueue : public PriorityQueue<T> {
public:
  explicit ArrayPriorityQueue(size_t capacity) : capacity(capacity), size(0) {
    queue = new T[capacity];
  }

  ArrayPriorityQueue(const ArrayPriorityQueue<T> &other) = delete;

  ArrayPriorityQueue<T> &
  operator=(const ArrayPriorityQueue<T> &other) {
    if (this == &other) {
      return *this;
    }

    delete[] queue;
    queue = new T[other.capacity];
    size = other.size;
    capacity = other.capacity;
    for (size_t i = 0; i < size; i++) {
      queue[i] = other.queue[i];
    }
    return *this;
  }

  ~ArrayPriorityQueue() { delete[] queue; }

  void insert(Priority p, T data) override {
    if (isFull()) {
      return;
    }
    queue[size++] = data;
  }

  std::optional<T> peek() const override {
    if (isEmpty()) {
      return std::nullopt;
    }
    return queue[0];
  }

  std::optional<T> min() const override {
    if (isEmpty()) {
      return std::nullopt;
    }
    T min = queue[0];
    for (size_t i = 1; i < size; i++) {
      if (queue[i] < min) {
        min = queue[i];
      }
    }
    return min;
  }

  std::optional<T> removeMin() override {
    if (isEmpty()) {
      return std::nullopt;
    }
    T minimum = queue[0];
    size_t minIndex = 0;
    for (size_t i = 1; i < size; i++) {
      if (queue[i] < minimum) {
        minimum = queue[i];
        minIndex = i;
      }
    }
    for (size_t i = minIndex; i < size - 1; i++) {
      queue[i] = queue[i + 1];
    }
    size--;
    return minimum;
  }

  bool isEmpty() const override { return size == 0; }

  size_t getSize() const override { return size; }

private:
  size_t capacity;
  size_t size;
  T *queue;

  bool isFull() { return size == capacity; }
};

} // namespace PriorityQueues

#endif // PRIOIRTY_QUEUE_H
