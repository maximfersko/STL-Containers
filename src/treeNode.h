#ifndef SRC_TREENODE_H_
#define SRC_TREENODE_H_

#include <iostream>

namespace stl {

template <typename K, typename T>
class treeNode {
 public:
  treeNode *right;
  treeNode *left;
  treeNode *parent;
  std::pair<K, T> *data;

  treeNode() : right(nullptr), left(nullptr), parent(nullptr) {
    data = new std::pair<K, T>;
  }
  treeNode(const treeNode<K, T> &other) : treeNode() { *this = other; }
  ~treeNode() { if (data) { delete data; data = nullptr; } }

  treeNode &operator=(const treeNode<K, T> &other);

  treeNode<K, T> *minimalNode();
  treeNode<K, T> *maximalNode();
  treeNode<K, T> *nextNode();
  treeNode<K, T> *prevNode();
  treeNode<K, T> *minimalNill();
};

};  // namespace stl

#include "treeNode.cc"
#endif  // SRC_TREENODE_H_
