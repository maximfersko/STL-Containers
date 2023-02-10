#ifndef SRC_STL_LIST_H_
#define SRC_STL_LIST_H_

#include <iostream>

namespace stl {

 
template <typename T>
class list {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  struct Node {
    value_type data;
    Node *next;
    Node *prev;
  };

  class ListIterator {
   private:
    Node *iter_;
    Node *head_;
    Node *tail_;

   public:
    Node *getIter() { return this->iter_; }
    void setIter(Node *value) { this->iter_ = value; }
    Node *getHead() { return this->head_; }
    void setHead(Node *value) { this->head_ = value; }
    Node *getTail() { return this->tail_; }
    void setTail(Node *value) { this->tail_ = value; }
    ListIterator() : iter_(nullptr), head_(nullptr), tail_(nullptr) {}
    explicit ListIterator(Node *other)
        : iter_(other), head_(nullptr), tail_(nullptr) {}
    explicit ListIterator(const list<T> &other)
        : iter_(other.head_), tail_(other.tail_), head_(other.head_) {}
    // ListIterator(const ListIterator &other) : iter(other.iter) {}

    reference operator*();
    ListIterator &operator--();
    ListIterator &operator++();
    bool operator==(const ListIterator &other);
    bool operator<=(const ListIterator &other);
    bool operator!=(const ListIterator &other);
  };

  class ListConstIterator {
   private:
    Node *iter_;
    Node *head_;
    Node *tail_;

   public:
    Node *getIter() { return this->iter_; }
    void setIter(Node *value) { this->iter_ = value; }
    Node *getHead() { return this->head_; }
    void setHead(Node *value) { this->head_ = value; }
    Node *getTail() { return this->tail_; }
    void setTail(Node *value) { this->tail_ = value; }
    ListConstIterator() : iter_(nullptr), head_(nullptr), tail_(nullptr) {}
    explicit ListConstIterator(Node *other)
        : iter_(other), head_(nullptr), tail_(nullptr) {}
    explicit ListConstIterator(const list<T> &other)
        : iter_(other.head_), tail_(other.tail_), head_(other.head_) {}
    // const_reference operator*();

    const_reference operator*();
    ListConstIterator &operator++();
    ListConstIterator &operator--();
    bool operator==(const ListConstIterator &other);
    bool operator!=(const ListConstIterator &other);
  };

  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  //  Constructor & Destructor

 private:
  Node *head_;
  Node *tail_;
  // Node *after_tail_;
  size_type size_;

 public:
  list() : head_(nullptr), tail_(nullptr), size_(0U) {}
  explicit list(size_type size);
  explicit list(std::initializer_list<T> const &items);
  list(const list &l);
  list(list &&l);
  list<T> &operator=(list &&l);
  ~list();

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  void print() const;
  Node *getTail() { return this->tail_; }
  const_reference front() const;
  const_reference back() const;
  void clear();
  void reverse();
  void push_back(const_reference value);
  void push_front(const_reference value);
  iterator insert(iterator position, const_reference value);
  void erase(iterator position);
  void splice(const_iterator position, const list &other);
  void swap(list &other);
  void sort();
  void unique();
  void pop_front();
  void pop_back();
  size_type size() const;
  bool empty() const;
  size_type max_size() const;

  template <typename... Args>
  void emplace_back(Args &&...args);
  template <typename... Args>
  void emplace_front(Args &&...args);
};

 
};  // namespace stl

#include "stl_list.cc"
#endif  // SRC_STL_LIST_H_
