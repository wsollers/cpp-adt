#ifndef STACK_H
#define STACK_H

#include <cstdlib>
#include <array>

namespace Stacks {

template <typename T>
class Stack {

public:

virtual T pop() = 0;
virtual T peek() = 0;
virtual void push(T data) = 0;
virtual bool isEmpty() = 0;
virtual size_t getSize() = 0;

}; // class Stack



template <typename T>
class ArrayStack : public Stack<T> {
public:
  ArrayStack(size_t capacity) : capacity(capacity), size(0) {
    stack = new T[capacity]; 
  }

  ~ArrayStack() {
    delete[] stack;
  }

  T pop() override {
    if (isEmpty()) {
      return T();
    }
    return stack[--size];
  }

  T peek() override {
    if (isEmpty()) {
      return T();
    }
    return stack[size - 1];
  }

  void push(T data) override {
    if (size == capacity) {
      return;
    }
    stack[size++] = data;
  }

  bool isEmpty() override {
    return size == 0;
  }

  size_t getSize() override {
    return size;
  }

private:
  size_t capacity;
  size_t size;
  T *stack {};

};

} // namespace Stacks

#endif // __STACK_H__
