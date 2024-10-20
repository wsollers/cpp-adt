#ifndef TREE_H
#define TREE_H

#include <cstdlib>
#include <functional>
#include <string>
#include <vector>

#include "../common/common.h"
#include "../node/node.h"

namespace Trees {

std::vector<int> xxx;

template <typename T, typename Custom_Comparator_Type = Common::Comparator<T>>
class BinarySearchTree {
public:
  using comparator_type = Custom_Comparator_Type;
  // const Allocator& alloc = Allocator()
  explicit BinarySearchTree();
  explicit BinarySearchTree(comparator_type comp);
  explicit BinarySearchTree(T data);
  virtual ~BinarySearchTree();

  void insert(T data);
  void remove(T data);
  bool isEmpty();
  bool contains(const T &data);

  size_t getSize();

  std::vector<T> findMatchingElements(std::function<bool(const T &)> predicate);

  void inOrderWithPredicate(std::function<bool(const T &)> predicate,
                            std::vector<T> &result) const;

  void preOrderWithPredicate(std::function<bool(const T &)> predicate,
                             std::vector<T> &result) const;

  void postOrderWithPredicate(std::function<bool(const T &)> predicate,
                              std::vector<T> &result) const;

private:
  bool isRoot(Nodes::BinaryTreeNode<T> *node);
  bool isLeaf(Nodes::BinaryTreeNode<T> *node);

  Nodes::BinaryTreeNode<T> *search(T data) const;

  void inOrderWithPredicateHelper(Nodes::BinaryTreeNode<T> *node,
                                  std::function<bool(const T &)> predicate,
                                  std::vector<T> &result) const;

  void preOrderWithPredicateHelper(Nodes::BinaryTreeNode<T> *node,
                                   std::function<bool(const T &)> predicate,
                                   std::vector<T> &result) const;

  void postOrderWithPredicateHelper(Nodes::BinaryTreeNode<T> *node,
                                    std::function<bool(const T &)> predicate,
                                    std::vector<T> &result) const;

