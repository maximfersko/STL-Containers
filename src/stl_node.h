#ifndef STL_NODE_H_
#define STL_NODE_H_

namespace stl {
template <class T>
class node {
 public:
  node() : value_(T()), next_(nullptr), prev_(nullptr) {}
  explicit node(T value) : node() { value_ = value; };
  T& get_value() { return value_; };
  node* get_next() { return next_; };
  node* get_prev() { return prev_; };
  void set_next(node* new_next) { next_ = new_next; }
  void set_prev(node* new_prev) { prev_ = new_prev; }
  void set_value(T new_value) { value_ = new_value; }

 private:
  T value_;
  node* next_;
  node* prev_;
};

}  // namespace stl

#endif  // STL_NODE_H