#ifndef TREE_H
#define TREE_H

#include "../node/node.h"

namespace Trees {

template <typename T> class BinaryTree {
public:
  explicit BinaryTree();
  explicit BinaryTree(T data);
  virtual ~BinaryTree();

  void insert(T data);
  void remove(T data);
  bool isEmpty();
  bool contains(const T& data);

  bool isRoot(Nodes::BinaryTreeNode<T> *node);
  bool isLeaf(Nodes::BinaryTreeNode<T> *node);
  Nodes::BinaryTreeNode<T> *search(T data);

private:
  Nodes::BinaryTreeNode<T> *root;
};

template <typename T> BinaryTree<T>::BinaryTree() : root(nullptr) {}

template <typename T> BinaryTree<T>::BinaryTree(T data) : root(new Nodes::BinaryTreeNode<T>(data)) {}

template <typename T> BinaryTree<T>::~BinaryTree() {
}

template <typename T> void BinaryTree<T>::insert(T data) {
  if (root == nullptr) {
    root = new Nodes::BinaryTreeNode<T>(data);
  } else {
    Nodes::BinaryTreeNode<T> *current = root;
    Nodes::BinaryTreeNode<T> *parent = nullptr;
    while (current != nullptr) {
      parent = current;
      if (data < current->data) {
        current = current->left;
      } else {
        current = current->right;
      }
    }
    if (data < parent->data) {
      parent->left = new Nodes::BinaryTreeNode<T>(data);
    } else {
      parent->right = new Nodes::BinaryTreeNode<T>(data);
    }
  }
}

template <typename T> void BinaryTree<T>::remove(T data) {
}

template <typename T> bool BinaryTree<T>::isEmpty() {
  return root == nullptr;
}

template <typename T> bool BinaryTree<T>::isRoot(Nodes::BinaryTreeNode<T> *node) {
  return root == node;
}

template <typename T> bool BinaryTree<T>::isLeaf(Nodes::BinaryTreeNode<T> *node) {
  return node->left == nullptr && node->right == nullptr;
}

} // namespace Trees

#endif // TREE_H 
