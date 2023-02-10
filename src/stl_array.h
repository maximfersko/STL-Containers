#ifndef SRC_STL_ARRAY_H_
#define SRC_STL_ARRAY_H_

#include <iostream>

#include "stl_vector.h"

namespace stl {

template <typename T, size_t s>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

 private:
  value_type *data_;
  size_type size_;
  void freeArray();

 public:
  //  Constructor & Destructor

  array();
  explicit array(std::initializer_list<value_type> const &items);
  explicit array(const array &a);
  explicit array(array &&a);
  ~array();

  //  Methods

  size_type size() const { return s; }
  bool empty() const;
  reference at(size_type position) const;
  void swap(array &other);
  void fill(const_reference);
  size_type max_size() const { return s; }
  const_reference back();
  const_reference front();
  iterator data() { return data_; }

  // iterators

  iterator begin();
  iterator end();

  // operators

  reference operator[](size_type index) const;
  array<T, s> &operator=(array &&a);
};

};  // namespace stl
#include "stl_array.cc"
#endif  // SRC_STL_ARRAY_H_
