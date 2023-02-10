#ifndef SRC_BTREE_H_
#define SRC_BTREE_H_

#include <iomanip>
#include <iostream>

#include "treeNode.h"

namespace stl {

template <typename K, typename T>
class Btree {
 public:
  using map_type = T;
  using key_type = K;
  using const_reference_key = const K &;
  using value_type = std::pair<K, T>;
  using size_type = size_t;
  using Node = treeNode<K, T>;

 protected:
  Node *root_;
  size_type size_;

 public:
  class Iterator {
   private:
   public:
    Node *iter_;
    Iterator() : iter_(nullptr) {}
    Iterator(const Iterator &other) : Iterator() { *this = other; }
    Iterator(Node *other) : iter_(other) {}
    ~Iterator() { iter_ = nullptr; }
    void operator++();
    void operator--();
    bool operator==(const Iterator &other);
    bool operator!=(const Iterator &other);
    key_type operator*();
  };

  using iterator = Iterator;

 protected:
  std::pair<iterator, bool> search(const_reference_key key);

 public:
  //             Constructor & Destructor

  Btree() : size_(0), root_(nullptr) {}
  Btree(const std::initializer_list<K> &items);
  Btree(const Btree<K, T> &other);
  Btree<K, T> &operator=(Btree<K, T> &&other);
  ~Btree();

  // iterators

  iterator begin() const;
  iterator end() const;

  //             methods

  iterator insert(const_reference_key &value);
  void erase(iterator pos);
  void print(Node *root);
  void printTree(Node *elm, int depth);
  Node *getRoot() { return this->root_; }
  void clear();
  void clean(Node *root);
  bool empty() const { return !(root_ != nullptr); }
  size_t size() const { return size_; }
  size_t max_size();
  void copy(Node *root);
  void swap(Btree<K, T> &other);
  iterator find(const_reference_key key);
  bool contains(const_reference_key key);
};

};  // namespace stl

#include "btree.cc"
#endif  // SRC_BTREE_H_
