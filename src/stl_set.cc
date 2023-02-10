#include "stl_set.h"
namespace  stl {

template <typename K>
set<K>& set<K>::operator=(set &&other) {
    if (this == &other) return *this;
    tree_ = std::move(other.tree_);
    other.tree_ = nullptr;
    return *this;
}

template <typename K>
std::pair<typename set<K>::iterator, bool> set<K>::insert(set<K>::const_reference value) {
    std::pair<iterator, bool> result;
    result.second = false;
    if (tree_->contains(value) != true) {
        result.first = tree_->insert(value);
        result.second = true;
    } else {
        result.first = tree_->find(value);
    }
    return result;
}

template <typename K>
void set<K>::merge(const set &other) {
    for (auto it = other.cbegin(); it != other.cend(); ++it) {
        insert(*it);
    }
    other.clear();
}

template <typename K>
template <typename... Args>
std::pair<typename set<K>::iterator, bool> set<K>::emplace(Args&&... args) {
    std::pair<set<K>::iterator, bool> result{nullptr, true};
    value_type items[] = { args... };
    for (value_type &item : items) {
        result = insert(item);
        if (!result.second) result.first = find(item);
    }
    return result;
}

};  //  namespace s21
