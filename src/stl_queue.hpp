#ifndef STL_QUEUE_H_
#define STL_QUEUE_H_

#include <iostream>

namespace stl {

template <class T>
class queue {
 private:
  class Node {
   public:
    Node(T value = T(), Node* next = nullptr, Node* prev = nullptr)
        : value_(value), next_(next), prev_(prev){};
    explicit Node(T value) : Node() { value_ = value; };
    T& getValue() { return value_; };
    Node* getNext() { return next_; };
    Node* getPrev() { return prev_; };
    void setNext(Node* new_next) { next_ = new_next; }
    void setPrev(Node* new_prev) { prev_ = new_prev; }
    void setValue(T new_value) { value_ = new_value; }

   private:
    T value_;
    Node* next_;
    Node* prev_;
  };

 public:
  using value_type = T;
  using reference = value_type&;
  using const_reference = const reference;
  using size_type = size_t;

 private:
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
  size_type size_ = 0;

 public:
  queue() : size_(0) {
    Node* null_tmp = new Node;
    head_ = null_tmp;
    tail_ = null_tmp;
  };

  explicit queue(std::initializer_list<value_type> const& items) : queue() {
    for (auto i = items.begin(); i != items.end(); ++i) {
      value_type value = *i;
      push(value);
    }
  };

  queue(const queue& q) : queue() {
    for (Node* count_node = q.head_; count_node;
         count_node = count_node->getPrev()) {
      push(count_node->getValue());
    }
  };

  queue(queue&& q) : head_(nullptr), tail_(nullptr) {
    std::swap(head_, q.head_);
    std::swap(tail_, q.tail_);
    size_ = q.size_;
    q.size_ = 0;
  };

  ~queue() {
    while (head_) {
      pop();
    }
  };

  queue& operator=(queue&& other) {
    while (head_) {
      pop();
    }
    swap(other);
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
    return *this;
  };

  const_reference front() { return head_->getValue(); };

  const_reference back() { return tail_->getNext()->getValue(); };

  void push(const_reference value) {
    tail_->setPrev(new Node(value_type(), tail_));
    tail_->setValue(value);
    tail_ = tail_->getPrev();
    ++size_;
  };

  void pop() {
    Node* tmp = head_->getPrev();
    delete head_;
    head_ = tmp;
    --size_;
  };

  void swap(queue& other) {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
  };

  size_type size() { return size_; };

  bool empty() { return !size_; };

  template <typename... Args>
  void emplace_back(Args&&... args) {
    value_type value(args...);
    push(value);
  };
};

}  // namespace stl

#endif  // STL_QUEUE_H_
