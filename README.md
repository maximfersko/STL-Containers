# STL-Containers

# Btree

The Btree class is a template class representing a B-tree data structure. It stores key-value pairs and allows efficient insertion, deletion, and search operations. The B-tree is a self-balancing binary search tree that maintains sorted data within its nodes.

## Class Template Parameters

- K: The type of the key.
- T: The type of the value.

## Member Types

- map_type: The type of the mapped value.
- key_type: The type of the key.
- const_reference_key: The type of the constant reference to the key.
- value_type: The type of the key-value pair.
- size_type: The type for representing the size of the B-tree.
- Node: The type representing the tree node.

### Iterators

- iterator begin() const: Returns an iterator pointing to the beginning of the B-tree.
- iterator end() const: Returns an iterator pointing to the end of the B-tree.

### Methods

- iterator insert(const_reference_key& value): Inserts a key-value pair into the B-tree.
- void erase(iterator pos): Erases the element at the specified position in the B-tree.
- void print(Node* root): Prints the elements of the B-tree.
- void printTree(Node* elm, int depth): Prints the B-tree structure.
- Node* getRoot(): Returns a pointer to the root node of the B-tree.
- void clear(): Clears all the elements in the B-tree.
- bool empty() const: Checks if the B-tree is empty.
- size_t size() const: Returns the number of elements in the B-tree.
- size_t max_size(): Returns the maximum number of elements the B-tree can hold.
- void copy(Node* root): Copies the elements of the B-tree from the specified root node.
- void swap(Btree<K, T>& other): Swaps the contents of two Btree objects.
- iterator find(const_reference_key key): Finds the specified key in the B-tree.
- bool contains(const_reference_key key): Checks if the B-tree contains the specified key.

## Iterator Class

The Iterator class is an iterator for iterating over the elements of the B-tree.

### Member Functions

- void operator++(): Moves the iterator to the next element.
- void operator--(): Moves the iterator to the previous element.
- bool operator==(const Iterator& other): Checks if the iterator is equal to another iterator.
- bool operator!=(const Iterator& other): Checks if the iterator is not equal to another iterator.
- key_type operator*(): Dereferences the iterator to get the current key.

## Example Usage

#include "btree.h"
using namespace stl;

```c
int main() {
  // Create a B-tree with integer keys and string values
  Btree<int, std::string> btree;

  // Insert key-value pairs into the B-tree
  btree.insert(std::make_pair(10, "apple"));
  btree.insert(std::make_pair(20, "banana"));
  btree.insert(std::make_pair(30, "cherry"));

  // Print the elements of the B-tree
  btree.print(btree.getRoot());

  // Find a key in the B-tree
  Btree<int, std::string>::iterator iter = btree.find(20);
  if (iter != btree.end()) {
    std::cout << "Found key: " << *iter << std::endl;
  }

  return 0;
}
```
