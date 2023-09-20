# STL-Containers

# Btree

The Btree class is a template class representing a B-tree data structure. It stores key-value pairs and allows efficient insertion, deletion, and search operations. The B-tree is a self-balancing binary search tree that maintains sorted data within its nodes.

## Class Template Parameters

- `K` - The type of the key.
- `T` - The type of the value.

## Member Types

- `map_type` - The type of the mapped value.
- `key_type` - The type of the key.
- `const_reference_key` - The type of the constant reference to the key.
- `value_type` - The type of the key-value pair.
- `size_type` - The type for representing the size of the B-tree.
- `Node` - The type representing the tree node.

## Iterators

- `iterator begin() const` - Returns an iterator pointing to the beginning of the B-tree.
- `iterator end() const` - Returns an iterator pointing to the end of the B-tree.

## Methods

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

## Iterator Class

The Iterator class is an iterator for iterating over the elements of the B-tree.


## Example Usage

```cpp
#include "btree.h"
using namespace stl;

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


# Map

The Map class is a template class representing an associative container based on a binary search tree. It stores key-value pairs and allows efficient insertion, deletion, and search operations. The keys are unique and sorted in the map.

## Class Template Parameters

- `K` - The type of the key.
- `T` - The type of the value.

## Member Types

- `map_type` - The type of the value stored in the map.
- `key_type` - The type of the key stored in the map.
- `const_reference_key` - A reference to a constant key.
- `const_reference_value` - A reference to a constant value.
- `value_type` - The type of the key-value pair stored in the map.
- `const_reference` - A reference to a constant key-value pair.
- `size_type` - The type used to represent sizes.
- `iterator` - An iterator for traversing the elements of the map.
- `Node` - The type representing the tree node.

## IteratorMap Class

The IteratorMap class is a derived class of the iterator class, providing additional functionality specific to maps.

## Constructors

- `Map()` - Constructs an empty map.
- `Map(Map<K, T>&& other)` - Move constructor.
- `explicit Map(const Map<K, T>& other)` - Copy constructor.
- `explicit Map(std::initializer_list<value_type> const& items)` - Constructs a map with the given set of key-value pairs.

## Destructor

- `~Map()` - Destructs the map and frees any dynamically allocated memory.

## Methods

- `std::pair<iterator, bool> insert(const_reference_key key, const_reference_value obj)` - Inserts a key-value pair into the map.
- `std::pair<iterator, bool> insert(const_reference value)` - Inserts a key-value pair into the map. (Overload)
- `const_reference_value operator[](const_reference_key key)` - Accesses the value associated with the specified key.
- `const_reference_value at(const_reference_key key)` - Accesses the value associated with the specified key. Throws an exception if the key is not found.
- `std::pair<iterator, bool> insert_or_assign(const_reference_key key, const_reference_value obj)` - Inserts or assigns a key-value pair in the map.
- `void merge(map &other)` - Merges the contents of another map into this map.
- `template <typename... Args> std::pair<iterator, bool> emplace(Args&&... args)` - Constructs and inserts an element into the map.

## Additional Methods

- `iterator erase(const_iterator position)` - Erases the element at the specified position in the map.
- `iterator erase(const_iterator first, const_iterator last)` - Erases a range of elements in the map.
- `size_type erase(const_reference_key key)` - Erases all elements in the map with a specific key.
- `void clear()` - Clears all elements in the map, making it empty.
- `size_type count(const_reference_key key) const` - Returns the number of elements with the specified key in the map.
- `iterator find(const_reference_key key)` - Finds an element with the specified key in the map and returns an iterator to it.
- `const_iterator find(const_reference_key key) const` - Finds an element with the specified key in the map and returns a const_iterator to it.
- `bool contains(const_reference_key key) const` - Checks if the map contains an element with the specified key.

These additional methods allow you to perform common map operations such as erasing elements, clearing the map, counting occurrences of keys, finding elements, and checking for key existence.

## Example Usage

```cpp
#include "stl_map.h"  // Include the Map class header

