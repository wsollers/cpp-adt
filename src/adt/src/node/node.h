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


//force compiler to generate the class for the types we need
//template class Node<int>;
//template class Node<std::string>;

#endif // NODE_H
