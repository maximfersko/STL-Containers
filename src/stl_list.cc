#include "stl_list.h"

namespace stl {

template <typename T>
typename list<T>::reference list<T>::ListIterator::operator*() {
    if (this->iter_ == nullptr) throw std::logic_error("Error");
    return this->iter_->data;
}

template <typename T>
typename list<T>::const_reference list<T>::ListConstIterator::operator*() {
    if (this->iter_ == nullptr) throw std::logic_error("Error");
    return this->iter_->data;
}

template <typename T>
typename list<T>::ListIterator &list<T>::ListIterator::operator--() {
    if (this->iter_) {
        this->iter_ = this->iter_->prev;
    } else {
        this->iter_ = this->tail_;
    }
    return *this;
}

template <typename T>
typename list<T>::ListIterator &list<T>::ListIterator::operator++() {
    this->iter_ = this->iter_->next;
    return *this;
}

template <typename T>
typename list<T>::ListConstIterator &list<T>::ListConstIterator::operator++() {
    this->iter_ = this->iter_->next;
    return *this;
}

template <typename T>
typename list<T>::ListConstIterator &list<T>::ListConstIterator::operator--() {
     if (this->iter_) {
        this->iter_ = this->iter_->prev;
    } else {
        this->iter_ = this->tail_;
    }
    return *this;
}

template <typename T>
bool list<T>::ListConstIterator::operator!=(const ListConstIterator &other) {
    return (this->iter_ != other.iter_) ? true : false;
}

template <typename T>
bool list<T>::ListIterator::operator==(const ListIterator &other) {
    return (this->iter_ == other.iter_) ? true : false;
}

template <typename T>
bool list<T>::ListIterator::operator!=(const ListIterator &other) {
    return (this->iter_ != other.iter_) ? true : false;
}

template <typename T>
bool list<T>::ListIterator::operator<=(const ListIterator &other) {
    return (this->iter_ <= other.iter_) ? true : false;
}

template <typename T>
typename list<T>::iterator list<T>::begin() {
    return iterator(this->head_);
}

template <typename T>
typename list<T>::iterator list<T>::end() {
    iterator last(*this);
    while (last.getIter() != nullptr) ++last;
    return last;
}

template <typename T>
typename list<T>::const_iterator list<T>::cbegin() const {
    return const_iterator(this->head_);
}

template <typename T>
typename list<T>::const_iterator list<T>::cend() const {
    const_iterator last(*this);
    while (last.getIter() != nullptr) ++last;
    return last;
}

template <typename T>
typename list<T>::const_reference list<T>::front() const {
    return this->head_->data;
}

template <typename T>
typename list<T>::const_reference list<T>::back() const {
    return this->tail_->data;
}

template <typename T>
list<T>::list(size_type size) :
    head_(nullptr),
    tail_(nullptr),
    size_(0) {
        if (size < 0) throw std::invalid_argument("The size must be greater than zero!");
        while (this->size_ < size) push_front(0);
}

template <typename T>
list<T>::list(std::initializer_list<T> const &items) :
    tail_(nullptr),
    head_(nullptr),
    size_(0) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        push_back(*it);
    }
}

template <typename T>
list<T>::list(const list &l) : list() {
    for (auto it = l.cbegin(); it != l.cend(); ++it) {
        push_back(*it);
    }
}

template <typename T>
list<T>::list(list &&l) :
    list() {
    *this = std::move(l);
}

template <typename T>
list<T> &list<T>::operator=(list &&l) {
    if (this == &l) return *this;
    if (!empty()) this->clear();
    this->size_ = l.size_;
    this->head_ = l.head_;
    this->tail_ = l.tail_;
    l.size_ = 0;
    l.head_ = nullptr;
    l.tail_ = nullptr;
    return *this;
}

template <typename T>
list<T>::~list() {
    this->clear();
}

template <typename T>
void list<T>::clear() {
    if (head_) {
        while (head_->next != nullptr) {
            head_ = head_->next;
            delete head_->prev;
        }
        delete head_;
        head_ = nullptr;
        size_ = 0;
    }
}

template <typename T>
void list<T>::push_back(const_reference value) {
    Node *tmp = new Node;
    tmp->data = value;
    if (this->head_ != nullptr) {
        this->tail_->next = tmp;
        tmp->prev = this->tail_;
        this->tail_ = tmp;
    } else {
        tmp->prev = nullptr;
        this->head_ = this->tail_ = tmp;
    }
    tmp->next = nullptr;
    ++size_;
}