int main() {
  // Create a Map with integer keys and string values
  stl::Map<int, std::string> map;

  // Insert key-value pairs into the map using the insert method
  map.insert(std::make_pair(10, "apple"));
  map.insert(std::make_pair(20, "banana"));
  map.insert(std::make_pair(30, "cherry"));

  // Access values using operator[] (subscript operator)
  std::cout << "Value for key 20: " << map[20] << std::endl;

  // Access values using at() method
  try {
    std::cout << "Value for key 40: " << map.at(40) << std::endl;  // Throws an exception since key 40 is not present
  } catch (const std::out_of_range& e) {
    std::cerr << "Key not found: " << e.what() << std::endl;
  }

  // Insert or assign key-value pairs using insert_or_assign method
  map.insert_or_assign(20, "orange");  // Key 20 already exists, so the value is updated to "orange"

  // Merge the contents of another map into this map
  stl::Map<int, std::string> otherMap;
  otherMap.insert(std::make_pair(40, "grape"));
  otherMap.insert(std::make_pair(50, "kiwi"));
  map.merge(otherMap);

  // Emplace key-value pairs into the map
  map.emplace(60, "pear");
  map.emplace(70, "plum");

  // Erase elements by key
  map.erase(30);  // Erases the key-value pair with key 30

  // Clear all elements in the map
  map.clear();

  // Check if a key exists in the map
  bool containsKey = map.contains(20);  // Returns false since key 20 was erased

  return 0;
}

```

# Set

The Set class is a template class representing an ordered container that enforces uniqueness of elements. It is based on a binary search tree and provides efficient insertion, deletion, and search operations. In a `set`, each element can appear only once.

## Class Template Parameters

- `K` - The type of the elements.

## Member Types

- `value_type` - The type of the elements in the set.
- `const_reference` - A reference to a constant element.
- `reference` - A reference to an element.
- `iterator` - An iterator for traversing the elements of the set.
- `size_type` - The type used to represent sizes.

## Constructors

- `set()` - Constructs an empty set.
- `explicit set(std::initializer_list<value_type> const &items)` - Constructs a set with the given set of elements.
- `set(const set &other)` - Copy constructor. Constructs a set by copying another set.
- `set(set &&other)` - Move constructor. Constructs a set by moving the contents of another set.
- `~set()` - Destructor. Destroys the set and frees any dynamically allocated memory.

## Assignment Operator

- `set<K> &operator=(set &&other)` - Move assignment operator. Assigns the contents of another set to this set.

## Iterators

- `iterator begin()` - Returns an iterator pointing to the beginning of the set.
- `iterator end()` - Returns an iterator pointing to the end of the set.
- `iterator cbegin() const` - Returns a const iterator pointing to the beginning of the set.
- `iterator cend() const` - Returns a const iterator pointing to the end of the set.

## Capacity

- `size_type max_size() const` - Returns the maximum number of elements the set can hold.
- `bool empty() const` - Checks if the set is empty.
- `size_type size() const` - Returns the number of elements in the set.

## Modifiers

- `std::pair<iterator, bool> insert(const_reference value)` - Inserts an element into the set. Returns a pair containing an iterator to the inserted element and a boolean indicating whether the insertion was successful (false if the element already exists).
- `void clear()` - Clears all elements in the set, making it empty.
- `void swap(set &other)` - Swaps the contents of two sets.
- `bool contains(const_reference key)` - Checks if the set contains the specified element.
- `void erase(iterator pos)` - Erases the element at the specified position in the set.
- `iterator find(const_reference key)` - Finds an element with the specified key in the set and returns an iterator to it.
- `void merge(const set &other)` - Merges the contents of another set into this set.
- `template <typename... Args> std::pair<iterator, bool> emplace(Args&&... args)` - Constructs and inserts an element into the set.


```cpp
#include "stl_set.h"  // Include the Set class header

int main() {
  // Create a Set with integer elements
  stl::set<int> mySet;

  // Insert elements into the set using insert method
  mySet.insert(10);
  mySet.insert(20);
  mySet.insert(30);  // Inserting a unique element

  // Check if an element is in the set
  bool containsTwenty = mySet.contains(20);  // Returns true

  // Attempt to insert a duplicate element
  std::pair<stl::set<int>::iterator, bool> insertResult = mySet.insert(10);  // Insertion fails, returns false

  // Erase an element by value
  mySet.erase(20);

  // Find an element in the set
  stl::set<int>::iterator findResult = mySet.find(30);  // Returns an iterator pointing to the found element

  // Iterate through the elements in the set
  for (stl::set<int>::iterator it = mySet.begin(); it != mySet.end(); ++it) {
    std::cout << "Element: " << *it << std::endl;
  }

  // Check if the set is empty
  bool isEmpty = mySet.empty();  // Returns false

  // Get the size of the set
  size_t setSize = mySet.size();  // Returns 2 after erasing one element

  // Create another set
  stl::set<int> otherSet;
  otherSet.insert(30);
  otherSet.insert(40);

  // Merge the contents of the other set into this set
  mySet.merge(otherSet);

  // Clear all elements in the set
  mySet.clear();

  return 0;
}

