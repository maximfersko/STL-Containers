#include "stl_multiset.h"

namespace stl {

template <typename K>
multiset<K>::multiset(std::initializer_list<value_type> const &items) {
    for (auto &item : items) this->tree_->insert(item);
}

template <typename K>
multiset<K>& multiset<K>::operator=(multiset &&other) {
    if (this == &other) return *this;
    this->tree_ = std::move(other.tree_);
    other.tree_ = nullptr;
    return *this;
}


template <typename K>
typename multiset<K>::size_type multiset<K>::count(const_reference key) {
    size_type result = 0;
    for (auto i = this->begin(); i != this->end(); ++i) {
        if (*i == key) ++result;
    }
    return result;
}

template <typename K>
typename multiset<K>::iterator multiset<K>::lower_bound(const_reference key) {
    auto it = this->begin();
    for (; it != this->end() && *it < key; ++it) {}
    return it;
}

template <typename K>
typename multiset<K>::iterator multiset<K>::upper_bound(const_reference key) {
    auto it = this->begin();
    for (; it != this->end() && *it <= key; ++it) {}
    return it;
}

template <typename K>
std::pair<typename multiset<K>::iterator, typename multiset<K>::iterator>
multiset<K>::equal_range(const_reference key) {
    std::pair<iterator, iterator> result;
    result.first = lower_bound(key);
    result.second = upper_bound(key);
    return result;
}

template <typename K>
template <typename... Args>
std::pair<typename multiset<K>::iterator, bool> multiset<K>::emplace(Args&&... args) {
    std::pair<iterator, bool> result{nullptr, true};
    value_type items[] = { args... };
    for (value_type &item : items) {
        result.first = insert(item);
    }
    return result;
}

};  // namespace stl
