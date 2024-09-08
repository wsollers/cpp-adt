#ifndef __NODE_H__
#define __NODE_H__

template <typename T> class Node {
public:
  Node(T data);
  T getData();
  virtual ~Node();
private:
  T data;
};

template <typename T> class SingleLinkNode : public Node<T> {
public:
  SingleLinkNode(T data);
  SingleLinkNode<T> *getNext();
  void setNext(SingleLinkNode<T> *next);
  virtual ~SingleLinkNode();
private:
  SingleLinkNode<T> *next;
};

#endif // __NODE_H__