```


# Multiset

The Multiset class is a template class representing an ordered container that allows multiple elements with the same value. It is based on a binary search tree and provides efficient insertion, deletion, and search operations. Unlike the `set` class, which enforces uniqueness of elements, the `multiset` class allows duplicate values.

## Class Template Parameters

- `K` - The type of the elements.

## Member Types

- `value_type` - The type of the elements in the multiset.
- `const_reference` - A reference to a constant element.
- `reference` - A reference to an element.
- `iterator` - An iterator for traversing the elements of the multiset.
- `size_type` - The type used to represent sizes.

## Constructors

- `multiset()` - Constructs an empty multiset.
- `explicit multiset(std::initializer_list<value_type> const &items)` - Constructs a multiset with the given set of elements.
- `explicit multiset(const multiset &other)` - Copy constructor. Constructs a multiset by copying another multiset.
- `multiset(multiset &&other)` - Move constructor. Constructs a multiset by moving the contents of another multiset.
- `~multiset()` - Destructor. Destroys the multiset and frees any dynamically allocated memory.

## Assignment Operator

- `multiset<K> &operator=(multiset &&other)` - Move assignment operator. Assigns the contents of another multiset to this multiset.

## Modifiers

- `iterator insert(const_reference value)` - Inserts an element into the multiset. Unlike `set`, this method allows duplicate elements.
- `size_type count(const_reference key)` - Returns the number of elements with the specified key.
- `std::pair<iterator, iterator> equal_range(const_reference key)` - Returns a range of iterators that represent all the elements with the specified key.
- `iterator lower_bound(const_reference key)` - Returns an iterator pointing to the first element that is not less than the specified key.
- `iterator upper_bound(const_reference key)` - Returns an iterator pointing to the first element that is greater than the specified key.
- `template <typename... Args> std::pair<iterator, bool> emplace(Args&&... args)` - Constructs and inserts an element into the multiset. Unlike `set`, this method allows duplicate elements.

These methods allow you to modify and manipulate the elements in the `multiset`, including inserting elements, counting occurrences, finding equal ranges, and searching for elements greater or equal to a specified key.


```cpp
#include "multiset.h"  // Include the Multiset class header

int main() {
  // Create a Multiset with integer elements
  stl::multiset<int> multiset;

  // Insert elements into the multiset
  multiset.insert(10);
  multiset.insert(20);
  multiset.insert(20);  // Inserting a duplicate element

  // Count the occurrences of an element
  int countTwenty = multiset.count(20);  // Returns 2, as there are two occurrences of 20

  // Find equal ranges for an element
  auto range = multiset.equal_range(20);  // Returns a pair of iterators representing the range of elements with value 20

  // Iterate through the equal range
  for (auto it = range.first; it != range.second; ++it) {
    std::cout << "Element in equal range: " << *it << std::endl;  // Prints both occurrences of 20
  }

  // Find the lower bound for an element
  auto lower = multiset.lower_bound(15);  // Returns an iterator pointing to the first element greater than or equal to 15

  // Find the upper bound for an element
  auto upper = multiset.upper_bound(20);  // Returns an iterator pointing to the first element greater than 20

  // Emplace elements into the multiset
  multiset.emplace(30);
  multiset.emplace(40);
  multiset.emplace(40);  // Emplacing a duplicate element

  // Create another multiset
  stl::multiset<int> otherMultiset;
  otherMultiset.insert(40);
  otherMultiset.insert(50);

  // Merge the contents of the other multiset into this multiset
  multiset.merge(otherMultiset);

  // Erase specific elements by value
  multiset.erase(20);  // Erases both occurrences of 20

  // Clear all elements in the multiset
  multiset.clear();

  // Check if an element exists in the multiset
  bool containsTwenty = multiset.contains(20);  // Returns false since all occurrences of 20 were erased

  return 0;
}

