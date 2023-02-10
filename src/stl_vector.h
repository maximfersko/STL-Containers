#ifndef SRC_STL_VECTOR_H_
#define SRC_STL_VECTOR_H_

#include <cmath>
#include <iostream>

namespace stl {

template <typename T>

class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;
  using size_type = size_t;

 private:
  value_type *data_;
  size_type size_;      // size vector
  size_type capacity_;  // max size vector

  void freeArray();
  void reallocate();

 public:
  //  Constructor & Destructor

  vector();
  explicit vector(size_type size);
  explicit vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);
  vector(vector &&v);
  ~vector();

  //  Methods

  bool empty();
  size_type size() const;
  size_type capacity() const;
  reference at(size_type position) const;
  reference back();
  const_reference back() const;
  void push_back(const_reference value);
  void resize(size_type new_size);
  void reserve(size_type new_size);
  reference front();
  const_reference front() const;
  const_iterator data() const;
  iterator data();
  void swap(vector &other);
  void shrink_to_fit();
  void pop_back();
  void clear();
  size_type max_size() const;
  iterator insert(iterator position, const_reference value);
  void erase(const_iterator position);
  template <typename... Args>
  void emplace_back(Args &&...args);
  template <typename... Args>
  iterator emplace(const_iterator position, Args &&...args);
  // iterator erase (const_iterator first, const_iterator second);
  // void assign(size_type count, const_reference value);

  void print() const;

  // iterators

  iterator begin();
  iterator end();
  reverse_iterator rbegin();
  reverse_iterator rend();
  const_iterator cend() const;
  const_iterator cbegin() const;

  // operators

  reference operator[](size_t index) const;
  vector<T> &operator=(vector &&v);
};

};  // namespace stl
#include "stl_vector.cc"
#endif  // SRC_STL_VECTOR_H_
