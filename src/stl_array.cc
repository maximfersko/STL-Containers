#include "stl_array.h"


namespace stl {

template <typename T, size_t s>
bool array<T, s>::empty() const {
    return (this->size_ != 0) ? false : true;
}

template <typename T, size_t s>
array<T, s>::array() {
    this->data_ = new value_type[s]{};
    this->size_ = s;
}

template <typename T, size_t s>
array<T, s>::array(std::initializer_list<value_type> const &items) : array() {
    size_type index = 0;
    for (auto i = items.begin(); i != items.end(); ++i) {
        this->data_[index++] = *i;
        ++size_;
    }
}

template <typename T, size_t s>
array<T, s>::array(const array &a) : size_(a.size_) {
    this->data_ = new value_type[this->size_]{};
    for (size_type i = 0; i < a.size(); ++i) this->data_[i] = a.data_[i];
}

template <typename T, size_t s>
array<T, s>::array(array &&a) : data_(nullptr), size_(0) {
    if (this == &a) return;
    this->data_ = a.data_;
    this->size_ = a.size_;
    a.data_ = nullptr;
    a.size_ = 0;
}

template <typename T, size_t s>
array<T, s>& array<T, s>::operator=(array &&a) {
    if (this == &a) return *this;
    this->freeArray();
    this->size_ = a.size_;
    a.size_ = 0;
    std::swap(this->data_, a.data_);
    return *this;
}

template <typename T, size_t s>
void array<T, s>::freeArray() {
    if (this->data_ != nullptr) {
        delete [] this->data_;
        this->data_ = nullptr;
    }
    this->size_ = 0;
}

template <typename T, size_t s>
array<T, s>::~array() {
    this->freeArray();
}

template <typename T, size_t s>
typename array<T, s>::reference array<T, s>::operator[](size_type index) const {
    return this->data_[index];
}

template <typename T, size_t s>
typename array<T, s>::reference array<T, s>::at(size_type position) const {
    if (position > size_) throw std::out_of_range("Error");
    return this->data_[position];
}

template <typename T, size_t s>
void array<T, s>::swap(array &other) {
    std::swap(this->data_, other.data_);
    std::swap(this->size_, other.size_);
}

template <typename T, size_t s>
void array<T, s>::fill(const_reference value) {
    for (size_type i = 0; i < size_; ++i) this->data_[i] = value;
}

template <typename T, size_t s>
typename array<T, s>::const_reference array<T, s>::back() {
    if (empty()) throw std::out_of_range("Error");
    return this->data_[this->data_ + s];
}

template <typename T, size_t s>
typename array<T, s>::const_reference array<T, s>::front() {
    if (empty()) throw std::out_of_range("Error");
    return this->data_[0];
}

template <typename T, size_t s>
typename array<T, s>::iterator array<T, s>::begin() {
    return this->data();
}

template <typename T, size_t s>
typename array<T, s>::iterator array<T, s>::end() {
    return this->data_ + this->size_;
}

};  // namespace stl
