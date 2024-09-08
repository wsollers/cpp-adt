#ifndef ___LIST_H___
#define ___LIST_H___

#include "../node/node.h"

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

template <typename T>
class Calculator {
public:
    Calculator(T a, T b);  // Constructor declaration
    T add();
    T subtract();
    T multiply();
    T divide();

private:
    T num1, num2;
};

#endif
