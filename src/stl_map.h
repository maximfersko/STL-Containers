#ifndef SRC_STL_MAP_H_
#define SRC_STL_MAP_H_

#include "btree.h"

namespace stl {
template <typename K, typename T>
class map : public Btree<K, T> {
 public:
  using map_type = T;
  using key_type = K;
  using const_reference_key = const K &;
  using const_reference_value = const T &;
  using value_type = std::pair<K, T>;
  using const_reference = const value_type &;
  using size_type = size_t;
  using iterator = typename Btree<K, T>::Iterator;
  using Node = treeNode<K, T>;

  class iteratorMap : public iterator {
   public:
    iteratorMap() : iterator::Iterator() {}
    value_type operator*();
  };

  iteratorMap begin() const;
  iteratorMap end() const;

  map() : Btree<K, T>::Btree() {}
  map(map<K, T> &&other);
  explicit map(const map<K, T> &other);
  explicit map(std::initializer_list<value_type> const &items);
  map<K, T> &operator=(map<K, T> &&other);
  ~map() {}

  std::pair<iterator, bool> insert(const_reference_key key,
                                   const_reference_value obj);
  std::pair<iterator, bool> insert(const_reference value) {
    return insert(value.first, value.second);
  }
  const_reference_value operator[](const_reference_key key);
  const_reference_value at(const_reference_key key);
  std::pair<iterator, bool> insert_or_assign(const_reference_key key,
                                             const_reference_value obj);
  void merge(map &other);
  template <typename... Args>
  std::pair<iterator, bool> emplace(Args&&... args);
};

};  // namespace stl

#include "stl_map.cc"
#endif  // SRC_STL_MAP_H_
