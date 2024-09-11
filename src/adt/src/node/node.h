#ifndef NODE_H
#define NODE_H

template <typename T> class Node {
public:
  Node(T data);
  T getData();
  virtual ~Node() = default;
private:
  T data;
};


template <typename T> Node<T>::Node(T data) : data(data) {}

template <typename T> T Node<T>::getData() {
  return data;
}

template <typename T> class SingleLinkNode : public Node<T> {
public:
  SingleLinkNode(T data);
  SingleLinkNode<T> *getNext();
  void setNext(SingleLinkNode<T> *next);
  virtual ~SingleLinkNode();
private:
  SingleLinkNode<T> *next;
};

template <typename T> SingleLinkNode<T>::SingleLinkNode(T data) : Node<T>(data), next(nullptr) {}

template <typename T> SingleLinkNode<T> *SingleLinkNode<T>::getNext() {
  return next;
}

template <typename T> void SingleLinkNode<T>::setNext(SingleLinkNode<T> *next) {
  if (this->next != nullptr) {
    delete this->next;
  }
  this->next = next;
}

template <typename T> SingleLinkNode<T>::~SingleLinkNode() {
  //delete next;
}


template <typename T> class DoubleLinkNode : public Node<T> {
public:
  DoubleLinkNode(T data);
  DoubleLinkNode<T> *getNext();
  DoubleLinkNode<T> *getPrev();
  void setNext(DoubleLinkNode<T> *next);
  void setPrev(DoubleLinkNode<T> *next);
  virtual ~DoubleLinkNode();
private:
  DoubleLinkNode<T> *next;
  DoubleLinkNode<T> *prev;
};


template <typename T> DoubleLinkNode<T>::DoubleLinkNode(T data) : Node<T>(data), next(nullptr), prev(nullptr) {}

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
  //delete next;
  //delete prev;
}






template <typename T> class BinaryTreeNode : public Node<T> {
public:
  BinaryTreeNode(T data);
  BinaryTreeNode<T> *getLeft();
  BinaryTreeNode<T> *getRight();
  void setLeft(BinaryTreeNode<T> *left);
  void setRight(BinaryTreeNode<T> *right);
  virtual ~BinaryTreeNode();
private:
  BinaryTreeNode<T> *left;
  BinaryTreeNode<T> *right;
};


template <typename T> BinaryTreeNode<T>::BinaryTreeNode(T data) : Node<T>(data), left(nullptr), right(nullptr) {}

template <typename T> BinaryTreeNode<T> *BinaryTreeNode<T>::getLeft() {
  return left;
}

template <typename T> BinaryTreeNode<T> *BinaryTreeNode<T>::getRight() {
  return right;
}

template <typename T> void BinaryTreeNode<T>::setRight(BinaryTreeNode<T> *right) {
  if (this->right != nullptr) {
    delete this->right;
  }
  this->right = right;
}

template <typename T> void BinaryTreeNode<T>::setLeft(BinaryTreeNode<T> *left) {
  if (this->left != nullptr) {
    delete this->left;
  }
  this->left = left;
}

template <typename T> BinaryTreeNode<T>::~BinaryTreeNode() {
  //delete next;
  //delete prev;
}


















//force compiler to generate the class for the types we need
//template class Node<int>;
//template class Node<std::string>;

#endif // NODE_H
