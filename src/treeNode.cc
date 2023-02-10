#include "treeNode.h"

namespace stl {

template <typename K, typename T>
treeNode<K, T> &treeNode<K, T>::operator=(const treeNode<K, T> &other) {
    data = other.data;
    parent = other.parent;
    left = other.left;
    right = other.right;
    return *this;
}

template <typename K, typename T>
treeNode<K, T> *treeNode<K, T>::minimalNode() {
    treeNode *min(this);
    while (min->left) {
        min = min->left;
    }
    return min;
}

template <typename K, typename T>
treeNode<K, T> *treeNode<K, T>::maximalNode() {
    treeNode *max(this);
    while (max->right) {
        max = max->right;
    }
    return max;
}

template <typename K, typename T>
treeNode<K, T> *treeNode<K, T>::nextNode() {
    treeNode<K, T> *p = this;
    if (p->right) {
        return p->right->minimalNode();
    } else if (p == p->parent->left && p->parent->left) {
        return p->parent;
    } else {
        treeNode *q = p->parent;
        if (q->parent == nullptr) return nullptr;
        while (p == q->right) {
            p = q;
            if (q->parent == nullptr) return nullptr;
            q = q->parent;
        }
        return q;
    }
}

template <typename K, typename T>
treeNode<K, T> *treeNode<K, T>::prevNode() {
    treeNode *p = this;
    if (p->left) {
        return p->left->maximalNode();
    } else if (p == p->parent->right) {
        return p->parent;
    } else {
        treeNode<K, T> *q = p->parent;
        if (q->parent == nullptr) return nullptr;
        while (p == q->left) {
            p = q;
            if (q->parent == nullptr) return nullptr;
            q = q->parent;
        }
        return q;
    }
}

};  //  namespace stl