template <typename T>
void list<T>::push_front(const_reference value) {
    Node *tmp = new Node;
    tmp->data = value;
    if (this->head_ != nullptr) {
        tmp->next = this->head_;
        this->head_->prev = tmp;
        this->head_ = tmp;
    } else {
        tmp->next = nullptr;
        this->head_ = this->tail_ = tmp;
    }
    tmp->prev = nullptr;
    ++size_;
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator position, const_reference value) {
    list<T>::iterator p(begin());
    ++size_;
    if (this->empty()) {
        this->push_front(value);
        p.setIter(head_);
    } else if (position.getIter() == head_) {
        this->push_front(value);
        p.setIter(head_);
    } else if (position.getIter() == tail_) {
        this->push_back(value);
        p.setIter(tail_);
    } else {
        while (p.getIter() != position.getIter()) ++p;
        --p;
        Node *elm = new Node;
        Node *tmp = p.getIter();
        elm->data = value;
        elm->next = tmp->next;
        elm->prev = tmp;
        tmp->next = elm;
        elm->next->prev = elm;
        p.setIter(elm);
    }
    return p;
}

template <typename T>
void list<T>::erase(iterator position) {
    if (empty()) {
        throw std::out_of_range("Error !The list is already empty");
    } else if (position.getIter() == nullptr) {
        throw std::out_of_range("Error ! The pointer does not point to anything");
    } else if (position.getIter() == this->head_) {
        pop_front();
    } else if (position.getIter() == this->tail_) {
        pop_back();
    } else {
        iterator p = begin();
        while (p.getIter() != position.getIter() && position.getIter() != nullptr) ++p;
        Node *elm = p.getIter();
        elm->prev->next = elm->next;
        elm->next->prev = elm->prev;
        delete elm;
    }
    --size_;
}

template <typename T>
void list<T>::pop_front() {
    if (!size()) throw std::out_of_range("List is Empty");
    if (size() == 1) {
        this->tail_ = this->head_ = nullptr;
    } else {
        Node *elm = head_;
        this->head_ = this->head_->next;
        this->head_->prev = nullptr;
        delete elm;
        elm = nullptr;
    }
    --size_;
}

template <typename T>
void list<T>::pop_back() {
    if (!size()) throw std::out_of_range("List is Empty");
    if (size() == 1) {
        this->tail_ = this->head_ = nullptr;
    } else {
        Node *elm = this->tail_;
        this->tail_ = tail_->prev;
        this->tail_->next = nullptr;
        delete elm;
        elm = nullptr;
    }
    --size_;
}

template <typename T>
void list<T>::reverse() {
    for (;;) {
        std::swap(this->head_->prev, this->head_->next);
        iterator tmp(this->head_->prev);
        if (!tmp.getIter()) break;
        this->head_ = tmp.getIter();
    }
}

template <typename T>
typename list<T>::size_type list<T>::size() const {
    return this->size_;
}

template <typename T>
bool list<T>::empty() const {
    return (this->size_ == 0) ? true : false;
}

template <typename T>
void list<T>::splice(const_iterator position, const list &other) {
    if (!other.empty()) {
        for (auto it = other.cbegin(); it != other.cend();) {
            this->insert(position, *it);
            ++it;
            other.pop_front();
        }
    }
}

template <typename T>
void list<T>::swap(list &other) {
    std::swap(this->size_, other.size_);
    std::swap(this->head_, other.head_);
    std::swap(this->tail_, other.tail_);
}

template <typename T>
typename list<T>::size_type list<T>::max_size() const {
    return (std::numeric_limits<size_type>::max() / sizeof(Node) / 2);
}

template <typename T>
void list<T>::unique() {
    if (!empty()) {
        iterator del;
        for (iterator p = this->begin(); p != this->end(); ++p) {
            if (p.getIter()->next != nullptr) {
                if (p.getIter()->data == p.getIter()->next->data) {
                    del = p;
                    ++p;
                    this->erase(del);
                }
            } else {
                break;
            }
        }
    }
}

template <typename T>
template <typename... Args>
void list<T>::emplace_back(Args &&...args) {
    list<T> tmp{ args... };
    for (iterator p = tmp.begin(); p != tmp.end(); ++p) {
        this->push_back(*p);
    }
}

template <typename T>
template <typename... Args>
void list<T>::emplace_front(Args &&...args) {
    list<T> tmp{ args... };
    for (iterator p = tmp.begin(); p != tmp.end(); ++p) {
        this->push_front(*p);
    }
}

template <typename T>
void list<T>::sort() {
    if (!empty()) {
        for (auto i = begin(); i != end(); ++i) {
            Node *current = i.getIter();
            for (auto j = i; j != end(); ++j) {
                Node *preCur = j.getIter();
                if (preCur->data < current->data) {
                    T swap = preCur->data;
                    preCur->data = current->data;
                    current->data = swap;
                }
            }
        }
    }
}

template <typename T>
void list<T>::print() const {
    const_iterator start(this->cbegin());
    std::cout << "================== S21 LIST ==============" << std::endl;
    while (start != cend()) {
        std::cout << *start << " ";
        ++start;
    }
    std::cout << std::endl;
    std::cout << "size :" << size_ << std::endl;
    std::cout << "========================================" << std::endl;
}

};  // namespace stl

