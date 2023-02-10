#include "stl_vector.h"

namespace stl {

template <typename T>
vector<T>::vector() :
    size_(0U),
    capacity_(0U),
    data_(nullptr) {}

template <typename T>
vector<T>::vector(vector<T>::size_type size) :
    capacity_(size),
    size_(size) {
    if (size < 1) throw std::invalid_argument("Error");
    this->data_ = new value_type[this->capacity_]{};
}

template <typename T>
vector<T>::vector(std::initializer_list<vector<T>::value_type> const &items) :
    vector(items.size()) {
        int i = 0;
        for (auto it = items.begin(); it != items.end(); it++) this->data_[i++] = *it;
        this->size_ = items.size();
        this->capacity_ = items.size();
}

template <typename T>
vector<T>::vector(const vector<T> &v) :
    size_(v.size_),
    capacity_(v.capacity_),
    data_(nullptr) {
    this->data_ = new value_type[this->capacity_]{};
    for (int i = 0; i < v.size(); i++) {
        this->data_[i] = v.data_[i];
    }
}

template <typename T>
vector<T>::vector(vector &&v) :
    capacity_(v.capacity_),
    size_(v.size_),
    data_(nullptr) {
    std::swap(this->data_, v.data_);
}

template <typename T>
vector<T>& vector<T>::operator=(vector &&v) {
    if (this == &v) return *this;
    this->clear();
    this->capacity_ = v.capacity_;
    this->size_ = v.size_;
    if (data_) delete[] data_;
    data_ = nullptr;
    std::swap(this->data_, v.data_);
    return *this;
}

template <typename T>
bool  vector<T>::empty() {
    return (this->size_ != 0) ? false : true;
}

template <typename T>
typename vector<T>::size_type vector<T>::size() const {
    return this->size_;
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() const {
    return this->capacity_;
}

template <typename T>
vector<T>::~vector() {
    this->freeArray();
}

template <typename T>
void vector<T>::clear() {
    this->size_ = 0;
}

template <typename T>
void vector<T>::freeArray() {
    if (this->data_) {
        delete[] this->data_;
        this->data_ = nullptr;
    }
    this->size_ = 0;
    this->capacity_ = 0;
}

template <typename T>
typename vector<T>::iterator vector<T>::begin() {
    return this->data_;
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cbegin() const {
    return this->data_;
}

template <typename T>
typename vector<T>::iterator vector<T>::end() {
    return this->size_ + this->data_;
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cend() const {
    return this->data_ + this->size_;
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](vector<T>::size_type index) const {
    return this->data_[index];
}

template <typename T>
typename vector<T>::reference vector<T>::at(vector<T>::size_type position) const {
    if (position > this->size_) throw std::out_of_range("Error");
    return this->data_[position];
}

template <typename T>
typename vector<T>::reference vector<T>::back() {
    if (empty()) throw std::out_of_range("Error");
    return this->data_[this->size_ - 1];
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() const {
    if (empty()) throw std::out_of_range("Error");
    return this->data_[this->size_ - 1];
}

template <typename T>
void vector<T>::push_back(vector<T>::const_reference value) {
    if (this->capacity_ == this->size_) reserve(this->capacity_ * 2);
    this->data_[this->size_] = value;
    ++size_;
}

template <typename T>
void vector<T>::reallocate() {
    iterator tmp = new value_type[capacity_]{};
    for (size_type i = 0; i < this->size_; ++i) {
        tmp[i] = this->data_[i];
    }
    std::swap(this->data_, tmp);
    delete[] tmp;
}

template <typename T>
void vector<T>::resize(vector<T>::size_type newsize_) {
    if (this->size_ != newsize_ && this->size_ < newsize_) {
        this->reserve(newsize_);
        this->size_ = newsize_;
    } else if (this->size_ > newsize_) {
        while (this->size_ > newsize_) this->pop_back();
    }
}

template <typename T>
void vector<T>::reserve(vector<T>::size_type newsize_) {
    if (newsize_ > 0 && this->size_ > 0) {
        this->capacity_ = newsize_;
        this->reallocate();
    }
    //  size_ = newsize_;
}

template <typename T>
typename vector<T>::reference vector<T>::front() {
    return this->data_[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() const {
    return this->data_[0];
}

template <typename T>
typename vector<T>::const_iterator vector<T>::data() const {
    return this->data_;
}

template <typename T>
typename vector<T>::iterator vector<T>::data() {
    return this->data_;
}

template <typename T>
void vector<T>::swap(vector &other) {
    std::swap(this->data_, other.data_);
    std::swap(this->size_, other.size_);
    std::swap(this->capacity_, other.capacity_);
}

template <typename T>
void vector<T>::shrink_to_fit() {
    if (this->size_ < this->capacity_) {
        vector<value_type> tmp(this->size_);
        for (int i = 0; i < this->size_; i++) tmp.data_[i] = this->data_[i];
        delete[] this->data_;
        this->data_ = tmp.data_;
        tmp.data_ = nullptr;
        this->capacity_ = tmp.capacity_;
    }
}

template <typename T>
void vector<T>::pop_back() {
    if (!empty()) --size_;
}

template <typename T>
typename vector<T>::reverse_iterator vector<T>::rbegin() {
    return reverse_iterator(this->end());
}

template <typename T>
typename vector<T>::reverse_iterator vector<T>::rend() {
    return reverse_iterator(this->begin());
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() const {
    return std::numeric_limits<size_t>::max() / (sizeof(vector<T>) * 2);
}

template <typename T>
void vector<T>::print() const {
    vector<T>::size_type index = 0;
    for (vector<T>::size_type i = 0; i < this->size(); ++i) {
        std::cout << "array" << "[" << i << "]" << " = " << this->at(index++) << std::endl;
    }
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(vector<T>::iterator position, \
    vector<T>::const_reference value) {
    if (this->size_ == this->capacity_) this->reserve(this->capacity_ * 2);
    size_type indexIterartor = position - this->begin();
    for (size_type i = this->size_; i > indexIterartor; --i) {
        this->data_[i] = this->data_[i - 1];
        if (i == indexIterartor) this->data_[i] = value;
    }
    ++size_;
    this->data_[indexIterartor] = value;
    position = this->data_ + indexIterartor;
    return position;
}

template<typename T>
void vector<T>::erase(vector<T>::const_iterator position) {
    if (size_ > 0) {
       vector<T>::size_type index = position - this->begin();
       for (size_type i = index; i < this->size() - 1; ++i) {
            this->data_[i] = this->data_[i + 1];
       }
       --size_;
    }
}

template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::emplace(const_iterator position, Args&&... args) {
    iterator it = (iterator)position;
    value_type items[] = {args...};
    for (auto item : items) {
        it = this->insert(it, item);
        ++it;
    }
    --it;
    return it;
}

template <typename T>
template <typename... Args>
void vector<T>::emplace_back(Args&&... args) {
    this->emplace(this->end(), args...);
}

};  //  namespace stl
