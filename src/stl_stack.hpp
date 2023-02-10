#ifndef STL_STACK_H_
#define STL_STACK_H_

#include <cstddef>
#include <iostream>
#include "stl_node.h"

namespace stl {

template <class T>
class stack {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const reference;
  using size_type = size_t;
  using Node = stl::node<T>;

 private:
  Node* head_;

 public:
  stack() : head_(nullptr){};

  explicit stack(std::initializer_list<value_type> const& items) : stack() {
    for (auto i = items.begin(); i != items.end(); ++i) {
      value_type value = *i;
      push(value);
    }
  };

  stack(const stack& other) : stack() {
    if (this != &other) {
      *this = other;
    }
  };

  stack(stack&& other) {
    if (this != &other) {
      std::swap(head_, other.head_);
      other.head_ = nullptr;
    }
  };

  ~stack() { free_stack(); };

  void push(const_reference value) {
    Node* new_head = new Node(value);
    new_head->set_next(nullptr);
    if (!empty()) {
      new_head->set_next(head_);
    }
    head_ = new_head;
  };

  void pop() {
    Node* tmp = head_->get_next();
    delete head_;
    head_ = tmp;
  };

  size_type size() {
    size_type size = 0;
    Node* tmp = head_;
    while (tmp) {
      ++size;
      tmp = tmp->get_next();
    }
    return size;
  };

  bool empty() {
    if (size()) {
      return 0;
    } else {
      return 1;
    }
  };

  const_reference top() { return head_->get_value(); };

  void swap(stack& other) {
    Node* tmp = head_;
    head_ = other.head_;
    other.head_ = tmp;
  };

  stack& operator=(stack&& other) {
    std::swap(this->head_, other.head_);
    return *this;
  };

  stack& operator=(const stack& other) {
    if (this != &other) {
      Node* tmp = other.head_;
      free_stack();
      copy_stack(*this, tmp);
    }
    return *this;
  }
  template <typename... Args>
  void emplace_front(Args&&... args) {
    value_type value(args...);
    push(value);
  };

 private:
  void copy_stack(stack& other, Node* iter) {
    value_type value;
    Node* next = iter;
    if (iter != nullptr) {
      value = next->get_value();
      next = next->get_next();
      copy_stack(other, next);
    }
    if (next != nullptr) {
      other.push(value);
    }
  };

  void free_stack() {
    while (head_ != nullptr) {
      pop();
    }
  }
};
}  // namespace stl
#endif  // STL_STACK_H_
