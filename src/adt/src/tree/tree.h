#ifndef TREE_H
#define TREE_H

#include "../node/node.h"

#include <cstdlib>

namespace Trees {

template <typename T> class BinarySearchTree {
public:
  explicit BinarySearchTree();
  explicit BinarySearchTree(T data);
  virtual ~BinarySearchTree();

  void insert(T data);
  void remove(T data);
  bool isEmpty();
  bool contains(const T &data);

  bool isRoot(Nodes::BinaryTreeNode<T> *node);
  bool isLeaf(Nodes::BinaryTreeNode<T> *node);
  Nodes::BinaryTreeNode<T> *search(T data);

  size_t getSize();

private:
  Nodes::BinaryTreeNode<T> *root;
  size_t size;
};

template <typename T>
BinarySearchTree<T>::BinarySearchTree() : root(nullptr), size(0) {}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(T data)
    : root(new Nodes::BinaryTreeNode<T>(data)), size(0) {}

template <typename T> BinarySearchTree<T>::~BinarySearchTree() {}

template <typename T> void BinarySearchTree<T>::insert(T data) {
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
  size++;
}

template <typename T> void BinarySearchTree<T>::remove(T data) { size--; }

template <typename T> bool BinarySearchTree<T>::isEmpty() {
  return root == nullptr;
}

template <typename T>
bool BinarySearchTree<T>::isRoot(Nodes::BinaryTreeNode<T> *node) {
  return root == node;
}

template <typename T>
bool BinarySearchTree<T>::isLeaf(Nodes::BinaryTreeNode<T> *node) {
  return node->left == nullptr && node->right == nullptr;
}

template <typename T> size_t BinarySearchTree<T>::getSize() { return size; }

} // namespace Trees

#endif // TREE_H