```

# Array

The `array` class is a fixed-size container that encapsulates an array of elements. It provides a simple interface to access and manipulate the elements.

## Template Parameters

- `T` - The type of the elements stored in the array.
- `s` - The size of the array. It must be a compile-time constant.

## Member Types

- `value_type` - The type of the elements stored in the array.
- `reference` - The type of the reference to an element.
- `const_reference` - The type of the constant reference to an element.
- `iterator` - The type of the iterator.
- `const_iterator` - The type of the constant iterator.
- `size_type` - The type for representing the size of the array.

## Methods

- `size_type size() const` - Returns the size of the array.
- `bool empty() const` - Checks if the array is empty.
- `reference at(size_type position) const` - Accesses the element at the specified position in the array.
- `void swap(array& other)` - Swaps the contents of two arrays.
- `void fill(const_reference)` - Fills the array with the specified value.
- `size_type max_size() const` - Returns the maximum number of elements the array can hold.
- `const_reference back()` - Returns a reference to the last element of the array.
- `const_reference front()` - Returns a reference to the first element of the array.
- `iterator data()` - Returns a pointer to the underlying array data.

## Iterators

- `iterator begin()` - Returns an iterator pointing to the first element of the array.
- `iterator end()` - Returns an iterator pointing to the past-the-end element of the array.

## Operators

- `reference operator[](size_type index) const` - Accesses the element at the specified index in the array.
- `array<T, s>& operator=(array&& a)` - Move assignment operator.

## Example Usage

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

# List


The `list` class represents an implementation of a doubly linked list. It includes various methods for working with the list data.

## Type Definitions
- `value_type` - The type of the elements in the list.
- `reference` - A reference to `value_type`.
- `const_reference` - A constant reference to `value_type`.
- `size_type` - An unsigned integral type representing the size of the list.

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

### Constructors and Destructor
- `list()` - Constructs an empty list.
- `explicit list(size_type size)` - Constructs a list with `size` default-inserted elements.
- `explicit list(std::initializer_list<T> const &items)` - Constructs a list with the elements from the initializer list `items`.
- `list(const list &l)` - Constructs a copy of the list `l`.
- `list(list &&l)` - Constructs a list by moving the contents of `l`.
- `list<T> &operator=(list &&l)` - Assigns the contents of the list `l` to the list.
- `~list()` - Destroys the list and frees the memory.

### Iterators
- `iterator begin()` - Returns an iterator to the beginning of the list.
- `iterator end()` - Returns an iterator to the end of the list.
- `const_iterator begin() const` - Returns a constant iterator to the beginning of the list.
- `const_iterator end() const` - Returns a constant iterator to the end of the list.
- `const_iterator cbegin() const` - Returns a constant iterator to the beginning of the list.
- `const_iterator cend() const` - Returns a constant iterator to the end of the list.

### Capacity
- `bool empty() const` - Checks if the list is empty.
- `size_type size() const` - Returns the number of elements in the list.

### Modifiers
- `void clear()` - Removes all elements from the list.
- `iterator insert(iterator pos, const T& value)` - Inserts a new element with the value `value` before the element at the specified position `pos` in the list. Returns an iterator pointing to the inserted element.
- `iterator erase(iterator pos)` - Removes the element at the specified position `pos` in the list. Returns an iterator pointing to the element that followed the erased element.
- `void push_back(const T& value)` - Appends the element `value` to the end of the list.
- `void push_front(const T& value)` - Prepends the element `value` to the beginning of the list.
- `void pop_back()` - Removes the last element from the list.
- `void pop_front()` - Removes the first element from the list.
- `void resize(size_type count)` - Resizes the list to contain `count` elements. If `count` is greater than the current size, additional elements are default-inserted. If `count` is less than the current size, excess elements are removed.
- `void swap(list<T>& other)` - Swaps the contents of the list with the contents of `other`.


### Example Usage

```cpp
    #include <iostream>
#include "st_llist.h"

int main() {
  stl::list<int> mylist;
  
  mylist.push_back(1);
  mylist.push_back(2);
  mylist.push_back(3);
  
  mylist.push_front(0);
  mylist.push_front(-1);
  

  stl::list<int>::iterator it = mylist.begin();
  it++; 
  mylist.insert(it, 10);
  

  it = mylist.begin();
  it++; 
  mylist.erase(it);
  

  for (const auto& value : mylist) {
    std::cout << value << " ";
  }
  std::cout << std::endl;
  
  return 0;
}

