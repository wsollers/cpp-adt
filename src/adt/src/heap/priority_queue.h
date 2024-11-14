#ifndef PRIOIRTY_QUEUE_H
#define PRIOIRTY_QUEUE_H

#include <cstdlib>

#include <optional>
#include <concepts>
#include <compare>

#include "../node/node.h"

namespace PriorityQueues {

template <typename T>
concept Prioritazable = requires(T a) {
    { a.getPriority() } -> std::totally_ordered;
};

using Priority = int16_t;

template <typename T>
struct PriorityContainer
{

  Priority priority;
  T data;

  int getPriority() const { return priority; }

  // Define comparison operators based on priority
  auto operator<=>(const PriorityContainer& other) const {
    return priority <=> other.priority;
  }

  bool operator==(const PriorityContainer& other) const {
    return priority == other.priority;
  } 

};

template <Prioritazable T>
class PriorityQueue {
public:
  virtual ~PriorityQueue() = default;

  virtual void insert(T data) = 0;

  virtual std::optional<T> peek() const = 0;
  virtual std::optional<T> extract() = 0;
  virtual std::optional<T> min() const = 0;
  virtual std::optional<T> removeMin() = 0;

  virtual bool isEmpty() const = 0;
  virtual size_t getSize() const = 0;

};

template <typename T>
class LinkedPriorityQueue : public PriorityQueue<T> {
public:
  LinkedPriorityQueue() : size(0), head(nullptr) {}

  LinkedPriorityQueue (const PriorityQueue<T> &other) = delete;

  LinkedPriorityQueue<T> &operator=(const PriorityQueue<T> &other) = delete;

  virtual ~LinkedPriorityQueue() {
    //delete tree here
  }

private:
  size_t size;
  Nodes::SingleLinkNode<PriorityContainer<T>> *head;

};

template <typename T>
class ArrayPriorityQueue : public PriorityQueue<T> {
public:
  ArrayPriorityQueue(size_t capacity) : capacity(capacity), size(0) {
    queue = new T[capacity];
  }

  ArrayPriorityQueue (const ArrayPriorityQueue<T> &other) = delete;

  ArrayPriorityQueue<T> &operator=(const PriorityQueue<T> &other) = delete;


  ~ArrayPriorityQueue() {
    delete[] queue;
  }

  void insert(T data) override {
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

  std::optional<T> extract() override {
    if (isEmpty()) {
      return std::nullopt;
    }
    T data = queue[0];
    for (size_t i = 0; i < size - 1; i++) {
      queue[i] = queue[i + 1];
    }
    size--;
    return data;
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

  bool isEmpty() const override {
    return size == 0;
  }

  size_t getSize() const override {
    return size;
  }

private:
  size_t capacity;
  size_t size;
  T *queue;

  bool isFull() {
    return size == capacity;
  }

};

} // namespace PriorityQueues

#endif // PRIOIRTY_QUEUE_H
