#ifndef SRC_STL_MULTISET_H_
#define SRC_STL_MULTISET_H_
#include "stl_set.h"

namespace stl {

template <typename K>
class multiset : public set<K> {
 public:
  using value_type = K;
  using const_reference = const K &;
  using reference = K &;
  using iterator = typename Btree<K, nullptr_t>::Iterator;
  using size_type = size_t;

  multiset() {}
  explicit multiset(std::initializer_list<value_type> const &items);
  explicit multiset(const multiset &other) : multiset() {
    if (this->tree_) delete this->tree_;
    this->tree_ = new Btree<value_type, std::nullptr_t>(*other.tree_);
  }
  multiset(multiset &&other) { *this = std::move(other); }
  ~multiset() { if (this->tree_) {delete this->tree_;} this->tree_ = nullptr; }
  multiset<K> &operator=(multiset &&other);
  iterator insert(const_reference value) { return this->tree_->insert(value); }
  size_type count(const_reference key);
  std::pair<iterator, iterator> equal_range(const_reference key);
  iterator lower_bound(const_reference key);
  iterator upper_bound(const_reference key);
  template <typename... Args>
  std::pair<iterator, bool> emplace(Args&&... args);
};

};  // namespace stl

#include "stl_multiset.cc"
#endif  // SRC_STL_MULTISET_H_