```


# Vector

The Vector class is a template class representing a dynamic array. It provides dynamic storage, allowing you to resize and manipulate a sequence of elements efficiently.

## Class Template Parameters

- `T` - The type of elements stored in the vector.

## Member Types

- `value_type` - The type of the elements.
- `reference` - A reference to an element.
- `const_reference` - A constant reference to an element.
- `iterator` - An iterator for traversing the elements.
- `const_iterator` - A constant iterator for traversing the elements.
- `reverse_iterator` - A reverse iterator for traversing the elements in reverse.
- `const_reverse_iterator` - A constant reverse iterator for traversing the elements in reverse.
- `size_type` - The type used to represent sizes.

## Constructor & Destructor

- `vector()` - Constructs an empty vector.
- `explicit vector(size_type size)` - Constructs a vector with the specified initial size.
- `explicit vector(std::initializer_list<value_type> const &items)` - Constructs a vector with the elements from the initializer list.
- `vector(const vector &v)` - Copy constructor. Constructs a vector by copying another vector.
- `vector(vector &&v)` - Move constructor. Constructs a vector by moving the contents of another vector.
- `~vector()` - Destructor. Destroys the vector and frees any dynamically allocated memory.

## Capacity

- `bool empty()` - Checks if the vector is empty.
- `size_type size() const` - Returns the number of elements in the vector.
- `size_type capacity() const` - Returns the current capacity of the vector.
- `size_type max_size() const` - Returns the maximum number of elements the vector can hold.

## Element Access

- `reference at(size_type position) const` - Accesses the element at the specified position with bounds checking.
- `reference operator[](size_t index) const` - Accesses the element at the specified index without bounds checking.
- `reference front()` - Accesses the first element.
- `const_reference front() const` - Accesses the first element (const version).
- `reference back()` - Accesses the last element.
- `const_reference back() const` - Accesses the last element (const version).
- `const_iterator data() const` - Returns a pointer to the underlying array (const version).
- `iterator data()` - Returns a pointer to the underlying array.

## Modifiers

- `void push_back(const_reference value)` - Adds an element to the end of the vector.
- `void pop_back()` - Removes the last element from the vector.
- `void resize(size_type new_size)` - Resizes the vector to the specified size.
- `void reserve(size_type new_size)` - Reserves memory to accommodate at least the specified number of elements.
- `void shrink_to_fit()` - Reduces the capacity to match the size.
- `void clear()` - Removes all elements from the vector.
- `void swap(vector &other)` - Swaps the contents of two vectors.

## Insertion and Erasure

- `iterator insert(iterator position, const_reference value)` - Inserts an element at the specified position.
- `void erase(const_iterator position)` - Erases an element at the specified position.
- `iterator emplace(const_iterator position, Args &&...args)` - Constructs and inserts an element at the specified position.

## Additional Methods

- `void emplace_back(Args &&...args)` - Constructs and adds an element to the end of the vector.
- `void print() const` - Prints the elements of the vector.

## Iterators

- `iterator begin()` - Returns an iterator pointing to the beginning of the vector.
- `iterator end()` - Returns an iterator pointing to the end of the vector.
- `reverse_iterator rbegin()` - Returns a reverse iterator pointing to the last element.
- `reverse_iterator rend()` - Returns a reverse iterator pointing to the element before the first element.
- `const_iterator cbegin() const` - Returns a constant iterator pointing to the beginning of the vector.
- `const_iterator cend() const` - Returns a constant iterator pointing to the end of the vector.

The `vector` class provides dynamic storage and a variety of methods to manipulate the elements efficiently. It allows you to work with sequences of elements similar to arrays but with dynamic resizing capabilities.

## Example Usage

```cpp
#include "vector.h"  // Include the Vector class header

int main() {
  // Create an empty vector of integers
  stl::vector<int> myVector;

  // Check if the vector is empty
  bool isEmpty = myVector.empty();  // Returns true

  // Add elements to the vector using push_back
  myVector.push_back(10);
  myVector.push_back(20);
  myVector.push_back(30);

  // Access elements using subscript operator []
  int element = myVector[1];  // Access the second element (20)

  // Access elements using at with bounds checking
  int firstElement = myVector.at(0);  // Access the first element (10)
  
  // Access the front and back elements
  int frontElement = myVector.front();  // Access the first element (10)
  int backElement = myVector.back();    // Access the last element (30)

  // Get the size and capacity of the vector
  size_t size = myVector.size();        // Returns 3 (number of elements)
  size_t capacity = myVector.capacity();  // Returns the initial capacity (e.g., 4)

  // Resize the vector to a larger size
  myVector.resize(5);

  // Reserve memory for a larger capacity
  myVector.reserve(10);

  // Shrink the capacity to match the size
  myVector.shrink_to_fit();

  // Iterate through the vector using iterators
  for (stl::vector<int>::iterator it = myVector.begin(); it != myVector.end(); ++it) {
    std::cout << "Element: " << *it << std::endl;
  }

  // Insert an element at a specific position
  stl::vector<int>::iterator insertPos = myVector.insert(myVector.begin() + 2, 25);

  // Erase an element at a specific position
  myVector.erase(myVector.begin() + 1);

  // Emplace an element at a specific position
  stl::vector<int>::iterator emplacePos = myVector.emplace(myVector.begin() + 3, 40);

  // Remove the last element from the vector
  myVector.pop_back();

  // Clear all elements from the vector
  myVector.clear();

  // Check if the vector is empty after clearing
  isEmpty = myVector.empty();  // Returns true

  return 0;
}

```