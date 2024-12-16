#ifndef STACK_H
#define STACK_H

#include <array>
#include <cstdlib>
#include <optional>

#include "../node/node.h"

namespace Stacks {

template <typename T>
class Stack {
 public:
  virtual std::optional<T> pop() = 0;
  virtual std::optional<T> peek() = 0;
  virtual void push(T data) = 0;
  virtual bool isEmpty() = 0;
  virtual size_t getSize() = 0;

};  // class Stack

template <typename T>
class ArrayStack : public Stack<T> {
 public:
  ArrayStack(size_t capacity) : capacity(capacity), size(0) {
    stack = new T[capacity];
  }

  ~ArrayStack() { delete[] stack; }

  std::optional<T> pop() override {
    if (isEmpty()) {
      return std::nullopt;
    }
    return stack[--size];
  }

  std::optional<T> peek() override {
    if (isEmpty()) {
      return std::nullopt;
    }
    return stack[size - 1];
  }

  void push(T data) override {
    if (size == capacity) {
      return;
    }
    stack[size++] = data;
  }

  bool isEmpty() override { return size == 0; }

  size_t getSize() override { return size; }

 private:
  size_t capacity;
  size_t size;
  T *stack{};
};

template <typename T>
class LinkedStack : public Stack<T> {
 public:
  LinkedStack() : size(0), head(nullptr) {}

  ~LinkedStack() {
    while (head != nullptr) {
      Nodes::SingleLinkNode<T> *temp = head;
      head = head->getNext();
      delete temp;
      temp = nullptr;
    }
  }

  std::optional<T> pop() override {
    if (isEmpty()) {
      return std::nullopt;
    }
    Nodes::SingleLinkNode<T> *temp = head;
    head = head->getNext();
    T data = temp->getData();
    delete temp;
    temp = nullptr;
    size--;
    return data;
  }

  std::optional<T> peek() override {
    if (isEmpty()) {
      return std::nullopt;
    }
    return head->getData();
  }

  void push(T data) override {
    Nodes::SingleLinkNode<T> *newNode = new Nodes::SingleLinkNode<T>(data);
    newNode->setNext(head);
    head = newNode;
    size++;
  }

  bool isEmpty() override { return size == 0; }

  size_t getSize() override { return size; }

 private:
  size_t size;
  Nodes::SingleLinkNode<T> *head;
};

}  // namespace Stacks

#endif  // __STACK_H__
