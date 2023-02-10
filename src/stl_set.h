#ifndef SRC_STL_SET_H_
#define SRC_STL_SET_H_

#include "btree.h"


namespace stl {
template <typename K>
class set {
 public:
  using value_type = K;
  using const_reference = const K &;
  using reference = K &;
  using iterator = typename Btree<K, nullptr_t>::Iterator;
  using size_type = size_t;

 protected:
  Btree<value_type, nullptr_t> *tree_;

 public:
  set() { tree_ = new Btree<value_type, nullptr_t>(); }
  explicit set(std::initializer_list<value_type> const &items) : set() {
    for (auto &item : items) this->insert(item);
  }
  set(const set &other)  {
    tree_ = new Btree<value_type, std::nullptr_t>(*other.tree_);
  }
  set(set &&other) : tree_(nullptr) { *this = std::move(other); }
  ~set() { if (tree_) { delete tree_; tree_ = nullptr; } }

  set<K> &operator=(set &&other);
  iterator begin() { return tree_->begin(); }
  iterator end() { return tree_->end(); }
  iterator cbegin() const { return tree_->begin(); }
  iterator cend() const { return tree_->end(); }

  size_type max_size() const { return tree_->max_size(); }
  bool empty() const { return tree_->empty(); }
  size_type size() const { return tree_->size(); }

  std::pair<iterator, bool> insert(const_reference value);
  void clear() const { tree_->clear(); }
  void swap(set &other) { tree_->swap(*other.tree_); }
  bool contains(const_reference key) { return tree_->contains(key); }
  void erase(iterator pos) { tree_->erase(pos); }
  iterator find(const_reference key) { return tree_->find(key); }
  void merge(const set &other);
  template <typename... Args>
  std::pair<iterator, bool> emplace(Args&&... args);
};

};  // namespace stl
#include "stl_set.cc"
#endif  // SRC_STL_SET_H_