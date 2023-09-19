# STL-Containers

## Btree

The Btree class is a template class representing a B-tree data structure. It stores key-value pairs and allows efficient insertion, deletion, and search operations. The B-tree is a self-balancing binary search tree that maintains sorted data within its nodes.

### Class Template Parameters

- `K` - The type of the key.
- `T` - The type of the value.

### Member Types

- `map_type` - The type of the mapped value.
- `key_type` - The type of the key.
- `const_reference_key` - The type of the constant reference to the key.
- `value_type` - The type of the key-value pair.
- `size_type` - The type for representing the size of the B-tree.
- `Node` - The type representing the tree node.

### Iterators

- `iterator begin() const` - Returns an iterator pointing to the beginning of the B-tree.
- `iterator end() const` - Returns an iterator pointing to the end of the B-tree.

### Methods

- `iterator insert(const_reference_key& value)` - Inserts a key-value pair into the B-tree.
- `void erase(iterator pos)` - Erases the element at the specified position in the B-tree.
- `void print(Node* root)` - Prints the elements of the B-tree.
- `void printTree(Node* elm, int depth)` - Prints the B-tree structure.
- `Node* getRoot()` - Returns a pointer to the root node of the B-tree.
- `void clear()` - Clears all the elements in the B-tree.
- `bool empty() const` - Checks if the B-tree is empty.
- `size_t size() const` - Returns the number of elements in the B-tree.
- `size_t max_size()` - Returns the maximum number of elements the B-tree can hold.
- `void copy(Node* root)` - Copies the elements of the B-tree from the specified root node.
- `void swap(Btree<K, T>& other)` - Swaps the contents of two Btree objects.
- `iterator find(const_reference_key key)` - Finds the specified key in the B-tree.
- `bool contains(const_reference_key key)` - Checks if the B-tree contains the specified key.

### Iterator Class

The Iterator class is an iterator for iterating over the elements of the B-tree.


### Example Usage

#include "btree.h"
using namespace stl;

```cpp
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


## array

The `array` class is a fixed-size container that encapsulates an array of elements. It provides a simple interface to access and manipulate the elements.

### Template Parameters

- `T` - The type of the elements stored in the array.
- `s` - The size of the array. It must be a compile-time constant.

### Member Types

- `value_type` - The type of the elements stored in the array.
- `reference` - The type of the reference to an element.
- `const_reference` - The type of the constant reference to an element.
- `iterator` - The type of the iterator.
- `const_iterator` - The type of the constant iterator.
- `size_type` - The type for representing the size of the array.

### Methods

- `size_type size() const` - Returns the size of the array.
- `bool empty() const` - Checks if the array is empty.
- `reference at(size_type position) const` - Accesses the element at the specified position in the array.
- `void swap(array& other)` - Swaps the contents of two arrays.
- `void fill(const_reference)` - Fills the array with the specified value.
- `size_type max_size() const` - Returns the maximum number of elements the array can hold.
- `const_reference back()` - Returns a reference to the last element of the array.
- `const_reference front()` - Returns a reference to the first element of the array.
- `iterator data()` - Returns a pointer to the underlying array data.

### Iterators

- `iterator begin()` - Returns an iterator pointing to the first element of the array.
- `iterator end()` - Returns an iterator pointing to the past-the-end element of the array.

### Operators

- `reference operator[](size_type index) const` - Accesses the element at the specified index in the array.
- `array<T, s>& operator=(array&& a)` - Move assignment operator.

### Example Usage

```cpp
#include "stl_array.h"
using namespace stl;

int main() {
  // Create an array of integers with size 5
  array<int, 5> arr;

  // Fill the array with the value 10
  arr.fill(10);

  // Access and modify elements using the index operator
  arr[2] = 20;

  // Print the elements of the array using iterators
  for (auto it = arr.begin(); it != arr.end(); ++it)
  {
    std::cout << *it << " ";
  }

  return 0;
}
```

## List

# Documentation for the `list` class from the file `stl_list.h`

The `list` class represents an implementation of a doubly linked list. It includes various methods for working with the list data.

## Type Definitions

```cpp
`value_type = T`;
using reference = value_type &;
using const_reference = const value_type &;
using size_type = size_t;
```

## Nested Structure `Node`

```cpp
struct Node {
  value_type data;
  Node *next;
  Node *prev;
};
```

The `Node` structure represents a node in the list and holds the data `data` along with pointers to the next and previous nodes in the list.

## Nested Class `ListIterator`

```cpp
class ListIterator {
 private:
  Node *iter_;
  Node *head_;
  Node *tail_;

