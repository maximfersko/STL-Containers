#include "btree.h"

namespace stl {

template <typename K, typename T>
Btree<K, T>& Btree<K, T>::operator=(Btree<K, T> &&other) {
    if (this == &other) return *this;
    if (root_) clear();
    size_ = other.size_;
    root_ = other.root_;
    other.root_ = nullptr;
    other.size_ = 0;
    return *this;
}

template <typename K, typename T>
Btree<K, T>::Btree(const Btree<K, T> &other) {
    for (auto &&item : other) insert(item);
}

template <typename K, typename T>
Btree<K, T>::Btree(const std::initializer_list<K> &items) : Btree() {
    for (auto &item : items) insert(item);
}

template <typename K, typename T>
void Btree<K, T>::clear() {
    if (root_) clean(this->root_);
    root_ = nullptr;
    size_ = 0;
}

template <typename K, typename T>
void Btree<K, T>::clean(Node *root) {
    if (root) {
        if (root->left) clean(root->left);
        if (root->right) clean(root->right);
        delete root;
    }
}

template <typename K, typename T>
Btree<K, T>::~Btree() {
    this->clear();
}

template <typename K, typename T>
size_t Btree<K, T>::max_size() {
    return std::numeric_limits<size_t>::max() / sizeof(Node) / 2;
}

template <typename K, typename T>
void Btree<K, T>::swap(Btree<K, T> &other) {
    if (this->root_ != other.root_) {
        std::swap(root_, other.root_);
        std::swap(size_, other.size_);
    }
}

template <typename K, typename T>
typename Btree<K, T>::iterator Btree<K, T>::find(const_reference_key key) {
    std::pair<iterator, bool> result = search(key);
    return result.first;
}

template <typename K, typename T>
bool Btree<K, T>::contains(const_reference_key key) {
    std::pair<iterator, bool> result = search(key);
    return (result.second == true) ? true : false;
}

template <typename K, typename T>
std::pair<typename Btree<K, T>::iterator, bool> Btree<K, T>::search(const_reference_key key) {
    std::pair<iterator, bool> result;
    result.second = false;
    result.first = root_;
    Node *p_root = root_;
    if (!empty()) {
        if (root_->data->first == key) {
            result.first.iter_ = p_root;
            result.second = true;
        } else {
            for (;;) {
                if (key < p_root->data->first && p_root->left != nullptr) {
                    if (p_root->left->data->first == key) {
                        result.first.iter_ = p_root->left;
                        result.second = true;
                        return result;
                    } else {
                        p_root = p_root->left;
                    }
                } else if (key > p_root->data->first && p_root->right != nullptr) {
                    if (p_root->right->data->first == key) {
                        result.first.iter_ = p_root->right;
                        result.second = true;
                        return result;
                    } else {
                        p_root = p_root->right;
                    }
                } else {
                    return result;
                }
            }
        }
    } else {
        result.second = false;
        return result;
    }

    return result;
}

template <typename K, typename T>
typename Btree<K, T>::iterator Btree<K, T>::insert(const_reference_key value) {
    Node *p = root_;
    Node *q = nullptr;
    iterator it;
    Node *elm = new Node;
    elm->data->first = value;
    ++size_;
    while (p) {
        q = p;
        p = (elm->data->first < p->data->first) ? p->left : p->right;
    }
    elm->parent = q;
    if (q == nullptr) {
        root_ = elm;
        it.iter_ = root_;
    } else if (elm->data->first < q->data->first) {
        q->left = elm;
        it.iter_ = q->left;
    } else {
        q->right = elm;
        it.iter_ = q->right;
    }
    return it;
}


template <typename K, typename T>
void Btree<K, T>::erase(iterator pos) {
    std::cout << "before: " << std::endl;
    this->print(this->root_);
    std::cout << std::endl;
    Node *current = pos.iter_;
    if (current == nullptr) throw std::out_of_range("position not be a nullptr!");
    if (current->left == nullptr && current->right == nullptr) {
        std::cout << "no child " << std::endl;
        if (current->parent == nullptr) {
           // root_ = nil_;
        } else if (current == current->parent->left) {
            current->parent->left = current->left;
        } else if (current == current->parent->right) {
            current->parent->right = current->right;
        }
        --size_;
        delete current;
        current = nullptr;
    } else if (current->left == nullptr && current->right != nullptr) {
        std::cout << "right child " << std::endl;
        Node *tmp = current->right->minimalNode();
        if (current->parent != nullptr) {
            if (current->parent->left == current) {
                current->parent->left = current->right;
            } else if (current->parent->right == current) {
                current->parent->right = current->right;
            }
        } else {
            tmp->left = nullptr;
            root_ = current->left;
        }
        current->right->parent = current->parent;
        --size_;
        delete current;
    } else if (current->left != nullptr && current->right == nullptr) {
        std::cout << "left child " << std::endl;
        Node *tmp = current->left->maximalNode();
        if (current->parent != nullptr) {
            if (current->parent->left == current) {
                current->parent->left = current->left;
            } else if (current->parent->right == current) {
                current->parent->right = current->left;
            }
        } else {
            root_ = current->right;
        }
        current->left->parent = current->parent;
        --size_;
        delete current;
        current = nullptr;
    } else {
        std::cout << "two  child " << std::endl;
        --size_;
        Node *replace = current->right->minimalNode();
        current->data->first = replace->data->first;
        if (sizeof(current->data->second) == sizeof(std::string))  {
            if (current->data->second != "") current->data->second = replace->data->second;
        } else {
            current->data->second = replace->data->second;
        }
        // if (current->parent == nullptr) {
        //     replace->parent = nullptr;
        //     root_ = replace;
        // }
        if (replace->parent->left == replace) {
            replace->parent->left = replace->right;
        } else {
            replace->parent->right = replace->right;
        }
        delete replace;
        replace = nullptr;
    }
    std::cout << "after: " << std::endl;
    this->print(this->root_);
    std::cout << std::endl;
}

template <typename K, typename T>
void Btree<K, T>::print(Node *root) {
    if (root == nullptr) return;
    print(root->left);
    std::cout << root->data->first << " ";
    print(root->right);
}

template <typename K, typename T>
void Btree<K, T>::printTree(Node *elm, int depth) {
    if (elm->right) {
            printTree(elm->right, depth + 4);
    }
    if (depth) {
        std::cout << std::setw(depth) << " ";
    }
    if (elm->right) {
        std::cout << " /\n" << std::setw(depth) << " ";
    }
    std::cout << elm->data->first << "\n ";
    if (elm->left) {
        std::cout << std::setw(depth) << " "
                            << " \\\n";
            printTree(elm->left, depth + 4);
    }
}

template <typename K, typename T>
typename Btree<K, T>::Iterator Btree<K, T>::begin() const {
    Iterator start;
    if (root_ != nullptr) start.iter_ = root_->minimalNode();
    return start;
}

template <typename K, typename T>
typename Btree<K, T>::Iterator Btree<K, T>::end() const {
    Iterator last;
    if (root_ != nullptr) {
        last.iter_ = nullptr;
    }
    return last;
}

template <typename K, typename T>
void Btree<K, T>::Iterator::operator++() {
    if (iter_ != nullptr) iter_ = iter_->nextNode();
}

template <typename K, typename T>
void Btree<K, T>::Iterator::operator--() {
    if (iter_->prevNode()) iter_ = iter_->prevNode();
}

template <typename K, typename T>
bool Btree<K, T>::Iterator::operator==(const Iterator &other) {
    return (this->iter_ == other.iter_) ? true : false;
}

template <typename K, typename T>
bool Btree<K, T>::Iterator::operator!=(const Iterator &other) {
    return (this->iter_ != other.iter_) ? true : false;
}

template <typename K, typename T>
typename Btree<K, T>::key_type Btree<K, T>::Iterator::operator*() {
    if (iter_ == nullptr)  throw std::out_of_range("Error! is not be a nullptr");
    return iter_->data->first;
}

};    // namespace stl
