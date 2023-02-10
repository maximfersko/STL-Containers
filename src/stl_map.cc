namespace stl {

template <typename K, typename T>
map<K, T>::map(map<K, T> &&other) {
    *this = std::move(other);
}

template <typename K, typename T>
map<K, T>::map(const map<K, T> &other) {
    for (auto value : other) insert(value);
}

template <typename K, typename T>
map<K, T>::map(std::initializer_list<value_type> const &items) {
    for (auto &item : items) insert(item);
}

template <typename K, typename T>
map<K, T>& map<K, T>::operator=(map<K, T> &&other) {
    if (this->root_ != nullptr) this->clear();
    this->root_ = other.root_;
    this->size_ = other.size_;
    other.root_ = nullptr;
    other.size_ = 0;
    return *this;
}

template <typename K, typename T>
typename map<K, T>::const_reference_value map<K, T>::operator[](const_reference_key key) {
    auto result = Btree<K, T>::search(key);
    return result.first.iter_->data->second;
}

template <typename K, typename T>
typename map<K, T>::const_reference_value map<K, T>::at(const_reference_key key) {
    if (!this->search(key).second) throw std::out_of_range("ERROR!");
    return(*this)[key];
}

template <typename K, typename T>
typename map<K, T>::iteratorMap map <K, T>::begin() const {
    iteratorMap it;
    if (this->root_ != nullptr) it.iter_ = this->root_->minimalNode();
    return it;
}

template <typename K, typename T>
typename map<K, T>::iteratorMap map <K, T>::end() const {
    iteratorMap it;
    if (this->root_ != nullptr) it.iter_ = nullptr;
    return it;
}

template <typename K, typename T>
typename map<K, T>::value_type map<K, T>::iteratorMap::operator*() {
    if (this->iter_ == nullptr) throw std::invalid_argument("Error pointer is not be nullptr");
    return *this->iter_->data;
}

template <typename K, typename T>
std::pair<typename map<K, T>::iterator, bool> map<K, T>::insert(const_reference_key key, \
    const_reference_value obj) {
    std::pair<iterator, bool> result = Btree<K, T>::search(key);
    if (!this->contains(key)) {
        result.first = Btree<K, T>::insert(key);
        result.first.iter_->data->second = obj;
        result.second = true;
    }
    return result;
}

template <typename K, typename T>
std::pair<typename map<K, T>::iterator, bool> map<K, T>::insert_or_assign(const_reference_key key, \
    const_reference_value obj) {
    auto result = this->search(key);
    if (!result.second) result.first = Btree<K, T>::insert(key);
    result.first.iter_->data->second = obj;
    result.second = !result.second;
    return result;
}

template <typename K, typename T>
void map<K, T>::merge(map &other) {
    for (auto it = other.begin(); it != other.end(); ++it) {
        insert(*it);
    }
    other.clear();
}

template <typename K, typename T>
template <typename... Args>
std::pair<typename map<K, T>::iterator, bool> map<K, T>::emplace(Args&&... args) {
    std::pair<iterator, bool> result{nullptr, true};
    std::pair<K, T> items[] = { args... };
    for (std::pair<key_type, map_type> &item : items) {
        result = insert(item.first, item.second);
        if (!result.second) {
            result = this->search(item.first);
            result.second = false;
        }
    }
    return result;
}

};  //  namespace stl
