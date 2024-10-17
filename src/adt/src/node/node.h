#ifndef NODE_H
#define NODE_H

#include "../common/common.h"

namespace Nodes {

template <typename T>
  requires Common::stl_container_storable<T>
class Node {
public:
  explicit Node(T data);
  T getData();
  void setData(T data);
  virtual ~Node() = default;

public:
  T data;
};

template <typename T>
  requires Common::stl_container_storable<T>
Node<T>::Node(T data) : data(data) {}

template <typename T>
  requires Common::stl_container_storable<T>
T Node<T>::getData() {
  return data;
}

template <typename T>
  requires Common::stl_container_storable<T>
void Node<T>::setData(T data) {
  this->data = data;
}

template <typename T> class SingleLinkNode : public Node<T> {
public:
  explicit SingleLinkNode(T data);
  SingleLinkNode<T> *getNext();
  void setNext(SingleLinkNode<T> *next);
  virtual ~SingleLinkNode();

public:
  SingleLinkNode<T> *next;
};

template <typename T>
SingleLinkNode<T>::SingleLinkNode(T data) : Node<T>(data), next(nullptr) {}

template <typename T> SingleLinkNode<T> *SingleLinkNode<T>::getNext() {
  return next;
}

template <typename T> void SingleLinkNode<T>::setNext(SingleLinkNode<T> *next) {
  // Do we need to delete the next node?
  this->next = next;
}

template <typename T> SingleLinkNode<T>::~SingleLinkNode() {
  // delete next;
}

template <typename T> class DoubleLinkNode : public Node<T> {
public:
  explicit DoubleLinkNode(T data);
  DoubleLinkNode<T> *getNext();
  DoubleLinkNode<T> *getPrev();
  void setNext(DoubleLinkNode<T> *next);
  void setPrev(DoubleLinkNode<T> *next);
  virtual ~DoubleLinkNode();

private:
  DoubleLinkNode<T> *next;
  DoubleLinkNode<T> *prev;
};

template <typename T>
DoubleLinkNode<T>::DoubleLinkNode(T data)
    : Node<T>(data), next(nullptr), prev(nullptr) {}

template <typename T> DoubleLinkNode<T> *DoubleLinkNode<T>::getNext() {
  return next;
}

template <typename T> DoubleLinkNode<T> *DoubleLinkNode<T>::getPrev() {
  return prev;
}

template <typename T> void DoubleLinkNode<T>::setNext(DoubleLinkNode<T> *next) {
  if (this->next != nullptr) {
    delete this->next;
  }
  this->next = next;
}

template <typename T> void DoubleLinkNode<T>::setPrev(DoubleLinkNode<T> *prev) {
  if (this->prev != nullptr) {
    delete this->prev;
  }
  this->prev = prev;
}

template <typename T> DoubleLinkNode<T>::~DoubleLinkNode() {
  // delete next;
  // delete prev;
}

template <typename T> class BinaryTreeNode : public Node<T> {
public:
  explicit BinaryTreeNode(T data);
  virtual ~BinaryTreeNode() = default;

  BinaryTreeNode<T> *getParent();
  BinaryTreeNode<T> *getLeft();
  BinaryTreeNode<T> *getRight();
  void setParent(BinaryTreeNode<T> *parent);
  void setLeft(BinaryTreeNode<T> *left);
  void setRight(BinaryTreeNode<T> *right);

  BinaryTreeNode<T> *parent;
  BinaryTreeNode<T> *left;
  BinaryTreeNode<T> *right;
};

template <typename T>
BinaryTreeNode<T>::BinaryTreeNode(T data)
    : Node<T>(data), parent(nullptr), left(nullptr), right(nullptr) {}

template <typename T> BinaryTreeNode<T> *BinaryTreeNode<T>::getParent() {
  return parent;
}

template <typename T> BinaryTreeNode<T> *BinaryTreeNode<T>::getLeft() {
  return left;
}

template <typename T> BinaryTreeNode<T> *BinaryTreeNode<T>::getRight() {
  return right;
}

template <typename T>
void BinaryTreeNode<T>::setParent(BinaryTreeNode<T> *parent) {
  this->parent = parent;
}

template <typename T> void BinaryTreeNode<T>::setLeft(BinaryTreeNode<T> *left) {
  if (this->left != nullptr) { // this delete is not needed
    delete this->left;
  }
  this->left = left;
}

template <typename T>
void BinaryTreeNode<T>::setRight(BinaryTreeNode<T> *right) {
  if (this->right != nullptr) { // this delete is not needed
    delete this->right;
  }
  this->right = right;
}

} // namespace Nodes

// force compiler to generate the class for the types we need
// template class Node<int>;
// template class Node<std::string>;

#endif // NODE_H