  Nodes::BinaryTreeNode<T> *root;
  size_t size;
  comparator_type comparator;
};

template <typename T, typename Custom_Comparator_Type>
BinarySearchTree<T, Custom_Comparator_Type>::BinarySearchTree()
    : root(nullptr), size(0) {}

template <typename T, typename Custom_Comparator_Type>
BinarySearchTree<T, Custom_Comparator_Type>::BinarySearchTree(T data)
    : root(new Nodes::BinaryTreeNode<T>(data)), size(0) {}

template <typename T, typename Custom_Comparator_Type>
BinarySearchTree<T, Custom_Comparator_Type>::~BinarySearchTree() {}

template <typename T, typename Custom_Comparator_Type>
void BinarySearchTree<T, Custom_Comparator_Type>::insert(T data) {
  if (root == nullptr) {
    root = new Nodes::BinaryTreeNode<T>(data);
  } else {
    Nodes::BinaryTreeNode<T> *current = root;
    Nodes::BinaryTreeNode<T> *parent = nullptr;
    while (current != nullptr) {
      parent = current;
      if (comparator(data, current->data)) {
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

template <typename T, typename Custom_Comparator_Type>
void BinarySearchTree<T, Custom_Comparator_Type>::remove(T data) {
  size--;
}

template <typename T, typename Custom_Comparator_Type>
bool BinarySearchTree<T, Custom_Comparator_Type>::isEmpty() {
  return root == nullptr;
}

template <typename T, typename Custom_Comparator_Type>
bool BinarySearchTree<T, Custom_Comparator_Type>::isRoot(
    Nodes::BinaryTreeNode<T> *node) {
  return root == node;
}

template <typename T, typename Custom_Comparator_Type>
bool BinarySearchTree<T, Custom_Comparator_Type>::isLeaf(
    Nodes::BinaryTreeNode<T> *node) {
  return node->left == nullptr && node->right == nullptr;
}

template <typename T, typename Custom_Comparator_Type>
size_t BinarySearchTree<T, Custom_Comparator_Type>::getSize() {
  return size;
}

template <typename T, typename Custom_Comparator_Type>
bool BinarySearchTree<T, Custom_Comparator_Type>::contains(const T &data) {
  return search(data) != nullptr;
}

template <typename T, typename Custom_Comparator_Type>
void BinarySearchTree<T, Custom_Comparator_Type>::inOrderWithPredicate(
    std::function<bool(const T &)> predicate, std::vector<T> &result) const {
  inOrderWithPredicateHelper(root, predicate, result);
}

template <typename T, typename Custom_Comparator_Type>
void BinarySearchTree<T, Custom_Comparator_Type>::inOrderWithPredicateHelper(
    Nodes::BinaryTreeNode<T> *node, std::function<bool(const T &)> predicate,
    std::vector<T> &result) const {
  if (node == nullptr) {
    return;
  }
  inOrderWithPredicateHelper(node->left, predicate,
                             result); // Traverse left subtree
  if (predicate(node->data)) {        // Apply predicate
    result.push_back(node->data);     // Add if predicate is true
  }
  inOrderWithPredicateHelper(node->right, predicate,
                             result); // Traverse right subtree
}

template <typename T, typename Custom_Comparator_Type>
void BinarySearchTree<T, Custom_Comparator_Type>::preOrderWithPredicate(
    std::function<bool(const T &)> predicate, std::vector<T> &result) const {
  preOrderWithPredicateHelper(root, predicate, result);
}

template <typename T, typename Custom_Comparator_Type>
void BinarySearchTree<T, Custom_Comparator_Type>::preOrderWithPredicateHelper(
    Nodes::BinaryTreeNode<T> *node, std::function<bool(const T &)> predicate,
    std::vector<T> &result) const {
  if (node == nullptr) {
    return;
  }
  preOrderWithPredicateHelper(node->left, predicate, result); // Traverse left subtree
  if (predicate(node->data)) {                          // Apply predicate
    result.push_back(node->data); // Add if predicate is true
  }
  preOrderWithPredicateHelper(node->right, predicate,
                        result); // Traverse right subtree
}

template <typename T, typename Custom_Comparator_Type>
void BinarySearchTree<T, Custom_Comparator_Type>::postOrderWithPredicate(
    std::function<bool(const T &)> predicate, std::vector<T> &result) const {
  postOrderWithPredicateHelper(root, predicate, result);
}

template <typename T, typename Custom_Comparator_Type>
void BinarySearchTree<T, Custom_Comparator_Type>::postOrderWithPredicateHelper(
    Nodes::BinaryTreeNode<T> *node, std::function<bool(const T &)> predicate,
    std::vector<T> &result) const {
  if (node == nullptr) {
    return;
  }
  postOrderWithPredicateHelper(node->left, predicate,
                         result); // Traverse left subtree
  if (predicate(node->data)) {    // Apply predicate
    result.push_back(node->data); // Add if predicate is true
  }
  postOrderWithPredicateHelper(node->right, predicate,
                         result); // Traverse right subtree
}

template <typename T, typename Custom_Comparator_Type>
std::vector<T>
BinarySearchTree<T, Custom_Comparator_Type>::findMatchingElements(
    std::function<bool(const T &)> predicate) {
  std::vector<T> result;
  inOrderWithPredicate(predicate, result);
  return result;
}

template <typename T, typename Custom_Comparator_Type>
Nodes::BinaryTreeNode<T> *
BinarySearchTree<T, Custom_Comparator_Type>::search(T data) const {
  Nodes::BinaryTreeNode<T> *current = root;
  while (current != nullptr) {
    if (data == current->data) {
      return current;
    } else if (data < current->data) {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  return nullptr;
}

} // namespace Trees

#endif // TREE_H