 public:
  Node *getIter();
  void setIter(Node *value);
  Node *getHead();
  void setHead(Node *value);
  Node *getTail();
  void setTail(Node *value);

  ListIterator();
  explicit ListIterator(Node *other);
  explicit ListIterator(const list<T> &other);

  reference operator*();
  ListIterator &operator--();
  ListIterator &operator++();
  bool operator==(const ListIterator &other);
  bool operator<=(const ListIterator &other);
  bool operator!=(const ListIterator &other);
};
```

The `ListIterator` class represents an iterator for traversing the list. It implements data access operators and comparison operators.

## Nested Class `ListConstIterator`

```cpp
class ListConstIterator {
 private:
  Node *iter_;
  Node *head_;
  Node *tail_;

 public:
  Node *getIter();
  void setIter(Node *value);
  Node *getHead();
  void setHead(Node *value);
  Node *getTail();
  void setTail(Node *value);

  ListConstIterator();
  explicit ListConstIterator(Node *other);
  explicit ListConstIterator(const list<T> &other);

  const_reference operator*();
  ListConstIterator &operator++();
  ListConstIterator &operator--();
  bool operator==(const ListConstIterator &other);
  bool operator!=(const ListConstIterator &other);
};
```

The `ListConstIterator` class represents a constant iterator for traversing the list. It implements data access operators and comparison operators.

The list class represents a doubly linked list data structure. It has various methods for manipulating the list and accessing its elements.

### Type Definitions
- `value_type` - The type of the elements in the list.
- `reference` - A reference to `value_type`.
- `const_reference` - A constant reference to `value_type`.
- `size_type` - An unsigned integral type representing the size of the list.

### Nested Structure Node
The `Node` structure represents a node in the list and holds the data of type `value_type`. It also contains pointers to the next and previous nodes in the list.

### Nested Class ListIterator
The `ListIterator` class represents an iterator for traversing the list. It has methods for accessing and modifying the iterator's state. It also implements data access operators and comparison operators.

### Nested Class ListConstIterator
The `ListConstIterator` class represents a constant iterator for traversing the list. It has methods for accessing and modifying the iterator's state. It also implements data access operators and comparison operators.

### Class list
The `list` class represents a doubly linked list. It has the following public methods:

#### Constructors and Destructor
- `list()` - Constructs an empty list.
- `explicit list(size_type size)` - Constructs a list with `size` default-inserted elements.
- `explicit list(std::initializer_list<T> const &items)` - Constructs a list with the elements from the initializer list `items`.
- `list(const list &l)` - Constructs a copy of the list `l`.
- `list(list &&l)` - Constructs a list by moving the contents of `l`.
- `list<T> &operator=(list &&l)` - Assigns the contents of the list `l` to the list.
- `~list()` - Destroys the list and frees the memory.

#### Iterators
- `iterator begin()` - Returns an iterator to the beginning of the list.
- `iterator end()` - Returns an iterator to the end of the list.
- `const_iterator begin() const` - Returns a constant iterator to the beginning of the list.
- `const_iterator end() const` - Returns a constant iterator to the end of the list.
- `const_iterator cbegin() const` - Returns a constant iterator to the beginning of the list.
- `const_iterator cend() const` - Returns a constant iterator to the end of the list.

#### Capacity
- `bool empty() const` - Checks if the list is empty.
- `size_type size() const` - Returns the number of elements in the list.

#### Modifiers
- `void clear()` - Removes all elements from the list.
- `iterator insert(iterator pos, const T& value)` - Inserts a new element with the value `value` before the element at the specified position `pos` in the list. Returns an iterator pointing to the inserted element.
- `iterator erase(iterator pos)` - Removes the element at the specified position `pos` in the list. Returns an iterator pointing to the element that followed the erased element.
- `void push_back(const T& value)` - Appends the element `value` to the end of the list.
- `void push_front(const T& value)` - Prepends the element `value` to the beginning of the list.
- `void pop_back()` - Removes the last element from the list.
- `void pop_front()` - Removes the first element from the list.
- `void resize(size_type count)` - Resizes the list to contain `count` elements. If `count` is greater than the current size, additional elements are default-inserted. If `count` is less than the current size, excess elements are removed.
- `void swap(list<T>& other)` - Swaps the contents of the list with the contents of `other`.

#