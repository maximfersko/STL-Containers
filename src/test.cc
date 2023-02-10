#include <array>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

#include "gtest/gtest.h"
#include "stl_containers.h"


//########################
//#                     ##
//#  FUNCTION FOR TEST  ##
//#                     ##
//########################

template <typename T>
void printstdVector(const std::vector<T> &A) {
  size_t index = 0;
  for (int i = 0; i < A.size(); i++) {
    std::cout << "orig :" << A[index++] << std::endl;
  }
}

template <typename T>
void printStdList(const std::list<T> &A) {
  std::cout << "============   std list   ===============" << std::endl;
  std::cout << "========================================" << std::endl;
  for (auto it = A.begin(); it != A.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
  std::cout << "size :" << A.size() << std::endl;
  std::cout << "========================================" << std::endl;
}

template <typename T>
bool isEqualVector(const stl::vector<T> &A, const std::vector<T> &B) {
  bool result = true;
  if (A.size() == B.size() && A.capacity() == B.capacity()) {
    for (size_t i = 0; i < A.size(); ++i) {
      if ((A[i] - B[i]) > 1E-7) {
        result = false;
        break;
      }
    }
    if (!result) {
      std::cout << "Fail compare element " << std::endl;
      std::cout << "stl(size) :" << A.size() << std::endl;
      std::cout << "stl(size) :" << B.size() << std::endl;
      std::cout << "stl(capacity) :" << A.capacity() << std::endl;
      std::cout << "stl(capacity) :" << B.capacity() << std::endl;
      A.print();
      printstdVector(B);
    }
  } else {
    std::cout << "Fail compare size or capacity" << std::endl;
    std::cout << "stl(size) :" << A.size() << std::endl;
    std::cout << "stl(size) :" << B.size() << std::endl;
    std::cout << "stl(capacity) :" << A.capacity() << std::endl;
    std::cout << "stl(capacity) :" << B.capacity() << std::endl;
    result = false;
    A.print();
    printstdVector(B);
  }
  return result;
}

template <typename T>
bool isEqualList(const stl::list<T> &A, const std::list<T> &B) {
  bool result = true;
  if (!A.empty() && !B.empty()) {
    typename stl::list<T>::const_iterator stl_it = A.cbegin();
    typename std::list<T>::const_iterator std_it = B.cbegin();
    int count1 = 0, count2 = 0;
    while (stl_it != A.cend() && std_it != B.cend()) {
      if (*stl_it != *std_it) result = false;
      if (!result) break;
      ++stl_it;
      ++std_it;
      ++count1;
      ++count2;
    }
    if (count1 != count2) result = false;
    if (!result) {
      std::cout << "RESULT FAIL !" << std::endl;
      A.print();
      printStdList(B);
    }
  } else {
    result = false;
    std::cout << "CHECK FAIL !" << std::endl;
    A.print();
    printStdList(B);
  }
  return result;
}

template <typename T, size_t s>
bool isEqualArray(const stl::array<T, s> &A, const std::array<T, s> &B) {
  bool result = true;
  if (A.size() == B.size() && !A.empty() && !B.empty()) {
    for (int i = 0; i < A.size(); ++i) {
      if ((A[i] - B[i]) > 1E-7) {
        result = false;
        break;
      }
    }
  } else {
    result = false;
  }
  return result;
}

template <typename T>
bool isEqualSet(const stl::set<T> &A, const std::set<T> &B) {
  bool result = true;
  if (A.size() == B.size()) {
    auto i = A.cbegin();
    auto j = B.cbegin();
    while (i != A.cend() && j != B.cend()) {
      if (*i != *j) result = false;
      if (!result) break;
      ++i;
      ++j;
    }
    if (!result) {
      std::cout << "fail compare!!" << std::endl;
      std::cout << "set stl current: " << *i << std::endl;
      std::cout << "set std current: " << *j << std::endl;
    }
  } else {
    std::cout << "size fail!!!!!!!!!!!" << std::endl;
    std::cout << "size stl:" << A.size() << std::endl;
    std::cout << "size std:" << B.size() << std::endl;
    result = false;
  }
  return result;
}

template <typename T>
bool isEqualMultiSet(const stl::multiset<T> &A, const std::multiset<T> &B) {
  bool result = true;
  if (A.size() == B.size()) {
    auto i = A.cbegin();
    auto j = B.cbegin();
    while (i != A.cend() && j != B.cend()) {
      if (*i != *j) result = false;
      if (!result) break;
      ++i;
      ++j;
    }
    if (!result) std::cout << "fail compare!!";
  } else {
    std::cout << "size fail!!!!!!!!!!!" << std::endl;
    std::cout << "size stl:" << A.size() << std::endl;
    std::cout << "size std:" << B.size() << std::endl;
    result = false;
  }
  return result;
}

template <typename T, typename K>
bool isEqualMap(const stl::map<T, K> &A, const std::map<T, K> &B) {
  bool result = true;
  auto i = A.begin();
  auto j = B.begin();
  while (i != A.end() && j != B.end()) {
    if ((*i).first != (*j).first) result = false;
    if ((*i).second != (*j).second) result = false;
    if (!result) break;
    ++i;
    ++j;
  }
  if (!result) {
    std::cout << "fail compare!!" << std::endl;
    std::cout << "stl current iter first: " << (*i).first << std::endl;
    std::cout << "stl current iter second: " << (*i).second << std::endl;
    std::cout << "std current iter first: " << (*j).first << std::endl;
    std::cout << "std current iter second: " << (*j).second << std::endl;
  }
  return result;
}

//########################
//#                     ##
//#    VECTOR TEST      ##
//#                     ##
//########################

TEST(testVector, initVector1) {
  stl::vector<float> A(2);
  std::vector<float> B(2);
  ASSERT_EQ(isEqualVector(A, B), true);
}

TEST(testVector, bracketsTestVector) {
  stl::vector<std::string> A(2);
  std::vector<std::string> B(2);
  A.push_back("A");
  B.push_back("A");
  ASSERT_EQ(A[2], B[2]);
}

TEST(testVector, copyConstructorVector) {
  stl::vector<int> A(3);
  stl::vector<int> B(A);
  std::vector<int> C(3);
  std::vector<int> D(C);
  ASSERT_EQ(isEqualVector(B, D), true);
}

TEST(testVector, emptyVectorTest) {
  stl::vector<std::string> A(1);
  std::vector<std::string> B(1);
  A.push_back("~");
  B.push_back("0--9");
  A.pop_back();
  B.pop_back();
  ASSERT_EQ(A.empty(), B.empty());
}

TEST(testVector, getSizeVector) {
  stl::vector<std::string> A(2);
  std::vector<std::string> B(2);
  A.push_back("hello");
  B.push_back("world");
  ASSERT_EQ(A.size(), B.size());
}

TEST(testVector, getCapacityVector) {
  stl::vector<int> A(3);
  stl::vector<int> B(3);
  B.push_back(9);
  B.push_back(8);
  A.push_back(9);
  A.push_back(8);
  ASSERT_EQ(A.capacity(), B.capacity());
}

TEST(testVector, pushBackTestVector) {
  stl::vector<int> A(3);
  std::vector<int> B(3);
  A.push_back(2);
  A.push_back(89);
  A.push_back(65);
  B.push_back(2);
  B.push_back(89);
  B.push_back(65);
  ASSERT_EQ(isEqualVector(A, B), true);
}

TEST(testVector, iteratorBeginVector) {
  stl::vector<int> A(1);
  std::vector<int> B(1);
  A.push_back(2);
  A.push_back(3);
  B.push_back(2);
  B.push_back(3);
  ASSERT_EQ(*A.begin(), *B.begin());
}

TEST(testVector, iteratorEndVector) {
  stl::vector<int> A(1);
  std::vector<int> B(1);
  A.push_back(2);
  B.push_back(2);
  ASSERT_EQ(*A.end() - *A.end() - 1, *B.end() - *B.end() - 1);
}

TEST(testVector, cbegin) {
  stl::vector<std::string> o(1);
  std::vector<std::string> p(1);
  o.push_back("9");
  p.push_back("9");
  const stl::vector<std::string> A(o);
  const std::vector<std::string> B(p);
  ASSERT_EQ(*A.cbegin(), *B.cbegin());
}

TEST(testVector, back) {
  stl::vector<float> A(3);
  std::vector<float> B(3);
  A.push_back(99.99f);
  B.push_back(99.99f);
  ASSERT_EQ(A.back(), B.back());
}

TEST(testVector, constBack) {
  stl::vector<float> A(3);
  std::vector<float> B(3);
  A.push_back(99.99f);
  B.push_back(99.99f);
  const stl::vector<float> AB(A);
  const std::vector<float> BA(B);
  ASSERT_EQ(A.back(), B.back());
}

TEST(testVector, resize6) {
  stl::vector<float> A(2);
  std::vector<float> B(2);
  A.resize(10);
  B.resize(10);
  ASSERT_EQ(isEqualVector(A, B), true);
}

TEST(testVector, contructorListVector) {
  stl::vector<float> A{6.7f, 8.1f};
  std::vector<float> B{6.7f, 8.1f};
  ASSERT_EQ(isEqualVector(A, B), true);
}

TEST(testVector, move) {
  stl::vector<std::string> A{"hello", "world", "!"};
  std::vector<std::string> B{"hello", "world", "!"};
  stl::vector<std::string> C = std::move(A);
  std::vector<std::string> D = std::move(B);
  for (int i = 0; i < C.size(); i++) {
    ASSERT_EQ(C[i], D[i]);
  }
}

TEST(testVector, at) {
  stl::vector<int> A{9, 5, 6, 8};
  std::vector<int> B{9, 6, 8, 8};
  ASSERT_EQ(A.at(3), B.at(3));
}

TEST(testVector, resize) {
  stl::vector<int> A{3, 5, 7};
  std::vector<int> B{3, 5, 7};
  A.resize(6);
  B.resize(6);
  ASSERT_EQ(isEqualVector(A, B), true);
}

TEST(testVector, resize2) {
  stl::vector<int> A{3, 9};
  std::vector<int> B{3, 9};
  A.resize(1);
  B.resize(1);
  ASSERT_EQ(isEqualVector(A, B), true);
}

TEST(testVector, resize3) {
  stl::vector<float> A{6.7f, 99.1f, 9.45f};
  std::vector<float> B{6.7f, 99.1f, 9.45f};
  A.resize(3);
  B.resize(3);
  ASSERT_EQ(isEqualVector(A, B), true);
}

TEST(testVector, reserve) {
  stl::vector<int> A{6, 7, 9, 8, 6, 1};
  std::vector<int> B{6, 7, 9, 8, 6, 1};
  A.reserve(10);
  B.reserve(10);
  ASSERT_EQ(isEqualVector(A, B), true);
}

TEST(testVector, front) {
  stl::vector<int> A{3, 8, 7};
  std::vector<int> B{3, 8, 7};
  ASSERT_EQ(A.front(), B.front());
}

TEST(testVector, front2) {
  const stl::vector<int> A{3, 8, 7};
  const std::vector<int> B{3, 8, 7};
  ASSERT_EQ(A.front(), B.front());
}

TEST(testVector, data) {
  stl::vector<int> A{7, 8};
  std::vector<int> B{7, 8};
  ASSERT_EQ(*A.data(), *B.data());
}

TEST(testVector, dataConst) {
  const stl::vector<int> A{2, 2};
  const std::vector<int> B{2, 2};
  ASSERT_EQ(*A.data(), *B.data());
}

TEST(testVector, swap) {
  stl::vector<float> A{3.06f, 2.228f};
  std::vector<float> B{3.06f, 2.228f};
  stl::vector<float> C;
  std::vector<float> D;
  C.swap(A);
  D.swap(B);
  ASSERT_EQ(isEqualVector(C, D), true);
}

TEST(testVector, shrink_to_fit) {
  stl::vector<int> A{2, 2};
  std::vector<int> B{2, 2};
  A.reserve(10);
  B.reserve(10);
  A.shrink_to_fit();
  B.shrink_to_fit();
  ASSERT_EQ(isEqualVector(A, B), true);
}

TEST(testVector, pop) {
  stl::vector<int> A{1, 1, 2};
  std::vector<int> B{1, 1, 2};
  A.pop_back();
  B.pop_back();
  ASSERT_EQ(isEqualVector(A, B), true);
}

TEST(testVector, popWhile) {
  stl::vector<int> A{2, 2, 8, 1, 3, 3, 7};
  std::vector<int> B{2, 2, 8, 1, 3, 3, 7};
  while (A.size() > 0) A.pop_back();
  while (B.size() > 0) B.pop_back();
  ASSERT_EQ(isEqualVector(A, B), true);
}

TEST(testVector, rbegin) {
  stl::vector<int> A{2, 7, 9};
  std::vector<int> B{2, 7, 9};
  stl::vector<int> C(A);
  std::vector<int> D(B);
  size_t index = 0, index1 = 0;
  size_t index2 = 0, index3 = 0;
  bool stlres = false;
  bool stdRes = false;
  for (auto i = A.rbegin(); i != A.rend(); ++i) {
    if (C[index++] == D[index1++]) stlres = true;
    if (!stlres) break;
  }
  for (auto i = B.rbegin(); i != B.rend(); ++i) {
    if (C[index2++] == D[index3++]) stdRes = true;
    if (!stdRes) break;
  }
  ASSERT_EQ(stlres, stdRes);
}

TEST(testVector, erase) {
  stl::vector<int> A{2, 2, 8, 1, 3, 3, 7, 9, 110, 12};
  std::vector<int> B{2, 2, 8, 1, 3, 3, 7, 9, 110, 12};
  for (auto i = A.begin(); i < A.end(); i += 2) A.erase(i);
  for (auto i = B.begin(); i < B.end(); i += 2) B.erase(i);
  ASSERT_EQ(isEqualVector(A, B), true);
}

TEST(testVector, insert) {
  stl::vector<double> A{2.2, 3, 22};
  std::vector<double> B{2.2, 3, 22};
  A.insert(A.end(), 77);
  B.insert(B.end(), 77);
  ASSERT_EQ(isEqualVector(A, B), true);
}

//########################
//#                     ##
//#    ARRAY TEST       ##
//#                     ##
//########################

TEST(arrayTest, defConstructor) {
  stl::array<int, 5> A;
  std::array<int, 5> B;
  ASSERT_EQ(A.size(), B.size());
}

TEST(arrayTest, initList) {
  stl::array<float, 2> A{2.28f, 9.090f};
  std::array<float, 2> B{2.28f, 9.090f};
  ASSERT_EQ(isEqualArray(A, B), true);
}

TEST(arrayTest, copyConstructor) {
  stl::array<int, 4> A{2, 8, 8, 9};
  std::array<int, 4> B{2, 8, 8, 9};
  stl::array<int, 4> C(A);
  std::array<int, 4> D(B);
  ASSERT_EQ(isEqualArray(C, D), true);
}

TEST(arrayTest, moveConstructor) {
  stl::array<int, 2> A{2, 9};
  std::array<int, 2> B{2, 9};
  stl::array<int, 2> C;
  std::array<int, 2> D;
  C = std::move(A);
  D = std::move(B);
  ASSERT_EQ(isEqualArray(C, D), true);
}

TEST(arrayTest, operatorBrackets) {
  stl::array<int, 1> A{99};
  std::array<int, 1> B{99};
  ASSERT_EQ(A[0], B[0]);
}

TEST(arrayTest, at) {
  stl::array<float, 2> A{0.009f, 0.01f};
  std::array<float, 2> B{0.009f, 0.01f};
  ASSERT_EQ(A.at(0), B.at(0));
}

TEST(arrayTest, front) {
  stl::array<int, 2> A{2, 6};
  std::array<int, 2> B{2, 6};
  ASSERT_EQ(A.front(), B.front());
}

TEST(arrayTest, maxSize) {
  stl::array<int, 5> A{2, 6, 90, 9, 1};
  std::array<int, 5> B{2, 6, 9, 1, 3};
  ASSERT_EQ(A.max_size(), B.max_size());
}

TEST(arrayTest, data) {
  stl::array<std::string, 3> A{"fail", "test", "bruh"};
  std::array<std::string, 3> B{"fail", "test", "bruh"};
  ASSERT_EQ(*A.data(), *B.data());
}

TEST(arrayTest, empty) {
  stl::array<std::string, 2> A{"BBC", "U"};
  std::array<int, 1> B{6};
  ASSERT_EQ(A.empty(), B.empty());
}

TEST(arrayTest, size) {
  stl::array<int, 2> A{9, 0};
  std::array<int, 2> B{0, 0};
  ASSERT_EQ(A.size(), B.size());
}

TEST(arrayTest, swap) {
  stl::array<int, 3> A{1, 1, 1};
  std::array<int, 3> B{1, 1, 1};
  stl::array<int, 3> C;
  std::array<int, 3> D;
  C.swap(A);
  D.swap(B);
  ASSERT_EQ(isEqualArray(C, D), true);
}

TEST(arrayTest, fiil) {
  stl::array<int, 2> A;
  std::array<int, 2> B;
  A.fill(2);
  B.fill(2);
  ASSERT_EQ(isEqualArray(A, B), true);
}

TEST(arrayTest, begin) {
  stl::array<double, 2> A{2.8, 8.9};
  std::array<double, 2> B{2.8, 8.9};
  ASSERT_EQ(*A.begin(), *B.begin());
}

TEST(arrayTest, end) {
  stl::array<double, 2> A{2.8, 8.9};
  std::array<double, 2> B{2.8, 8.9};
  ASSERT_EQ(*A.end() - *A.begin() / 2, *B.end() - *B.begin() / 2);
}

TEST(arrayTest, moveConstructorArr) {
  stl::array<int, 2> A{99, 2};
  std::array<int, 2> B{99, 2};
  stl::array<int, 2> C(std::move(A));
  ASSERT_EQ(isEqualArray(C, B), true);
}

//########################
//#                     ##
//#    LIST TEST        ##
//#                     ##
//########################

TEST(listTest, getElmIterator) {
  stl::list<int> A{2, 4, 6, 7};
  std::list<int> B{2, 4, 6, 7};
  ASSERT_EQ(isEqualList(A, B), true);
}

TEST(listTest, operatorMinusMinus) {
  stl::list<int> A{1, 3, 5, 9, 9, 23, 9, 76, 9, 9, 112};
  std::list<int> B{1, 3, 5, 9, 9, 23, 9, 76, 9, 9, 112};
  auto i = A.end();
  auto j = B.end();
  --i;
  --j;
  ASSERT_EQ(*i, *j);
}

TEST(listTest, operatorPlus) {
  stl::list<int> A{5, 7, 1, 1};
  std::list<int> B{5, 7, 1, 1};
  auto i = A.begin();
  auto j = B.begin();
  ++i;
  ++j;
  ASSERT_EQ(*i, *j);
}

TEST(listTest, operatorPlus2) {
  stl::list<int> A{1, 3, 5, 9, 9, 23, 9, 76, 9, 9, 112};
  std::list<int> B{1, 3, 5, 9, 9, 23, 9, 76, 9, 9, 112};
  auto i = A.begin();
  auto j = B.begin();
  for (int a = 0; a < 5; ++a) ++i;
  for (int k = 0; k < 5; ++k) ++j;
  ASSERT_EQ(*i, *j);
}

TEST(listTest, operatorEqual) {
  stl::list<int> A{1, 3, 5, 9, 76, 9, 9, 112};
  std::list<int> B{1, 3, 5, 9, 76, 9, 9, 112};
  auto i = A.begin();
  auto j = B.begin();
  bool result = false;
  if (*j == *i) result = true;
  ASSERT_EQ(result, true);
  result = false;
  for (int k = 0; k < 3; k++) {
    if (*i == *j) result = true;
    ++i;
    ++j;
  }
  ASSERT_EQ(result, true);
}

TEST(listTest, sort) {
  stl::list<int> A{1, 3, 5, 9, 9, 23, 9, 76, 9, 9, 112};
  std::list<int> B{1, 3, 5, 9, 9, 23, 9, 76, 9, 9, 112};
  A.sort();
  B.sort();
  ASSERT_EQ(isEqualList(A, B), true);
}

TEST(listTest, sort2) {
  stl::list<int> A{2, 3, 1, 4, 3, 8, 9, 7, 8, 1, 0, 9};
  std::list<int> B{2, 3, 1, 4, 3, 8, 9, 7, 8, 1, 0, 9};
  A.sort();
  B.sort();
  ASSERT_EQ(isEqualList(A, B), true);
}

TEST(listTest, sort3) {
  stl::list<int> A{289, 3,  1,  455, 3, 80,  94323, 7,  8,  17,
                   0,   99, 34, 1,   0, 454, 56,    78, 54, 34};
  std::list<int> B{289, 3,  1,  455, 3, 80,  94323, 7,  8,  17,
                   0,   99, 34, 1,   0, 454, 56,    78, 54, 34};
  A.sort();
  B.sort();
  ASSERT_EQ(isEqualList(A, B), true);
}

TEST(listTest, sort4) {
  stl::list<int> A{8,   2,   6,  8,  7878,  9,  1, 99, -9, 8,  5,  289, 3,
                   1,   455, 3,  80, 94323, 7,  8, 17, 0,  99, 34, 1,   0,
                   454, 56,  78, 54, 34,    34, 1, 67, 4,  4,  1,  9,   8};
  std::list<int> B{8,   2,   6,  8,  7878,  9,  1, 99, -9, 8,  5,  289, 3,
                   1,   455, 3,  80, 94323, 7,  8, 17, 0,  99, 34, 1,   0,
                   454, 56,  78, 54, 34,    34, 1, 67, 4,  4,  1,  9,   8};
  A.sort();
  B.sort();
  ASSERT_EQ(isEqualList(A, B), true);
}

TEST(listTest, sort5) {
  stl::list<int> A{2,  3,     1,  4, 3,  8,  9,  7,   8,   1,   0,   9,   1,
                   3,  5,     9,  9, 23, 9,  76, 9,   9,   112, 8,   2,   6,
                   8,  7878,  9,  1, 99, -9, 8,  5,   289, 3,   1,   455, 3,
                   80, 94323, 7,  8, 17, 0,  99, 34,  1,   0,   454, 56,  78,
                   54, 34,    34, 1, 67, 4,  4,  1,   9,   8,   1,   3,   5,
                   9,  9,     23, 9, 76, 9,  9,  112, 2,   3,   1,   4,   3,
                   8,  9,     7,  8, 1,  0,  9};
  std::list<int> B{2,  3,     1,  4, 3,  8,  9,  7,   8,   1,   0,   9,   1,
                   3,  5,     9,  9, 23, 9,  76, 9,   9,   112, 8,   2,   6,
                   8,  7878,  9,  1, 99, -9, 8,  5,   289, 3,   1,   455, 3,
                   80, 94323, 7,  8, 17, 0,  99, 34,  1,   0,   454, 56,  78,
                   54, 34,    34, 1, 67, 4,  4,  1,   9,   8,   1,   3,   5,
                   9,  9,     23, 9, 76, 9,  9,  112, 2,   3,   1,   4,   3,
                   8,  9,     7,  8, 1,  0,  9};
  A.sort();
  B.sort();
  ASSERT_EQ(isEqualList(A, B), true);
}

TEST(listTest, sort6) {
  stl::list<int> A{
      -9,    5,  4,  -88, -1, 0, 1,   7,  8,    4,    90, -245, -113,  8,  89,
      -8787, 1,  2,  3,   1,  4, 3,   8,  9,    7,    8,  1,    0,     9,  1,
      3,     5,  9,  9,   23, 9, 76,  9,  9,    112,  8,  2,    6,     8,  7878,
      9,     1,  99, -9,  8,  5, 289, 3,  1,    455,  3,  80,   94323, 7,  8,
      17,    0,  99, 34,  1,  0, 454, 56, 78,   54,   34, 34,   1,     67, 4,
      4,     1,  9,  8,   1,  3, 5,   9,  9,    23,   9,  76,   9,     9,  112,
      2,     3,  1,  4,   3,  8, 9,   7,  8,    1,    0,  9,    -9,    5,  4,
      -88,   -1, 0,  1,   7,  8, 4,   90, -245, -113, 8,  89,   -8787, 1};
  std::list<int> B{
      -9,    5,  4,  -88, -1, 0, 1,   7,  8,    4,    90, -245, -113,  8,  89,
      -8787, 1,  2,  3,   1,  4, 3,   8,  9,    7,    8,  1,    0,     9,  1,
      3,     5,  9,  9,   23, 9, 76,  9,  9,    112,  8,  2,    6,     8,  7878,
      9,     1,  99, -9,  8,  5, 289, 3,  1,    455,  3,  80,   94323, 7,  8,
      17,    0,  99, 34,  1,  0, 454, 56, 78,   54,   34, 34,   1,     67, 4,
      4,     1,  9,  8,   1,  3, 5,   9,  9,    23,   9,  76,   9,     9,  112,
      2,     3,  1,  4,   3,  8, 9,   7,  8,    1,    0,  9,    -9,    5,  4,
      -88,   -1, 0,  1,   7,  8, 4,   90, -245, -113, 8,  89,   -8787, 1};
  A.sort();
  B.sort();
  ASSERT_EQ(isEqualList(A, B), true);
}

TEST(listTest, sort8) {
  stl::list<int> A{
      -9,    5,     4,     -88,   -1,    0,     1,     7,     8,     4,
      90,    -245,  -113,  8,     89,    -8787, 1,     2,     3,     1,
      4,     3,     8,     9,     7,     8,     1,     0,     9,     1,
      3,     5,     9,     9,     23,    9,     76,    9,     9,     112,
      8,     2,     6,     8,     7878,  9,     1,     99,    -9,    8,
      5,     289,   3,     1,     455,   3,     80,    94323, 7,     8,
      17,    0,     99,    34,    1,     0,     454,   56,    78,    54,
      34,    34,    1,     67,    4,     4,     1,     9,     8,     1,
      3,     5,     9,     9,     23,    9,     76,    9,     9,     112,
      2,     3,     1,     4,     3,     8,     9,     7,     8,     1,
      0,     9,     -9,    5,     4,     -88,   -1,    0,     1,     7,
      8,     4,     90,    -245,  -113,  8,     89,    -8787, 1,     -9,
      5,     4,     -88,   -1,    0,     1,     7,     8,     4,     90,
      -245,  -113,  8,     89,    -8787, 1,     2,     3,     1,     4,
      3,     8,     9,     7,     8,     1,     0,     9,     1,     3,
      5,     9,     9,     23,    9,     76,    9,     9,     112,   8,
      2,     6,     8,     7878,  9,     1,     99,    -9,    8,     5,
      289,   3,     1,     455,   3,     80,    94323, 7,     8,     17,
      0,     99,    34,    1,     0,     454,   56,    78,    54,    34,
      34,    1,     67,    4,     4,     1,     9,     8,     1,     3,
      5,     9,     9,     23,    9,     76,    9,     9,     112,   2,
      3,     1,     4,     3,     8,     9,     7,     8,     1,     0,
      9,     -9,    5,     4,     -88,   -1,    0,     1,     7,     8,
      4,     90,    -245,  -113,  8,     89,    -8787, 1 - 9, 5,     4,
      -88,   -1,    0,     1,     7,     8,     4,     90,    -245,  -113,
      8,     89,    -8787, 1,     2,     3,     1,     4,     3,     8,
      9,     7,     8,     1,     0,     9,     1,     3,     5,     9,
      9,     23,    9,     76,    9,     9,     112,   8,     2,     6,
      8,     7878,  9,     1,     99,    -9,    8,     5,     289,   3,
      1,     455,   3,     80,    94323, 7,     8,     17,    0,     99,
      34,    1,     0,     454,   56,    78,    54,    34,    34,    1,
      67,    4,     4,     1,     9,     8,     1,     3,     5,     9,
      9,     23,    9,     76,    9,     9,     112,   2,     3,     1,
      4,     3,     8,     9,     7,     8,     1,     0,     9,     -9,
      5,     4,     -88,   -1,    0,     1,     7,     8,     4,     90,
      -245,  -113,  8,     89,    -8787, 1,     -9,    5,     4,     -88,
      -1,    0,     1,     7,     8,     4,     90,    -245,  -113,  8,
      89,    -8787, 1,     2,     3,     1,     4,     3,     8,     9,
      7,     8,     1,     0,     9,     1,     3,     5,     9,     9,
      23,    9,     76,    9,     9,     112,   8,     2,     6,     8,
      7878,  9,     1,     99,    -9,    8,     5,     289,   3,     1,
      455,   3,     80,    94323, 7,     8,     17,    0,     99,    34,
      1,     0,     454,   56,    78,    54,    34,    34,    1,     67,
      4,     4,     1,     9,     8,     1,     3,     5,     9,     9,
      23,    9,     76,    9,     9,     112,   2,     3,     1,     4,
      3,     8,     9,     7,     8,     1,     0,     9,     -9,    5,
      4,     -88,   -1,    0,     1,     7,     8,     4,     90,    -245,
      -113,  8,     89,    -8787, 1,     -9,    5,     4,     -88,   -1,
      0,     1,     7,     8,     4,     90,    -245,  -113,  8,     89,
      -8787, 1,     2,     3,     1,     4,     3,     8,     9,     7,
      8,     1,     0,     9,     1,     3,     5,     9,     9,     23,
      9,     76,    9,     9,     112,   8,     2,     6,     8,     7878,
      9,     1,     99,    -9,    8,     5,     289,   3,     1,     455,
      3,     80,    94323, 7,     8,     17,    0,     99,    34,    1,
      0,     454,   56,    78,    54,    34,    34,    1,     67,    4,
      4,     1,     9,     8,     1,     3,     5,     9,     9,     23,
      9,     76,    9,     9,     112,   2,     3,     1,     4,     3,
      8,     9,     7,     8,     1,     0,     9,     -9,    5,     4,
      -88,   -1,    0,     1,     7,     8,     4,     90,    -245,  -113,
      8,     89,    -8787, 1 - 9, 5,     4,     -88,   -1,    0,     1,
      7,     8,     4,     90,    -245,  -113,  8,     89,    -8787, 1,
      2,     3,     1,     4,     3,     8,     9,     7,     8,     1,
      0,     9,     1,     3,     5,     9,     9,     23,    9,     76,
      9,     9,     112,   8,     2,     6,     8,     7878,  9,     1,
      99,    -9,    8,     5,     289,   3,     1,     455,   3,     80,
      94323, 7,     8,     17,    0,     99,    34,    1,     0,     454,
      56,    78,    54,    34,    34,    1,     67,    4,     4,     1,
      9,     8,     1,     3,     5,     9,     9,     23,    9,     76,
      9,     9,     112,   2,     3,     1,     4,     3,     8,     9,
      7,     8,     1,     0,     9,     -9,    5,     4,     -88,   -1,
      0,     1,     7,     8,     4,     90,    -245,  -113,  8,     89,
      -8787, 1};
  std::list<int> B{
      -9,    5,     4,     -88,   -1,    0,     1,     7,     8,     4,
      90,    -245,  -113,  8,     89,    -8787, 1,     2,     3,     1,
      4,     3,     8,     9,     7,     8,     1,     0,     9,     1,
      3,     5,     9,     9,     23,    9,     76,    9,     9,     112,
      8,     2,     6,     8,     7878,  9,     1,     99,    -9,    8,
      5,     289,   3,     1,     455,   3,     80,    94323, 7,     8,
      17,    0,     99,    34,    1,     0,     454,   56,    78,    54,
      34,    34,    1,     67,    4,     4,     1,     9,     8,     1,
      3,     5,     9,     9,     23,    9,     76,    9,     9,     112,
      2,     3,     1,     4,     3,     8,     9,     7,     8,     1,
      0,     9,     -9,    5,     4,     -88,   -1,    0,     1,     7,
      8,     4,     90,    -245,  -113,  8,     89,    -8787, 1,     -9,
      5,     4,     -88,   -1,    0,     1,     7,     8,     4,     90,
      -245,  -113,  8,     89,    -8787, 1,     2,     3,     1,     4,
      3,     8,     9,     7,     8,     1,     0,     9,     1,     3,
      5,     9,     9,     23,    9,     76,    9,     9,     112,   8,
      2,     6,     8,     7878,  9,     1,     99,    -9,    8,     5,
      289,   3,     1,     455,   3,     80,    94323, 7,     8,     17,
      0,     99,    34,    1,     0,     454,   56,    78,    54,    34,
      34,    1,     67,    4,     4,     1,     9,     8,     1,     3,
      5,     9,     9,     23,    9,     76,    9,     9,     112,   2,
      3,     1,     4,     3,     8,     9,     7,     8,     1,     0,
      9,     -9,    5,     4,     -88,   -1,    0,     1,     7,     8,
      4,     90,    -245,  -113,  8,     89,    -8787, 1 - 9, 5,     4,
      -88,   -1,    0,     1,     7,     8,     4,     90,    -245,  -113,
      8,     89,    -8787, 1,     2,     3,     1,     4,     3,     8,
      9,     7,     8,     1,     0,     9,     1,     3,     5,     9,
      9,     23,    9,     76,    9,     9,     112,   8,     2,     6,
      8,     7878,  9,     1,     99,    -9,    8,     5,     289,   3,
      1,     455,   3,     80,    94323, 7,     8,     17,    0,     99,
      34,    1,     0,     454,   56,    78,    54,    34,    34,    1,
      67,    4,     4,     1,     9,     8,     1,     3,     5,     9,
      9,     23,    9,     76,    9,     9,     112,   2,     3,     1,
      4,     3,     8,     9,     7,     8,     1,     0,     9,     -9,
      5,     4,     -88,   -1,    0,     1,     7,     8,     4,     90,
      -245,  -113,  8,     89,    -8787, 1,     -9,    5,     4,     -88,
      -1,    0,     1,     7,     8,     4,     90,    -245,  -113,  8,
      89,    -8787, 1,     2,     3,     1,     4,     3,     8,     9,
      7,     8,     1,     0,     9,     1,     3,     5,     9,     9,
      23,    9,     76,    9,     9,     112,   8,     2,     6,     8,
      7878,  9,     1,     99,    -9,    8,     5,     289,   3,     1,
      455,   3,     80,    94323, 7,     8,     17,    0,     99,    34,
      1,     0,     454,   56,    78,    54,    34,    34,    1,     67,
      4,     4,     1,     9,     8,     1,     3,     5,     9,     9,
      23,    9,     76,    9,     9,     112,   2,     3,     1,     4,
      3,     8,     9,     7,     8,     1,     0,     9,     -9,    5,
      4,     -88,   -1,    0,     1,     7,     8,     4,     90,    -245,
      -113,  8,     89,    -8787, 1,     -9,    5,     4,     -88,   -1,
      0,     1,     7,     8,     4,     90,    -245,  -113,  8,     89,
      -8787, 1,     2,     3,     1,     4,     3,     8,     9,     7,
      8,     1,     0,     9,     1,     3,     5,     9,     9,     23,
      9,     76,    9,     9,     112,   8,     2,     6,     8,     7878,
      9,     1,     99,    -9,    8,     5,     289,   3,     1,     455,
      3,     80,    94323, 7,     8,     17,    0,     99,    34,    1,
      0,     454,   56,    78,    54,    34,    34,    1,     67,    4,
      4,     1,     9,     8,     1,     3,     5,     9,     9,     23,
      9,     76,    9,     9,     112,   2,     3,     1,     4,     3,
      8,     9,     7,     8,     1,     0,     9,     -9,    5,     4,
      -88,   -1,    0,     1,     7,     8,     4,     90,    -245,  -113,
      8,     89,    -8787, 1 - 9, 5,     4,     -88,   -1,    0,     1,
      7,     8,     4,     90,    -245,  -113,  8,     89,    -8787, 1,
      2,     3,     1,     4,     3,     8,     9,     7,     8,     1,
      0,     9,     1,     3,     5,     9,     9,     23,    9,     76,
      9,     9,     112,   8,     2,     6,     8,     7878,  9,     1,
      99,    -9,    8,     5,     289,   3,     1,     455,   3,     80,
      94323, 7,     8,     17,    0,     99,    34,    1,     0,     454,
      56,    78,    54,    34,    34,    1,     67,    4,     4,     1,
      9,     8,     1,     3,     5,     9,     9,     23,    9,     76,
      9,     9,     112,   2,     3,     1,     4,     3,     8,     9,
      7,     8,     1,     0,     9,     -9,    5,     4,     -88,   -1,
      0,     1,     7,     8,     4,     90,    -245,  -113,  8,     89,
      -8787, 1};
  A.sort();
  B.sort();
  ASSERT_EQ(isEqualList(A, B), true);
}

TEST(listTest, sort7) {
  stl::list<int> A{
      -9,    5,    4,     -88,  -1,    0,     1,     7,     8,     4,    90,
      -245,  -113, 8,     89,   -8787, 1,     2,     3,     1,     4,    3,
      8,     9,    7,     8,    1,     0,     9,     1,     3,     5,    9,
      9,     23,   9,     76,   9,     9,     112,   8,     2,     6,    8,
      7878,  9,    1,     99,   -9,    8,     5,     289,   3,     1,    455,
      3,     80,   94323, 7,    8,     17,    0,     99,    34,    1,    0,
      454,   56,   78,    54,   34,    34,    1,     67,    4,     4,    1,
      9,     8,    1,     3,    5,     9,     9,     23,    9,     76,   9,
      9,     112,  2,     3,    1,     4,     3,     8,     9,     7,    8,
      1,     0,    9,     -9,   5,     4,     -88,   -1,    0,     1,    7,
      8,     4,    90,    -245, -113,  8,     89,    -8787, 1,     -9,   5,
      4,     -88,  -1,    0,    1,     7,     8,     4,     90,    -245, -113,
      8,     89,   -8787, 1,    2,     3,     1,     4,     3,     8,    9,
      7,     8,    1,     0,    9,     1,     3,     5,     9,     9,    23,
      9,     76,   9,     9,    112,   8,     2,     6,     8,     7878, 9,
      1,     99,   -9,    8,    5,     289,   3,     1,     455,   3,    80,
      94323, 7,    8,     17,   0,     99,    34,    1,     0,     454,  56,
      78,    54,   34,    34,   1,     67,    4,     4,     1,     9,    8,
      1,     3,    5,     9,    9,     23,    9,     76,    9,     9,    112,
      2,     3,    1,     4,    3,     8,     9,     7,     8,     1,    0,
      9,     -9,   5,     4,    -88,   -1,    0,     1,     7,     8,    4,
      90,    -245, -113,  8,    89,    -8787, 1 - 9, 5,     4,     -88,  -1,
      0,     1,    7,     8,    4,     90,    -245,  -113,  8,     89,   -8787,
      1,     2,    3,     1,    4,     3,     8,     9,     7,     8,    1,
      0,     9,    1,     3,    5,     9,     9,     23,    9,     76,   9,
      9,     112,  8,     2,    6,     8,     7878,  9,     1,     99,   -9,
      8,     5,    289,   3,    1,     455,   3,     80,    94323, 7,    8,
      17,    0,    99,    34,   1,     0,     454,   56,    78,    54,   34,
      34,    1,    67,    4,    4,     1,     9,     8,     1,     3,    5,
      9,     9,    23,    9,    76,    9,     9,     112,   2,     3,    1,
      4,     3,    8,     9,    7,     8,     1,     0,     9,     -9,   5,
      4,     -88,  -1,    0,    1,     7,     8,     4,     90,    -245, -113,
      8,     89,   -8787, 1};
  std::list<int> B{
      -9,    5,    4,     -88,  -1,    0,     1,     7,     8,     4,    90,
      -245,  -113, 8,     89,   -8787, 1,     2,     3,     1,     4,    3,
      8,     9,    7,     8,    1,     0,     9,     1,     3,     5,    9,
      9,     23,   9,     76,   9,     9,     112,   8,     2,     6,    8,
      7878,  9,    1,     99,   -9,    8,     5,     289,   3,     1,    455,
      3,     80,   94323, 7,    8,     17,    0,     99,    34,    1,    0,
      454,   56,   78,    54,   34,    34,    1,     67,    4,     4,    1,
      9,     8,    1,     3,    5,     9,     9,     23,    9,     76,   9,
      9,     112,  2,     3,    1,     4,     3,     8,     9,     7,    8,
      1,     0,    9,     -9,   5,     4,     -88,   -1,    0,     1,    7,
      8,     4,    90,    -245, -113,  8,     89,    -8787, 1,     -9,   5,
      4,     -88,  -1,    0,    1,     7,     8,     4,     90,    -245, -113,
      8,     89,   -8787, 1,    2,     3,     1,     4,     3,     8,    9,
      7,     8,    1,     0,    9,     1,     3,     5,     9,     9,    23,
      9,     76,   9,     9,    112,   8,     2,     6,     8,     7878, 9,
      1,     99,   -9,    8,    5,     289,   3,     1,     455,   3,    80,
      94323, 7,    8,     17,   0,     99,    34,    1,     0,     454,  56,
      78,    54,   34,    34,   1,     67,    4,     4,     1,     9,    8,
      1,     3,    5,     9,    9,     23,    9,     76,    9,     9,    112,
      2,     3,    1,     4,    3,     8,     9,     7,     8,     1,    0,
      9,     -9,   5,     4,    -88,   -1,    0,     1,     7,     8,    4,
      90,    -245, -113,  8,    89,    -8787, 1 - 9, 5,     4,     -88,  -1,
      0,     1,    7,     8,    4,     90,    -245,  -113,  8,     89,   -8787,
      1,     2,    3,     1,    4,     3,     8,     9,     7,     8,    1,
      0,     9,    1,     3,    5,     9,     9,     23,    9,     76,   9,
      9,     112,  8,     2,    6,     8,     7878,  9,     1,     99,   -9,
      8,     5,    289,   3,    1,     455,   3,     80,    94323, 7,    8,
      17,    0,    99,    34,   1,     0,     454,   56,    78,    54,   34,
      34,    1,    67,    4,    4,     1,     9,     8,     1,     3,    5,
      9,     9,    23,    9,    76,    9,     9,     112,   2,     3,    1,
      4,     3,    8,     9,    7,     8,     1,     0,     9,     -9,   5,
      4,     -88,  -1,    0,    1,     7,     8,     4,     90,    -245, -113,
      8,     89,   -8787, 1};
  A.sort();
  B.sort();
  ASSERT_EQ(isEqualList(A, B), true);
}

TEST(listTest, operatorNotEqual) {
  stl::list<int> A{1, 3, 5, 9, 76, 9, 9, 112};
  std::list<int> B{2, 4, 8, 0, 6, 1, 2, 11};
  auto i = A.begin();
  auto j = B.begin();
  bool result = false;
  if (*j != *i) result = true;
  ASSERT_EQ(result, true);
  result = false;
  for (int k = 0; k < 3; k++) {
    if (*i != *j) result = true;
    ++i;
    ++j;
  }
  ASSERT_EQ(result, true);
}

TEST(listTest, begin) {
  stl::list<int> A{2, 4, 6, 7};
  std::list<int> B{2, 4, 6, 7};
  ASSERT_EQ(*A.begin(), *B.begin());
}

TEST(listTest, end2) {
  stl::list<int> A{2, 4, 6, 7};
  std::list<int> B{2, 4, 6, 7};
  ASSERT_EQ(*--A.end(), *--B.end());
}

TEST(listTest, cbegin) {
  const stl::list<int> A{2, 4, 6, 7};
  const std::list<int> B{2, 4, 6, 7};
  ASSERT_EQ(*A.cbegin(), *B.cbegin());
}

TEST(listTest, end) {
  const stl::list<int> A{2, 4, 6, 7};
  const std::list<int> B{2, 4, 6, 7};
  ASSERT_EQ(*--A.cend(), *--B.cend());
}

TEST(listTest, front) {
  const stl::list<int> A{2, 4, 6, 7};
  const std::list<int> B{2, 4, 6, 7};
  ASSERT_EQ(A.front(), B.front());
}

TEST(listTest, back) {
  const stl::list<int> A{2, 4, 6, 7};
  const std::list<int> B{2, 4, 6, 7};
  ASSERT_EQ(A.back(), B.back());
}

TEST(listTest, copyConstructor) {
  stl::list<int> A{2, 4, 6, 7};
  std::list<int> B{2, 4, 6, 7};
  stl::list<int> C(A);
  std::list<int> D(B);
  ASSERT_EQ(isEqualList(C, D), true);
}

TEST(listTest, moveConstructor) {
  stl::list<int> A{100, 7, 9, 999};
  stl::list<int> B(std::move(A));
  std::list<int> C{100, 7, 9, 999};
  ASSERT_EQ(isEqualList(B, C), true);
}

TEST(listTest, moveConstructorString) {
  stl::list<int> A{2, 3, 6};
  std::list<int> B{2, 3, 6};
  stl::list<int> C(std::move(A));
  ASSERT_EQ(isEqualList(C, B), true);
}

TEST(listTest, moveOperator) {
  stl::list<float> A{2.34f, 455.98f, 1.0f};
  std::list<float> B{2.34f, 455.98f, 1.0f};
  stl::list<float> C;
  C = std::move(A);
  ASSERT_EQ(isEqualList(C, B), true);
}

TEST(listTest, empty) {
  stl::list<int> A{2, 2};
  std::list<int> B{9, 8};
  bool result = false;
  A.pop_back();
  B.pop_back();
  if (!A.empty() && !B.empty()) result = true;
  ASSERT_TRUE(result);
  result = false;
  stl::list<int> C{};
  std::list<int> D{};
  if (C.empty() && D.empty()) result = true;
  ASSERT_TRUE(result);
}

TEST(listTest, size) {
  stl::list<int> A{};
  std::list<int> B{};
  ASSERT_EQ(A.size(), B.size());
  stl::list<int> C{3, 7, 8, 5, 1, 1};
  std::list<int> D{3, 7, 8, 5, 1, 1};
  ASSERT_EQ(A.size(), B.size());
}

TEST(listTest, insert) {
  stl::list<int> A{2, 3, 1, 4, 3, 8, 9};
  std::list<int> B{2, 3, 1, 4, 3, 8, 9};
  auto i = A.begin();
  auto j = B.begin();
  ++j;
  ++i;
  A.insert(i, 999);
  B.insert(j, 999);
  ASSERT_EQ(isEqualList(A, B), true);
  --j;
  --i;
  A.insert(i, 0);
  B.insert(j, 0);
  for (int x = 0; x < 4; ++x) {
    ++i;
    ++j;
  }
  A.insert(i, 100000);
  B.insert(j, 100000);
  ASSERT_EQ(isEqualList(A, B), true);
  for (int x = 0; x < 1; ++x) {
    ++i;
    ++j;
  }
  A.insert(i, 1337);
  B.insert(j, 1337);
  ASSERT_EQ(isEqualList(A, B), true);
}

TEST(listTest, insert2) {
  stl::list<int> A{2, 3, 1, 4, 3, 8, 9};
  std::list<int> B{2, 3, 1, 4, 3, 8, 9};
  auto i = A.begin();
  auto j = B.begin();
  A.insert(i, 1337);
  B.insert(j, 1337);
  ASSERT_EQ(isEqualList(A, B), true);
}

TEST(listTest, insert3) {
  stl::list<int> A;
  std::list<int> B;
  auto i = A.begin();
  auto j = B.begin();
  A.insert(i, 1337);
  B.insert(j, 1337);
  ASSERT_EQ(isEqualList(A, B), true);
}

TEST(listTest, insert4) {
  stl::list<int> A{2, 3, 1, 4, 3, 8, 9, 7, 8, 1, 0, 9};
  std::list<int> B{2, 3, 1, 4, 3, 8, 9, 7, 8, 1, 0, 9};
  auto i = --A.end();
  auto j = B.end();
  A.insert(i, 1337);
  B.insert(j, 1337);
  ASSERT_EQ(isEqualList(A, B), true);
}

TEST(listTest, erase) {
  stl::list<int> A{2, 3, 1, 4, 3, 8, 9, 7, 8, 1, 0, 9};
  std::list<int> B{2, 3, 1, 4, 3, 8, 9, 7, 8, 1, 0, 9};
  auto i = A.end();
  auto j = B.end();
  auto k = A.begin();
  auto h = B.begin();
  --i;
  --j;
  A.erase(i);
  B.erase(j);
  ASSERT_EQ(isEqualList(A, B), true);
}

TEST(listTest, erase2) {
  stl::list<int> A{2, 3, 1, 4, 3, 8, 9, 7, 8, 1, 0, 9};
  std::list<int> B{2, 3, 1, 4, 3, 8, 9, 7, 8, 1, 0, 9};
  auto i = A.begin();
  auto j = B.begin();
  A.erase(i);
  B.erase(j);
  ASSERT_EQ(isEqualList(A, B), true);
}

TEST(listTest, erase3) {
  stl::list<int> A{2, 3, 1, 4, 3, 8, 9, 7, 8, 1, 0, 9};
  std::list<int> B{2, 3, 1, 4, 3, 8, 9, 7, 8, 1, 0, 9};
  auto i = A.begin();
  auto j = B.begin();
  ++i;
  ++j;
  ++i;
  ++j;
  ++i;
  ++j;
  ++i;
  ++j;
  A.erase(i);
  B.erase(j);
  ASSERT_EQ(isEqualList(A, B), true);
}

TEST(listTest, unique) {
  stl::list<int> A{2, 3, 1, 4, 3, 8, 9, 7, 8, 1, 0, 9, 1, 2};
  std::list<int> B{2, 3, 1, 4, 3, 8, 9, 7, 8, 1, 0, 9, 1, 2};
  A.unique();
  B.unique();
  ASSERT_EQ(isEqualList(A, B), true);
}

TEST(listTest, unique2) {
  stl::list<int> A{1, 1, 1, 1};
  std::list<int> B{1, 1, 1, 1};
  A.unique();
  B.unique();
  ASSERT_EQ(isEqualList(A, B), true);
}

TEST(listTest, push_back) {
  stl::list<int> A{2, 2};
  std::list<int> B{2, 2};
  A.push_back(23);
  B.push_back(23);
  ASSERT_EQ(isEqualList(A, B), true);
  stl::list<int> C{};
  std::list<int> D{};
  C.push_back(1);
  D.push_back(1);
  ASSERT_EQ(isEqualList(C, D), true);
}

TEST(listTest, pop_back) {
  stl::list<float> A{2.2f, 1.1f};
  std::list<float> B{2.2f, 1.1f};
  A.pop_back();
  B.pop_back();
  ASSERT_EQ(isEqualList(A, B), true);
}

TEST(listTest, pushFront) {
  stl::list<int> A{0};
  std::list<int> B{0};
  A.push_front(228);
  B.push_front(228);
  ASSERT_EQ(isEqualList(A, B), true);
  stl::list<int> C{};
  std::list<int> D{};
  C.push_front(11212);
  D.push_front(11212);
  ASSERT_EQ(isEqualList(C, D), true);
}

TEST(listTest, pop_front) {
  stl::list<float> A{2.2f, 1.1f};
  std::list<float> B{2.2f, 1.1f};
  A.pop_front();
  B.pop_front();
  ASSERT_EQ(isEqualList(A, B), true);
}

TEST(listTest, swap) {
  stl::list<int> A{2, 6, 7, 8, 1, 0, 223};
  std::list<int> B{2, 6, 7, 8, 1, 0, 223};
  stl::list<int> C{7, 9};
  std::list<int> D{7, 9};
  A.swap(C);
  B.swap(D);
  ASSERT_EQ(isEqualList(A, B), true);
  ASSERT_EQ(isEqualList(C, D), true);
}

TEST(testList, reverse) {
  stl::list<int> C{2, 3, 1, 4, 3, 8, 9, 7, 8, 1, 0, 9};
  std::list<int> D{2, 3, 1, 4, 3, 8, 9, 7, 8, 1, 0, 9};
  C.reverse();
  D.reverse();
  ASSERT_EQ(isEqualList(C, D), true);
}

TEST(testList, constructorNull) {
  stl::list<int> A(6);
  std::list<int> B{0, 0, 0, 0, 0, 0};
  ASSERT_EQ(isEqualList(A, B), true);
}

TEST(listTest, minusminusoperator) {
  stl::list<int> A{2, 6, 7, 8, 1, 0, 223};
  std::list<int> B{2, 6, 7, 8, 1, 0, 223};
  auto i = --A.end();
  auto j = --B.end();
  for (; i != A.begin() && j != B.begin(); --i, --j) {
    ASSERT_EQ(*i, *j);
  }
}

TEST(listTest, clear) {
  stl::list<int> A{2, 6, 7, 8, 1, 0, 223};
  std::list<int> B{2, 6, 7, 8, 1, 0, 223};
  A.clear();
  B.clear();
  ASSERT_EQ(A.empty(), B.empty());
}

TEST(listTest, clear2) {
  stl::list<int> A{};
  std::list<int> B{};
  A.clear();
  B.clear();
  ASSERT_EQ(A.empty(), B.empty());
}

TEST(listTest, emplace_back) {
  stl::list<int> A{2, 6, 7, 8, 1, 0, 223};
  std::list<int> B{2, 6, 7, 8, 1, 0, 223, 7, 8, 8};
  A.emplace_back(7, 8, 8);
  ASSERT_EQ(isEqualList(A, B), true);
}

TEST(listTest, emplace_back2) {
  stl::list<int> A{2, 6, 7, 8, 1, 0, 223};
  std::list<int> B{2, 6, 7, 8, 1, 0, 223, 1, 1, 1};
  A.emplace_back(1, 1, 1);
  ASSERT_EQ(isEqualList(A, B), true);
}

TEST(listTest, emplace_front2) {
  stl::list<int> A{2, 6, 7, 8, 1, 0, 223};
  std::list<int> B{1, 1, 1, 2, 6, 7, 8, 1, 0, 223};
  A.emplace_front(1, 1, 1);
  ASSERT_EQ(isEqualList(A, B), true);
}

//########################
//#                     ##
//#    SET TEST         ##
//#                     ##
//########################

TEST(testSet, constructorcopy) {
  stl::set<int> A{1, 67, -123, 2};
  std::set<int> B{1, 67, -123, 2};
  const stl::set<int> &C(A);
  const std::set<int> &D(B);
  ASSERT_EQ(isEqualSet(C, D), true);
}

TEST(testSet, constructorcopy2) {
  stl::set<int> A{8, 9, -1, 6, 5, -100, 100};
  std::set<int> B{8, 9, -1, 6, 5, -100, 100};
  const stl::set<int> &C(A);
  const std::set<int> &D(B);
  ASSERT_EQ(isEqualSet(C, D), true);
}

TEST(testSet, constructorcopy3) {
  stl::set<int> A{3, 9, 1, 0};
  std::set<int> B{3, 9, 1, 0};
  const stl::set<int> &C(A);
  const std::set<int> &D(B);
  ASSERT_EQ(isEqualSet(C, D), true);
}

TEST(testSet, constructorMove) {
  stl::set<int> A{3, 9, 1, 0};
  std::set<int> B{3, 9, 1, 0};
  stl::set<int> C(std::move(A));
  std::set<int> D(std::move(B));
  ASSERT_EQ(isEqualSet(C, D), true);
}

TEST(testSet, constructorMove2) {
  stl::set<int> A{1, 2, 2, 67, -123};
  std::set<int> B{1, 2, 2, 67, -123};
  stl::set<int> C(std::move(A));
  std::set<int> D(std::move(B));
  ASSERT_EQ(isEqualSet(C, D), true);
}

TEST(testSet, constructorMove3) {
  stl::set<int> A{8, 9, -1, 6, 5, -100, 100};
  std::set<int> B{8, 9, -1, 6, 5, -100, 100};
  stl::set<int> C(std::move(A));
  std::set<int> D(std::move(B));
  ASSERT_EQ(isEqualSet(C, D), true);
}

TEST(testSet, operatorMove) {
  stl::set<int> A{3, 9, 1, 0};
  std::set<int> B{3, 9, 1, 0};
  stl::set<int> C = std::move(A);
  std::set<int> D = std::move(B);
  ASSERT_EQ(isEqualSet(C, D), true);
}

TEST(testSet, operatorMove2) {
  stl::set<int> A{1, 2, 2, 67, -123};
  std::set<int> B{1, 2, 2, 67, -123};
  stl::set<int> C = std::move(A);
  std::set<int> D = std::move(B);
  ASSERT_EQ(isEqualSet(C, D), true);
}

TEST(testSet, operatorminusminus) {
  stl::set<int> A{8, 9, -1, 6, 5, -100, 100};
  std::set<int> B{8, 9, -1, 6, 5, -100, 100};
  auto i = A.begin();
  auto j = B.begin();
  for (int ij = 0; ij < 4; ++ij) ++i;
  for (int ji = 0; ji < 4; ++ji) ++j;
  --i;
  --j;
  --i;
  --j;
  ASSERT_EQ(*i, *j);
}

TEST(testSet, operatorminusminus2) {
  stl::set<int> A{8, 9, -1, 6, 5, -100, 100};
  std::set<int> B{8, 9, -1, 6, 5, -100, 100};
  auto i = A.begin();
  auto j = B.begin();
  for (int ij = 0; ij < 6; ++ij) ++i;
  for (int ji = 0; ji < 6; ++ji) ++j;
  --i;
  --j;
  --i;
  --j;
  --i;
  --j;

  ASSERT_EQ(*i, *j);
}

TEST(testSet, operatorMove3) {
  stl::set<int> A{8, 9, -1, 6, 5, -100, 100};
  std::set<int> B{8, 9, -1, 6, 5, -100, 100};
  stl::set<int> C = std::move(A);
  std::set<int> D = std::move(B);
  ASSERT_EQ(isEqualSet(C, D), true);
}

TEST(testSet, constructorInitiliazer) {
  stl::set<int> first{1, 2, 2, 67, -123};
  std::set<int> second{1, 2, 2, 67, -123};
  ASSERT_EQ(isEqualSet(first, second), true);
}

TEST(testSet, iteratorBegin) {
  stl::set<int> A{1, 67, -123, 2};
  std::set<int> B{1, 67, -123, 2};
  auto i = A.begin();
  auto j = B.begin();
  ++i;
  ++j;
  ASSERT_EQ(*i, *j);
}

TEST(testSet, empty) {
  stl::set<float> A;
  std::set<float> B;
  ASSERT_EQ(A.empty(), B.empty());
  stl::set<int> C{3, 9, 1, 0};
  std::set<int> D{3, 9, 1, 0};
  ASSERT_EQ(C.empty(), D.empty());
}

TEST(testSet, size) {
  stl::set<std::string> A{"A", "B"};
  std::set<std::string> B{"C", "D"};
  ASSERT_EQ(A.size(), B.size());
  stl::set<int> i;
  std::set<int> j;
  ASSERT_EQ(i.size(), j.size());
}

TEST(testSet, clear) {
  stl::set<int> A{9, 5, 8, 7};
  std::set<int> B{7, 8, 9};
  A.clear();
  B.clear();
  ASSERT_EQ(A.empty(), B.empty());
}

TEST(testSet, insert) {
  stl::set<float> A;
  std::set<float> B;
  stl::set<int> C;
  std::set<int> D;
  for (int i = 1; i <= 5; ++i) {
    A.insert(i * i);
  }
  for (int i = 1; i <= 5; ++i) {
    B.insert(i * i);
  }
  ASSERT_EQ(isEqualSet(A, B), true);
  auto i = A.insert(2.67f);
  auto I = B.insert(2.67f);
  auto j = A.insert(2.67f);
  auto J = B.insert(2.67f);
  ASSERT_EQ(i.second, I.second);
  ASSERT_EQ(j.second, J.second);
  ASSERT_EQ(isEqualSet(A, B), true);
}

TEST(testSet, erase) {
  stl::set<int> A{8, 9, -1, 6, 5, -100, 100};
  std::set<int> B{8, 9, -1, 6, 5, -100, 100};
  auto i = A.begin();
  auto j = B.begin();
  A.erase(i);
  B.erase(j);
  ASSERT_EQ(isEqualSet(A, B), true);
  auto a = A.begin();
  auto b = B.begin();
  ++a;
  ++b;
  A.erase(a);
  B.erase(b);
  ASSERT_EQ(isEqualSet(A, B), true);
}

TEST(testSet, eraseNoChild) {
  stl::set<int> A{8, 9, 10, 12, 33, -2, -4, 5, 6};
  std::set<int> B{8, 9, 10, 12, 33, -2, -4, 5, 6};
  A.erase(A.find(33));
  B.erase(B.find(33));
  ASSERT_EQ(isEqualSet(A, B), true);
}

TEST(testSet, eraseCaseFirst) {
  stl::set<int> A{8, 9, 10, 12, 33, -2, -4, 5, 6};
  std::set<int> B{8, 9, 10, 12, 33, -2, -4, 5, 6};
  A.erase(A.find(6));
  B.erase(B.find(6));
  ASSERT_EQ(isEqualSet(A, B), true);
}

TEST(testSet, eraseCaseSecond) {
  stl::set<int> A{6, 9, 8, 1};
  std::set<int> B{6, 9, 8, 1};
  A.erase(A.find(8));
  B.erase(B.find(8));
  ASSERT_EQ(isEqualSet(A, B), true);
}

TEST(testSet, eraseCase3) {
  stl::set<int> A{8, 9, 10, 12, 33, -2, -4, 5, 6};
  std::set<int> B{8, 9, 10, 12, 33, -2, -4, 5, 6};
  A.erase(A.find(-4));
  B.erase(B.find(-4));
  ASSERT_EQ(isEqualSet(A, B), true);
}

TEST(testSet, eraseCase4) {
  stl::set<int> A{8, 9, 10, 12, 33, -2, -4, 5, 6};
  std::set<int> B{8, 9, 10, 12, 33, -2, -4, 5, 6};
  A.erase(A.find(12));
  B.erase(B.find(12));
  ASSERT_EQ(isEqualSet(A, B), true);
}

TEST(testSet, eraseCase5) {
  stl::set<int> A{8, 9, 10, 12, 33, -2, -4, 5, 6};
  std::set<int> B{8, 9, 10, 12, 33, -2, -4, 5, 6};
  A.erase(A.find(-4));
  B.erase(B.find(-4));
  ASSERT_EQ(isEqualSet(A, B), true);
}

TEST(testSet, eraseCase6) {
  stl::set<int> A{8, 9, 10, 12, 33, -2, -4, 5, 6};
  std::set<int> B{8, 9, 10, 12, 33, -2, -4, 5, 6};
  A.erase(A.find(5));
  B.erase(B.find(5));
  ASSERT_EQ(isEqualSet(A, B), true);
}

TEST(testSet, eraseCase7) {
  stl::set<int> A{8, 9, 10, 12, 33, -2, -4, 5, 6};
  std::set<int> B{8, 9, 10, 12, 33, -2, -4, 5, 6};
  A.erase(A.find(6));
  B.erase(B.find(6));
  ASSERT_EQ(isEqualSet(A, B), true);
}

TEST(testSet, eraseCase8) {
  stl::set<int> A{8, 5, 10, 2, 6, 7};
  std::set<int> B{8, 5, 10, 2, 6, 7};
  A.erase(A.find(5));
  B.erase(B.find(5));
}

TEST(testSet, eraseCase9) {
  stl::set<int> A{8, 5, 10, 2, 6, 7};
  std::set<int> B{8, 5, 10, 2, 6, 7};
  A.erase(A.find(6));
  B.erase(B.find(6));
  ASSERT_EQ(isEqualSet(A, B), true);
}

TEST(testSet, eraseCas11) {
  stl::set<int> A{8, 5, 10, 2, 6, 7};
  std::set<int> B{8, 5, 10, 2, 6, 7};
  A.erase(A.find(2));
  B.erase(B.find(2));
  ASSERT_EQ(isEqualSet(A, B), true);
}

TEST(testSet, eraseCase10) {
  stl::set<int> A{8, 5, 10, 2, 6, 7};
  std::set<int> B{8, 5, 10, 2, 6, 7};
  A.erase(A.find(2));
  B.erase(B.find(2));
  ASSERT_EQ(isEqualSet(A, B), true);
}

TEST(testSet, eraseCase12) {
  stl::set<int> A{8, 5, 10, 2, 6, 7};
  std::set<int> B{8, 5, 10, 2, 6, 7};
  A.erase(A.find(7));
  B.erase(B.find(7));
  ASSERT_EQ(isEqualSet(A, B), true);
}

TEST(testSet, eraseCase13) {
  stl::set<int> A{8, 3, 10, 1, 6, 14, 4, 7, 13};
  std::set<int> B{8, 3, 10, 1, 6, 14, 4, 7, 13};
  A.erase(A.find(14));
  B.erase(B.find(14));
  ASSERT_EQ(isEqualSet(A, B), true);
}

TEST(testSet, eraseCase14) {
  stl::set<int> A{8, 3, 10, 1, 6, 14, 4, 7, 13};
  std::set<int> B{8, 3, 10, 1, 6, 14, 4, 7, 13};
  A.erase(A.find(10));
  B.erase(B.find(10));
  ASSERT_EQ(isEqualSet(A, B), true);
}

TEST(testSet, swap) {
  stl::set<int> A{8, 9, -1, 6, 5, -100, 100};
  std::set<int> B{8, 9, -1, 6, 5, -100, 100};
  stl::set<int> E{};
  std::set<int> F{};
  E.swap(A);
  F.swap(B);
  ASSERT_EQ(isEqualSet(E, F), true);
}

TEST(testSet, swapSec) {
  stl::set<int> A{867, 1900};
  std::set<int> B{867, 1900};
  stl::set<int> E{};
  std::set<int> F{};
  E.swap(A);
  F.swap(B);
  ASSERT_EQ(isEqualSet(E, F), true);
}

TEST(testSet, merge) {
  stl::set<int> PP{8, 9, -1, 6, 5, -100, 100};
  stl::set<int> PPP{867, 1900};
  std::set<int> A{8, 9, -1, 6, 5, -100, 100};
  std::set<int> B{867, 1900};
  PP.merge(PPP);
  A.merge(B);
  ASSERT_EQ(isEqualSet(PP, A), true);
}

TEST(testSet, find) {
  stl::set<int> A{6, 7, 1, 9};
  std::set<int> B{6, 7, 1, 9};
  ASSERT_EQ(*A.find(1), 1);
  ASSERT_EQ(*B.find(1), 1);
  stl::set<int> C{6, 7, 1, 9, 77, -9, 225, 100, 226, 61, 11, 12, -26, 1000};
  std::set<int> D{6, 7, 1, 9, 77, -9, 225, 100, 226, 61, 11, 12, -26, 1000};
  ASSERT_EQ(*C.find(11), 11);
  ASSERT_EQ(*D.find(11), 11);
}

TEST(testSet, findCaseTwo) {
  stl::set<int> C{228, 7777, 99,  6,  7,  1,  9,   77,  -9,
                  225, 100,  226, 61, 11, 12, -26, 1000};
  std::set<int> D{228, 7777, 99,  6,  7,  1,  9,   77,  -9,
                  225, 100,  226, 61, 11, 12, -26, 1000};
  ASSERT_EQ(*C.find(226), 226);
  ASSERT_EQ(*D.find(226), 226);
}

TEST(testSet, findCaseThird) {
  stl::set<int> A{6, 7, 1, 9};
  std::set<int> B{6, 7, 1, 9};
  ASSERT_EQ(*A.find(6), 6);
  ASSERT_EQ(*B.find(6), 6);
}

TEST(testSet, findCasef) {
  stl::set<int> A{2, 5, 9};
  ASSERT_EQ(*A.find(999), 2);
}

TEST(testSet, contains) {
  stl::set<int> C{228, 7777, 99,  6,  7,  1,  9,   77,  -9,
                  225, 100,  226, 61, 11, 12, -26, 1000};
  ASSERT_EQ(C.contains(13122), false);
}

TEST(testSet, containsTrue) {
  stl::set<int> C{228, 7777, 99,  6,  7,  1,  9,   77,  -9,
                  225, 100,  226, 61, 11, 12, -26, 1000};
  ASSERT_EQ(C.contains(-9), true);
}

TEST(testSet, emplaceArgs) {
  stl::set<int> C{228, 7777, 99,  6,  7,  1,  9,   77,  -9,
                  225, 100,  226, 61, 11, 12, -26, 1000};
  std::set<int> D{228, 7777, 99, 6,  7,  1,   9,    77,   -9,    225,
                  100, 226,  61, 11, 12, -26, 1000, -999, 11221, 111};
  C.emplace(-999, 11221, 111);
  ASSERT_EQ(isEqualSet(C, D), true);
}

TEST(testSet, emplaceArgs2) {
  stl::set<int> C{228, 7777, 99,  6,  7,  1,  9,   77,  -9,
                  225, 100,  226, 61, 11, 12, -26, 1000};
  std::set<int> D{228, 7777, 99, 6,  7,  1,   9,    77, -9, 225,
                  100, 226,  61, 11, 12, -26, 1000, 23, 999};
  C.emplace(23, 999);
  ASSERT_EQ(isEqualSet(C, D), true);
}

//########################
//#                     ##
//#    MULTISET TEST    ##
//#                     ##
//########################

TEST(multiSet, constructorcopy) {
  stl::multiset<int> A{1, 67, -123, 2};
  std::multiset<int> B{1, 67, -123, 2};
  const stl::multiset<int> &C(A);
  const std::multiset<int> &D(B);
  ASSERT_EQ(isEqualMultiSet(C, D), true);
}

TEST(multiSet, constructorcopy2) {
  stl::multiset<int> A{8, 9, -1, 6, 5, -100, 100};
  std::multiset<int> B{8, 9, -1, 6, 5, -100, 100};
  const stl::multiset<int> &C(A);
  const std::multiset<int> &D(B);
  ASSERT_EQ(isEqualMultiSet(C, D), true);
}

TEST(multiSet, constructorcopy3) {
  stl::multiset<int> A{3, 9, 1, 0};
  std::multiset<int> B{3, 9, 1, 0};
  const stl::multiset<int> &C(A);
  const std::multiset<int> &D(B);
  ASSERT_EQ(isEqualMultiSet(C, D), true);
}

TEST(multiSet, eraseCaseFirst) {
  stl::multiset<int> A{8, 9, 10, 12, 33, -2, -4, 5, 6};
  std::multiset<int> B{8, 9, 10, 12, 33, -2, -4, 5, 6};
  A.erase(A.find(6));
  B.erase(B.find(6));
  ASSERT_EQ(isEqualMultiSet(A, B), true);
}

TEST(multiSet, eraseCaseSecond) {
  stl::multiset<int> A{6, 9, 8, 1};
  std::multiset<int> B{6, 9, 8, 1};
  A.erase(A.find(8));
  B.erase(B.find(8));
  ASSERT_EQ(isEqualMultiSet(A, B), true);
}

TEST(multiSet, eraseCase3) {
  stl::multiset<int> A{8, 9, 10, 12, 33, -2, -4, 5, 6};
  std::multiset<int> B{8, 9, 10, 12, 33, -2, -4, 5, 6};
  A.erase(A.find(-4));
  B.erase(B.find(-4));
  ASSERT_EQ(isEqualMultiSet(A, B), true);
}

TEST(multiSet, eraseCase4) {
  stl::multiset<int> A{8, 9, 10, 12, 33, -2, -4, 5, 6};
  std::multiset<int> B{8, 9, 10, 12, 33, -2, -4, 5, 6};
  A.erase(A.find(12));
  B.erase(B.find(12));
  ASSERT_EQ(isEqualMultiSet(A, B), true);
}

TEST(multiSet, eraseCase5) {
  stl::multiset<int> A{8, 9, 10, 12, 33, -2, -4, 5, 6};
  std::multiset<int> B{8, 9, 10, 12, 33, -2, -4, 5, 6};
  A.erase(A.find(-4));
  B.erase(B.find(-4));
  ASSERT_EQ(isEqualMultiSet(A, B), true);
}

TEST(multiSet, eraseCase6) {
  stl::multiset<int> A{8, 9, 10, 12, 33, -2, -4, 5, 6};
  std::multiset<int> B{8, 9, 10, 12, 33, -2, -4, 5, 6};
  A.erase(A.find(5));
  B.erase(B.find(5));
  ASSERT_EQ(isEqualMultiSet(A, B), true);
}

TEST(multiSet, eraseCase7) {
  stl::multiset<int> A{8, 9, 10, 12, 33, -2, -4, 5, 6};
  std::multiset<int> B{8, 9, 10, 12, 33, -2, -4, 5, 6};
  A.erase(A.find(6));
  B.erase(B.find(6));
  ASSERT_EQ(isEqualMultiSet(A, B), true);
}

TEST(multiSet, eraseCase8) {
  stl::multiset<int> A{8, 5, 10, 2, 6, 7};
  std::multiset<int> B{8, 5, 10, 2, 6, 7};
  A.erase(A.find(5));
  B.erase(B.find(5));
}

TEST(multiSet, eraseCase9) {
  stl::multiset<int> A{8, 5, 10, 2, 6, 7};
  std::multiset<int> B{8, 5, 10, 2, 6, 7};
  A.erase(A.find(6));
  B.erase(B.find(6));
  ASSERT_EQ(isEqualMultiSet(A, B), true);
}

TEST(multiSet, eraseCas11) {
  stl::multiset<int> A{8, 5, 10, 2, 6, 7};
  std::multiset<int> B{8, 5, 10, 2, 6, 7};
  A.erase(A.find(2));
  B.erase(B.find(2));
  ASSERT_EQ(isEqualMultiSet(A, B), true);
}

TEST(multiSet, eraseCase10) {
  stl::multiset<int> A{8, 5, 10, 2, 6, 7};
  std::multiset<int> B{8, 5, 10, 2, 6, 7};
  A.erase(A.find(2));
  B.erase(B.find(2));
  ASSERT_EQ(isEqualMultiSet(A, B), true);
}

TEST(multiSet, eraseCase12) {
  stl::multiset<int> A{8, 5, 10, 2, 6, 7};
  std::multiset<int> B{8, 5, 10, 2, 6, 7};
  A.erase(A.find(7));
  B.erase(B.find(7));
  ASSERT_EQ(isEqualMultiSet(A, B), true);
}

TEST(multiSet, eraseCase13) {
  stl::multiset<int> A{8, 3, 10, 1, 6, 14, 4, 7, 13};
  std::multiset<int> B{8, 3, 10, 1, 6, 14, 4, 7, 13};
  A.erase(A.find(14));
  B.erase(B.find(14));
  ASSERT_EQ(isEqualMultiSet(A, B), true);
}

TEST(multiSet, eraseCase14) {
  stl::multiset<int> A{8, 3, 10, 1, 6, 14, 4, 7, 13};
  std::multiset<int> B{8, 3, 10, 1, 6, 14, 4, 7, 13};
  A.erase(A.find(10));
  B.erase(B.find(10));
  ASSERT_EQ(isEqualMultiSet(A, B), true);
}

TEST(multiSet, operatorminusminus) {
  stl::multiset<int> A{8, 9, -1, 6, 5, -100, 100};
  std::multiset<int> B{8, 9, -1, 6, 5, -100, 100};
  auto i = A.begin();
  auto j = B.begin();
  for (int ij = 0; ij < 4; ++ij) ++i;
  for (int ji = 0; ji < 4; ++ji) ++j;
  --i;
  --j;
  --i;
  --j;
  ASSERT_EQ(*i, *j);
}

TEST(multiSet, operatorminusminus2) {
  stl::multiset<int> A{8, 9, -1, 6, 5, -100, 100};
  std::multiset<int> B{8, 9, -1, 6, 5, -100, 100};
  auto i = A.begin();
  auto j = B.begin();
  for (int ij = 0; ij < 6; ++ij) ++i;
  for (int ji = 0; ji < 6; ++ji) ++j;
  --i;
  --j;
  --i;
  --j;
  --i;
  --j;
  ASSERT_EQ(*i, *j);
}

TEST(multiSet, initiliazerConstructor) {
  stl::multiset<int> A{2, 8, 8, 8};
  std::multiset<int> B{2, 8, 8, 8};
  ASSERT_EQ(isEqualMultiSet(A, B), true);
}

TEST(multiSet, initiliazerConstructorCase2) {
  stl::multiset<int> A{7, 8, 9, 1};
  std::multiset<int> B{7, 8, 9, 1};
  ASSERT_EQ(isEqualMultiSet(A, B), true);
}

TEST(multiset, iterator) {
  stl::multiset<int> A{2, 7, 8, 8};
  std::multiset<int> B{2, 7, 8, 8};
  auto i = A.begin();
  auto j = B.begin();
  ++i;
  ++j;
  ++i;
  ++j;
  ASSERT_EQ(*i, *j);
}

TEST(multiSet, empty) {
  stl::multiset<int> A{7, 8, 9, 1};
  std::multiset<int> B{7, 8, 9, 1};
  ASSERT_EQ(A.empty(), B.empty());
}

TEST(multiSet, emptyfalse) {
  stl::multiset<int> A{};
  std::multiset<int> B{};
  ASSERT_EQ(A.empty(), B.empty());
}

TEST(multiSet, size) {
  stl::multiset<int> A{1, 1, 1, 1, 1, 1};
  std::multiset<int> B{1, 1, 1, 1, 1, 1};
  ASSERT_EQ(A.size(), B.size());
}

TEST(multiSet, size2) {
  stl::multiset<int> A{};
  std::multiset<int> B{};
  ASSERT_EQ(A.size(), B.size());
}

TEST(multiSet, clear) {
  stl::multiset<float> A{};
  std::multiset<float> B{};
  A.clear();
  B.clear();
  ASSERT_EQ(A.empty(), B.empty());
}

TEST(multiSet, clear2) {
  stl::multiset<float> A{2, 9, 99.9f};
  std::multiset<float> B{1, 8};
  A.clear();
  B.clear();
  ASSERT_EQ(A.empty(), B.empty());
}

TEST(multiSet, clear3) {
  stl::multiset<float> A{2, 9, 99, 99.9f, 1};
  std::multiset<float> B{1, 8};
  A.clear();
  B.clear();
  ASSERT_EQ(A.empty(), B.empty());
}

TEST(multiSet, insert) {
  stl::multiset<int> A{};
  std::multiset<int> B{};
  A.insert(5);
  B.insert(5);
  A.insert(6);
  B.insert(6);
  ASSERT_EQ(isEqualMultiSet(A, B), true);
}

TEST(multiSet, insert1) {
  stl::multiset<float> A{1.1f};
  std::multiset<float> B{1.1f};
  A.insert(1.1f);
  B.insert(1.1f);
  A.insert(1.1f);
  B.insert(1.1f);
  ASSERT_EQ(isEqualMultiSet(A, B), true);
}

TEST(multiSet, insert2) {
  stl::multiset<double> A{2, 7.9};
  std::multiset<double> B{2, 7.9};
  for (double i = 1; i < 4; ++i) {
    A.insert(i + 3);
  }
  for (double i = 1; i < 4; ++i) {
    B.insert(i + 3);
  }
  ASSERT_EQ(isEqualMultiSet(A, B), true);
}

TEST(multiSet, insert3) {
  stl::multiset<int> A{2, 7, 8, 8};
  std::multiset<int> B{2, 7, 8, 8};
  auto itstl = A.insert(-2);
  auto itstd = B.insert(-2);
  ++itstl;
  ++itstd;
  ASSERT_EQ(*itstl, *itstd);
}

TEST(multiSet, swap) {
  stl::multiset<int> A{1, 1, 1, 1, 1, 1};
  std::multiset<int> B{1, 1, 1, 1, 1, 1};
  stl::multiset<int> C;
  std::multiset<int> D;
  C.swap(A);
  D.swap(B);
  ASSERT_EQ(isEqualMultiSet(C, D), true);
}

TEST(multiSet, swap2) {
  stl::multiset<int> A{6,   7,   1,  9,  77, -9,  225,
                       100, 226, 61, 11, 12, -26, 1000};
  std::multiset<int> B{6,   7,   1,  9,  77, -9,  225,
                       100, 226, 61, 11, 12, -26, 1000};
  stl::multiset<int> C{};
  std::multiset<int> D{};
  C.swap(A);
  D.swap(B);
  ASSERT_EQ(isEqualMultiSet(C, D), true);
}

TEST(multiSet, merge) {
  stl::multiset<int> PP{8, 9, -1, 6, 5, -100, 100};
  stl::multiset<int> PPP{867, 1900};
  std::multiset<int> A{8, 9, -1, 6, 5, -100, 100};
  std::multiset<int> B{867, 1900};
  PP.merge(PPP);
  A.merge(B);
  auto i = PP.begin();
  auto j = A.begin();
  while (i != PP.end() && j != A.end()) {
    ASSERT_EQ(*i, *j);
    ++i;
    ++j;
  }
}

TEST(multiSet, count) {
  stl::multiset<int> A{1, 3, 1, 2, 91, 3, 1, 2, 9, 1};
  std::multiset<int> B{1, 3, 1, 2, 91, 3, 1, 2, 9, 1};
  ASSERT_EQ(A.count(2), B.count(2));
}

TEST(multiSet, count2) {
  stl::multiset<int> A{1, 1, 1, 1, 1, 1};
  std::multiset<int> B{1, 1, 1, 1, 1, 1};
  ASSERT_EQ(A.count(1), B.count(1));
}

TEST(multiSet, count3) {
  stl::multiset<int> A{228, 7777, 99,  6,  7,  1,  9,   77,  -9,
                       225, 100,  226, 61, 11, 12, -26, 1000};
  std::multiset<int> B{228, 7777, 99,  6,  7,  1,  9,   77,  -9,
                       225, 100,  226, 61, 11, 12, -26, 1000};
  ASSERT_EQ(A.count(6), B.count(6));
}

TEST(multiSet, find) {
  stl::multiset<int> A{228, 7777, 99,  6,  7,  1,  9,   77,  -9,
                       225, 100,  226, 61, 11, 12, -26, 1000};
  std::multiset<int> B{228, 7777, 99,  6,  7,  1,  9,   77,  -9,
                       225, 100,  226, 61, 11, 12, -26, 1000};
  auto i = A.find(-26);
  ASSERT_EQ(*i, -26);
}

TEST(multiSet, find2) {
  stl::multiset<int> A{228, 7777, 99,  6,  7,  1,  9,   77,  -9,
                       225, 100,  226, 61, 11, 12, -26, 1000};
  std::multiset<int> B{228, 7777, 99,  6,  7,  1,  9,   77,  -9,
                       225, 100,  226, 61, 11, 12, -26, 1000};
  auto i = A.find(7777);
  ASSERT_EQ(*i, 7777);
}

TEST(multiSet, find3) {
  stl::multiset<int> A{228, 7777, 99,  6,  7,  1,  9,   77,  -9,
                       225, 100,  226, 61, 11, 12, -26, 1000};
  std::multiset<int> B{228, 7777, 99,  6,  7,  1,  9,   77,  -9,
                       225, 100,  226, 61, 11, 12, -26, 1000};
  auto i = A.find(61);
  ASSERT_EQ(*i, 61);
}

TEST(multiSet, find4) {
  stl::multiset<int> A{228, 7777, 99,  6,  7,  1,  9,   77,  -9,
                       225, 100,  226, 61, 11, 12, -26, 1000};
  std::multiset<int> B{228, 7777, 99,  6,  7,  1,  9,   77,  -9,
                       225, 100,  226, 61, 11, 12, -26, 1000};
  auto i = A.find(9);
  ASSERT_EQ(*i, 9);
}

TEST(multiSet, find5) {
  stl::multiset<int> A{228, 7777, 99,  6,  7,  1,  9,   77,  -9,
                       225, 100,  226, 61, 11, 12, -26, 1000};
  std::multiset<int> B{228, 7777, 99,  6,  7,  1,  9,   77,  -9,
                       225, 100,  226, 61, 11, 12, -26, 1000};
  auto i = A.find(1);
  ASSERT_EQ(*i, 1);
}

TEST(multiSet, contains) {
  stl::multiset<int> A{228, 7777, 99,  6,  7,  1,  9,   77,  -9,
                       225, 100,  226, 61, 11, 12, -26, 1000};
  std::multiset<int> B{228, 7777, 99,  6,  7,  1,  9,   77,  -9,
                       225, 100,  226, 61, 11, 12, -26, 1000};
  ASSERT_EQ(A.contains(-26), true);
}

TEST(multiSet, contains2) {
  stl::multiset<int> A{228, 7777, 99,  6,  7,  1,  9,   77,  -9,
                       225, 100,  226, 61, 11, 12, -26, 1000};
  std::multiset<int> B{228, 7777, 99,  6,  7,  1,  9,   77,  -9,
                       225, 100,  226, 61, 11, 12, -26, 1000};
  ASSERT_EQ(A.contains(-262), false);
}

TEST(multiSet, contains3) {
  stl::multiset<int> A{228, 7777, 99,  6,  7,  1,  9,   77,  -9,
                       225, 100,  226, 61, 11, 12, -26, 1000};
  std::multiset<int> B{228, 7777, 99,  6,  7,  1,  9,   77,  -9,
                       225, 100,  226, 61, 11, 12, -26, 1000};
  ASSERT_EQ(A.contains(228), true);
}

TEST(multiSet, contains4) {
  stl::multiset<int> A{228, 7777, 99,  6,  7,  1,  9,   77,  -9,
                       225, 100,  226, 61, 11, 12, -26, 1000};
  std::multiset<int> B{228, 7777, 99,  6,  7,  1,  9,   77,  -9,
                       225, 100,  226, 61, 11, 12, -26, 1000};
  ASSERT_EQ(A.contains(1000), true);
}

TEST(multiSet, contains5) {
  stl::multiset<int> A{228, 7777, 99,  6,  7,  1,  9,   77,  -9,
                       225, 100,  226, 61, 11, 12, -26, 1000};
  std::multiset<int> B{228, 7777, 99,  6,  7,  1,  9,   77,  -9,
                       225, 100,  226, 61, 11, 12, -26, 1000};
  ASSERT_EQ(A.contains(-112), false);
}

TEST(multiSet, contains6) {
  stl::multiset<int> A{228, 7777, 99,  6,  7,  1,  9,   77,  -9,
                       225, 100,  226, 61, 11, 12, -26, 1000};
  std::multiset<int> B{228, 7777, 99,  6,  7,  1,  9,   77,  -9,
                       225, 100,  226, 61, 11, 12, -26, 1000};
  ASSERT_EQ(A.contains(-26), true);
}

TEST(multiSet, lower_bound) {
  stl::multiset<int> A{6,   7,   1,  9,  77, -9,  225,
                       100, 226, 61, 11, 12, -26, 1000};
  std::multiset<int> B{6,   7,   1,  9,  77, -9,  225,
                       100, 226, 61, 11, 12, -26, 1000};
  auto i = A.lower_bound(11);
  auto j = B.lower_bound(11);
  ASSERT_EQ(*i, *j);
}

TEST(multiSet, lower_bound2) {
  stl::multiset<int> A{6,   7,   1,  9,  77, -9,  225,
                       100, 226, 61, 11, 12, -26, 1000};
  std::multiset<int> B{6,   7,   1,  9,  77, -9,  225,
                       100, 226, 61, 11, 12, -26, 1000};
  auto i = A.lower_bound(226);
  auto j = B.lower_bound(226);
  ASSERT_EQ(*i, *j);
}

TEST(multiSet, lower_bound3) {
  stl::multiset<int> A{6,   7,   1,  9,  77, -9,  225,
                       100, 226, 61, 11, 12, -26, 1000};
  std::multiset<int> B{6,   7,   1,  9,  77, -9,  225,
                       100, 226, 61, 11, 12, -26, 1000};
  auto i = A.lower_bound(100);
  auto j = B.lower_bound(100);
  ASSERT_EQ(*i, *j);
}

TEST(multiSet, lower_bound4) {
  stl::multiset<int> A{6,   7,   1,  9,  77, -9,  225,
                       100, 226, 61, 11, 12, -26, 1000};
  std::multiset<int> B{6,   7,   1,  9,  77, -9,  225,
                       100, 226, 61, 11, 12, -26, 1000};
  auto i = A.lower_bound(77);
  auto j = B.lower_bound(77);
  ASSERT_EQ(*i, *j);
}

TEST(multiSet, lower_bound5) {
  stl::multiset<int> A{6,   7,   1,  9,  77, -9,  225,
                       100, 226, 61, 11, 12, -26, 1000};
  std::multiset<int> B{6,   7,   1,  9,  77, -9,  225,
                       100, 226, 61, 11, 12, -26, 1000};
  auto i = A.lower_bound(-9);
  auto j = B.lower_bound(-9);
  ASSERT_EQ(*i, *j);
}

TEST(multiSet, upper_bound) {
  stl::multiset<int> A{6,   7,   1,  9,  77, -9,  225,
                       100, 226, 61, 11, 12, -26, 1000};
  std::multiset<int> B{6,   7,   1,  9,  77, -9,  225,
                       100, 226, 61, 11, 12, -26, 1000};
  auto i = A.upper_bound(1);
  auto j = B.upper_bound(1);
  ASSERT_EQ(*i, *j);
}

TEST(multiSet, upper_bound2) {
  stl::multiset<int> A{6,   7,   1,  9,  77, -9,  225,
                       100, 226, 61, 11, 12, -26, 1000};
  std::multiset<int> B{6,   7,   1,  9,  77, -9,  225,
                       100, 226, 61, 11, 12, -26, 1000};
  auto i = A.upper_bound(61);
  auto j = B.upper_bound(61);
  ASSERT_EQ(*i, *j);
}

TEST(multiSet, upper_bound3) {
  stl::multiset<int> A{6,   7,   1,  9,  77, -9,  225,
                       100, 226, 61, 11, 12, -26, 1000};
  std::multiset<int> B{6,   7,   1,  9,  77, -9,  225,
                       100, 226, 61, 11, 12, -26, 1000};
  auto i = A.upper_bound(-26);
  auto j = B.upper_bound(-26);
  ASSERT_EQ(*i, *j);
}

TEST(multiSet, upper_bound4) {
  stl::multiset<int> A{6,   7,   1,  9,  77, -9,  225,
                       100, 226, 61, 11, 12, -26, 1000};
  std::multiset<int> B{6,   7,   1,  9,  77, -9,  225,
                       100, 226, 61, 11, 12, -26, 1000};
  auto i = A.upper_bound(12);
  auto j = B.upper_bound(12);
  ASSERT_EQ(*i, *j);
}

TEST(multiSet, upper_bound5) {
  stl::multiset<int> A{6,   7,   1,  9,  77, -9,  225,
                       100, 226, 61, 11, 12, -26, 1000};
  std::multiset<int> B{6,   7,   1,  9,  77, -9,  225,
                       100, 226, 61, 11, 12, -26, 1000};
  auto i = A.upper_bound(100);
  auto j = B.upper_bound(100);
  ASSERT_EQ(*i, *j);
}

TEST(multiSet, equal_range) {
  stl::multiset<int> A{6,   7,   1,  9,  77, -9,  225,
                       100, 226, 61, 11, 12, -26, 1000};
  std::multiset<int> B{6,   7,   1,  9,  77, -9,  225,
                       100, 226, 61, 11, 12, -26, 1000};
  auto i = A.equal_range(226);
  auto j = B.equal_range(226);
  while (i.first != i.second && j.first != j.second) {
    ++i.first;
    ++j.first;
    ASSERT_EQ(*i.first, *j.first);
  }
}

TEST(multiSet, equal_range2) {
  stl::multiset<int> A{6,   7,   1,  9,  77, -9,  225,
                       100, 226, 61, 11, 12, -26, 1000};
  std::multiset<int> B{6,   7,   1,  9,  77, -9,  225,
                       100, 226, 61, 11, 12, -26, 1000};
  auto i = A.equal_range(-9);
  auto j = B.equal_range(-9);
  while (i.first != i.second && j.first != j.second) {
    ++i.first;
    ++j.first;
    ASSERT_EQ(*i.first, *j.first);
  }
}

TEST(multiSet, equal_range3) {
  stl::multiset<int> A{6,   7,   1,  9,  77, -9,  225,
                       100, 226, 61, 11, 12, -26, 1000};
  std::multiset<int> B{6,   7,   1,  9,  77, -9,  225,
                       100, 226, 61, 11, 12, -26, 1000};
  auto i = A.equal_range(100);
  auto j = B.equal_range(100);
  while (i.first != i.second && j.first != j.second) {
    ++i.first;
    ++j.first;
    ASSERT_EQ(*i.first, *j.first);
  }
}

TEST(multiSet, equal_range4) {
  stl::multiset<int> A{6,   7,   1,  9,  77, -9,  225,
                       100, 226, 61, 11, 12, -26, 1000};
  std::multiset<int> B{6,   7,   1,  9,  77, -9,  225,
                       100, 226, 61, 11, 12, -26, 1000};
  auto i = A.equal_range(6);
  auto j = B.equal_range(6);
  while (i.first != i.second && j.first != j.second) {
    ++i.first;
    ++j.first;
    ASSERT_EQ(*i.first, *j.first);
  }
}

TEST(multiSet, equal_range5) {
  stl::multiset<int> A{6,   7,   1,  9,  77, -9,  225,
                       100, 226, 61, 11, 12, -26, 1000};
  std::multiset<int> B{6,   7,   1,  9,  77, -9,  225,
                       100, 226, 61, 11, 12, -26, 1000};
  auto i = A.equal_range(77);
  auto j = B.equal_range(77);
  while (i.first != i.second && j.first != j.second) {
    ++i.first;
    ++j.first;
    ASSERT_EQ(*i.first, *j.first);
  }
}

TEST(testmultiSet, emplaceArgs) {
  stl::multiset<int> C{228, 7777, 99,  6,  7,  1,  9,   77,  -9,
                       225, 100,  226, 61, 11, 12, -26, 1000};
  std::multiset<int> D{228, 7777, 99, 6,  7,  1,   9,    77,   -9,    225,
                       100, 226,  61, 11, 12, -26, 1000, -999, 11221, 111};
  C.emplace(-999, 11221, 111);
  ASSERT_EQ(isEqualMultiSet(C, D), true);
}

TEST(testmultiSet, emplaceArgs2) {
  stl::multiset<int> C{228, 7777, 99,  6,  7,  1,  9,   77,  -9,
                       225, 100,  226, 61, 11, 12, -26, 1000};
  std::multiset<int> D{228, 7777, 99, 6,  7,  1,   9,    77, -9, 225,
                       100, 226,  61, 11, 12, -26, 1000, 23, 999};
  C.emplace(23, 999);
  ASSERT_EQ(isEqualMultiSet(C, D), true);
}

//########################
//#                     ##
//#      MAP TEST       ##
//#                     ##
//########################

TEST(mapTest, constructorCopy) {
  stl::map<int, std::string> A{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  std::map<int, std::string> B{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  stl::map<int, std::string> C(A);
  std::map<int, std::string> D(B);
  ASSERT_EQ(isEqualMap(C, D), true);
}

TEST(mapTest, constructorCopy2) {
  stl::map<int, std::string> A{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  std::map<int, std::string> B{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  stl::map<int, std::string> C(A);
  std::map<int, std::string> D(B);
  ASSERT_EQ(isEqualMap(C, D), true);
}

TEST(mapTest, constructorCopy3) {
  stl::map<int, std::string> A{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  std::map<int, std::string> B{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  stl::map<int, std::string> C(A);
  std::map<int, std::string> D(B);
  ASSERT_EQ(isEqualMap(C, D), true);
}

TEST(mapTest, constructorMove) {
  stl::map<int, std::string> A{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  std::map<int, std::string> B{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  stl::map<int, std::string> C(std::move(A));
  std::map<int, std::string> D(std::move(B));
  ASSERT_EQ(isEqualMap(C, D), true);
}

TEST(mapTest, constructorMove2) {
  stl::map<int, std::string> A{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  std::map<int, std::string> B{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  stl::map<int, std::string> C(std::move(A));
  std::map<int, std::string> D(std::move(B));
  ASSERT_EQ(isEqualMap(C, D), true);
}

TEST(mapTest, constructorMove3) {
  stl::map<int, std::string> A{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  std::map<int, std::string> B{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  stl::map<int, std::string> C(std::move(A));
  std::map<int, std::string> D(std::move(B));
  ASSERT_EQ(isEqualMap(C, D), true);
}

TEST(mapSet, operatorminusminus) {
  stl::map<int, std::string> A{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  std::map<int, std::string> B{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  auto i = A.begin();
  auto j = B.begin();
  for (int ij = 0; ij < 4; ++ij) ++i;
  for (int ji = 0; ji < 4; ++ji) ++j;
  --i;
  --j;
  --i;
  --j;
  ASSERT_EQ((*i).first, (*j).first);
  ASSERT_EQ((*i).second, (*j).second);
}

TEST(mapSet, operatorminusminus2) {
  stl::map<int, std::string> A{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  std::map<int, std::string> B{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  auto i = A.begin();
  auto j = B.begin();
  for (int ij = 0; ij < 8; ++ij) ++i;
  for (int ji = 0; ji < 8; ++ji) ++j;
  --i;
  --j;
  --i;
  --j;
  --i;
  --j;
  ASSERT_EQ((*i).first, (*j).first);
  ASSERT_EQ((*i).second, (*j).second);
}

TEST(mapTest, constructorInitialiazer) {
  stl::map<int, std::string> A{{1, "Bob"}, {8, "max"}, {-4, "ella"}};
  std::map<int, std::string> B{{1, "Bob"}, {8, "max"}, {-4, "ella"}};
  ASSERT_EQ(isEqualMap(A, B), true);
}

TEST(mapTest, constructorInitialiazer2) {
  stl::map<int, std::string> A{{-1, "victor"}, {8, "bobby"}, {-4, "ella"}};
  std::map<int, std::string> B{{-1, "victor"}, {8, "bobby"}, {-4, "ella"}};
  ASSERT_EQ(isEqualMap(A, B), true);
}

TEST(mapTest, constructorInitialiazer3) {
  stl::map<int, std::string> A{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  std::map<int, std::string> B{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  ASSERT_EQ(isEqualMap(A, B), true);
}

TEST(mapTest, at) {
  stl::map<int, std::string> A{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  std::map<int, std::string> B{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  ASSERT_EQ(A.at(99), B.at(99));
}

TEST(mapTest, at2) {
  stl::map<int, std::string> A{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  std::map<int, std::string> B{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  ASSERT_EQ(A.at(-1), B.at(-1));
}

TEST(mapTest, at3) {
  stl::map<int, std::string> A{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  std::map<int, std::string> B{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  ASSERT_EQ(A.at(-112), B.at(-112));
}

TEST(mapTest, at4) {
  stl::map<int, std::string> A{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  std::map<int, std::string> B{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  ASSERT_EQ(A.at(-1), B.at(-1));
}

TEST(mapTest, at5) {
  stl::map<int, std::string> A{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  std::map<int, std::string> B{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  ASSERT_EQ(A.at(8), B.at(8));
}

TEST(mapTest, operatorBrackets) {
  stl::map<int, std::string> A{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  std::map<int, std::string> B{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  ASSERT_EQ(A[8], B[8]);
}

TEST(mapTest, operatorBrackets2) {
  stl::map<int, std::string> A{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  std::map<int, std::string> B{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  ASSERT_EQ(A[4], B[4]);
}

TEST(mapTest, operatorBrackets3) {
  stl::map<int, std::string> A{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  std::map<int, std::string> B{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  ASSERT_EQ(A[112], B[112]);
}

TEST(mapTest, operatorBrackets4) {
  stl::map<int, std::string> A{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  std::map<int, std::string> B{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  ASSERT_EQ(A[-1], B[-1]);
}

TEST(mapTest, operatorBrackets5) {
  stl::map<int, std::string> A{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  std::map<int, std::string> B{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  ASSERT_EQ(A[-4], B[-4]);
}

TEST(mapTest, empty) {
  stl::map<int, std::string> A{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  std::map<int, std::string> B{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  A.clear();
  B.clear();
  ASSERT_EQ(A.empty(), B.empty());
}

TEST(mapTest, empty2) {
  stl::map<int, std::string> A{{5, "a"}};
  std::map<int, std::string> B{{8, "b"}};
  ASSERT_EQ(A.empty(), B.empty());
}

TEST(mapTest, size) {
  stl::map<int, std::string> A{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  std::map<int, std::string> B{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  ASSERT_EQ(A.size(), B.size());
}

TEST(mapTest, iterator) {
  stl::map<int, std::string> A{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  std::map<int, std::string> B{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  auto i = A.begin();
  auto j = B.begin();
  ++i;
  ++j;
  ++i;
  ++j;
  ++i;
  ++j;
  ++i;
  ++j;
  ASSERT_EQ((*i).first, (*j).first);
  ASSERT_EQ((*i).second, (*j).second);
  --i;
  --j;
  --i;
  --j;
  ASSERT_EQ((*i).first, (*j).first);
  ASSERT_EQ((*i).second, (*j).second);
}

TEST(mapTest, size2) {
  stl::map<int, std::string> A{};
  std::map<int, std::string> B{};
  ASSERT_EQ(A.size(), B.size());
}

TEST(mapTest, size3) {
  stl::map<int, std::string> A{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  std::map<int, std::string> B{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  ASSERT_EQ(A.size(), B.size());
}

TEST(mapTest, clear) {
  stl::map<int, std::string> A{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  std::map<int, std::string> B{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  A.clear();
  B.clear();
  ASSERT_EQ(A.empty(), B.empty());
}

TEST(mapTest, insert1) {
  stl::map<int, std::string> A{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  std::map<int, std::string> B{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  A.insert({7988, "bobby"});
  B.insert({7988, "bobby"});
  ASSERT_EQ(isEqualMap(A, B), true);
}

TEST(mapTest, insert2) {
  stl::map<int, std::string> A{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  std::map<int, std::string> B{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  A.insert({-12, "bobby"});
  B.insert({-12, "bobby"});
  for (int i = 999; i < 1100; i += 15) {
    A.insert({i, "s"});
    B.insert({i, "s"});
  }
  ASSERT_EQ(isEqualMap(A, B), true);
}

TEST(mapTest, insertcaseTwo) {
  stl::map<int, std::string> A{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  std::map<int, std::string> B{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  A.insert(-12, "bobby");
  B.insert({-12, "bobby"});
  for (int i = 999; i < 1100; i += 15) {
    A.insert(i, "s");
    B.insert({i, "s"});
  }
  ASSERT_EQ(isEqualMap(A, B), true);
}

TEST(mapTest, insert_assign) {
  stl::map<int, std::string> A{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  std::map<int, std::string> B{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  A.insert_or_assign(-1, "lola");
  B.insert_or_assign(-1, "lola");
  ASSERT_EQ(isEqualMap(A, B), true);
}

TEST(mapTest, insert_assign2) {
  stl::map<int, std::string> A{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  std::map<int, std::string> B{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  A.insert_or_assign(-199, "lola");
  B.insert_or_assign(-199, "lola");
  ASSERT_EQ(isEqualMap(A, B), true);
}

TEST(mapTest, insert_assign3) {
  stl::map<int, std::string> A{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  std::map<int, std::string> B{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  A.insert_or_assign(112, "hola");
  B.insert_or_assign(112, "hola");
  ASSERT_EQ(isEqualMap(A, B), true);
}

TEST(mapTest, insert_assign4) {
  stl::map<int, std::string> A{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  std::map<int, std::string> B{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  A.insert_or_assign(4, "Ian");
  B.insert_or_assign(4, "Ian");
  ASSERT_EQ(isEqualMap(A, B), true);
}

TEST(mapTest, insert_assign5) {
  stl::map<int, std::string> A{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  std::map<int, std::string> B{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  A.insert_or_assign(11, "vladimir");
  B.insert_or_assign(11, "vladimir");
  ASSERT_EQ(isEqualMap(A, B), true);
}

TEST(mapTest, swap) {
  stl::map<int, std::string> A;
  std::map<int, std::string> B;
  stl::map<int, std::string> C{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  std::map<int, std::string> D{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  A.swap(C);
  B.swap(D);
  ASSERT_EQ(isEqualMap(A, B), true);
}

TEST(mapTest, swap2) {
  stl::map<int, std::string> A{};
  std::map<int, std::string> B{};
  stl::map<int, std::string> C{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  std::map<int, std::string> D{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  A.swap(C);
  B.swap(D);
  ASSERT_EQ(isEqualMap(A, B), true);
}

TEST(mapTest, merge) {
  stl::map<int, std::string> A{};
  std::map<int, std::string> B{};
  stl::map<int, std::string> C{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  std::map<int, std::string> D{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  A.merge(C);
  B.merge(D);
  ASSERT_EQ(A.empty(), B.empty());
  ASSERT_EQ(isEqualMap(A, B), true);
}

TEST(mapTest, merge2) {
  stl::map<int, std::string> A{{1, "Bob"}, {890, "max"}, {-4, "ella"}};
  std::map<int, std::string> B{{1, "Bob"}, {890, "max"}, {-4, "ella"}};
  stl::map<int, std::string> C{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  std::map<int, std::string> D{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  A.merge(C);
  B.merge(D);
  ASSERT_EQ(isEqualMap(A, B), true);
}

TEST(mapTest, contains) {
  stl::map<int, std::string> A{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  ASSERT_EQ(A.contains(78), true);
}

TEST(mapTest, contains2) {
  stl::map<int, std::string> A{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  ASSERT_EQ(A.contains(1000), true);
}

TEST(mapTest, contains3) {
  stl::map<int, std::string> A{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  ASSERT_EQ(A.contains(-87765), false);
}

TEST(mapTest, contains4) {
  stl::map<int, std::string> A{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  ASSERT_EQ(A.contains(3750), true);
}

TEST(mapTest, contains5) {
  stl::map<int, std::string> A{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  ASSERT_EQ(A.contains(4), true);
}

TEST(mapTest, erase) {
  stl::map<int, std::string> A{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  std::map<int, std::string> B{{-1, "ella"},   {8, "bobby"},  {-4, "ella"},
                               {99, "robert"}, {112, "sean"}, {4, "leap"},
                               {-112, "max"}};
  A.erase(A.find(112));
  B.erase(B.find(112));
  ASSERT_EQ(isEqualMap(A, B), true);
}

TEST(mapTest, erase2) {
  stl::map<int, std::string> A{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  std::map<int, std::string> B{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  A.erase(A.find(444));
  B.erase(B.find(444));
  ASSERT_EQ(isEqualMap(A, B), true);
}

TEST(mapTest, erase3) {
  stl::map<int, std::string> A{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  std::map<int, std::string> B{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  A.erase(A.find(322));
  B.erase(B.find(322));
  ASSERT_EQ(isEqualMap(A, B), true);
}

TEST(mapTest, erase4) {
  stl::map<int, std::string> A{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  std::map<int, std::string> B{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  A.erase(A.find(7));
  B.erase(B.find(7));
  ASSERT_EQ(isEqualMap(A, B), true);
}

TEST(mapTest, erase5) {
  stl::map<int, std::string> A{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  std::map<int, std::string> B{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  A.erase(A.find(89));
  B.erase(B.find(89));
  ASSERT_EQ(isEqualMap(A, B), true);
}

TEST(mapTest, erase6) {
  stl::map<int, std::string> A{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  std::map<int, std::string> B{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  A.erase(A.find(78));
  B.erase(B.find(78));
  ASSERT_EQ(isEqualMap(A, B), true);
}

TEST(mapTest, erase7) {
  stl::map<int, std::string> A{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  std::map<int, std::string> B{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  A.erase(A.find(4));
  B.erase(B.find(4));
  ASSERT_EQ(isEqualMap(A, B), true);
}

TEST(mapTest, erase8) {
  stl::map<int, std::string> A{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  std::map<int, std::string> B{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  A.erase(A.find(1000));
  B.erase(B.find(1000));
  ASSERT_EQ(isEqualMap(A, B), true);
}

TEST(mapTest, emplaceArgs) {
  stl::map<int, std::string> A{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  std::map<int, std::string> B{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"},  {99, "allc"},
      {11221, "trip"}, {111, "today"}};
  A.emplace(std::pair<int, std::string>(99, "allc"),
            std::pair<int, std::string>(11221, "trip"),
            std::pair<int, std::string>(111, "today"));
  ASSERT_EQ(isEqualMap(A, B), true);
}

TEST(mapTest, emplaceArgs2) {
  stl::map<int, std::string> A{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"}};
  std::map<int, std::string> B{
      {-1, "ella"},    {8, "bobby"},    {-4, "ella"},  {99, "robert"},
      {112, "sean"},   {4, "leap"},     {-112, "max"}, {7, "yopy"},
      {1000, "debby"}, {444, "carl"},   {89, "robby"}, {3750, "nataly"},
      {78, "sergey"},  {322, "daniel"}, {-3, "curl"},  {9, "all"},
      {1122, "tri"},   {11, "toda"}};
  A.emplace(std::pair<int, std::string>(9, "all"),
            std::pair<int, std::string>(1122, "tri"),
            std::pair<int, std::string>(11, "toda"));
  ASSERT_EQ(isEqualMap(A, B), true);
}

//########################
//#                     ##
//#      STACK TEST     ##
//#                     ##
//########################

TEST(test_def_constructor_stack, def_constr_1) {
  stl::stack<double> st;
  stl::stack<double> st_1;
  stl::stack<double> st_2;
  stl::stack<double> st_3;
  stl::stack<double> st_4;
  stl::stack<double> st_5;
  stl::stack<double> st_6;
  stl::stack<double> st_7;
  stl::stack<double> st_8;
  for (auto i = 0.0; i < 100; ++i) {
    st.push(i);
    ASSERT_EQ(st.top(), i);
  }
}

TEST(test_list, list_1) {
  std::initializer_list<double> c1{0, 10, 2, 0, 0, 4, 6, 7, 100.432, 1.1234567};
  stl::stack<double> st(c1);
  for (auto i = c1.end() - 1; i != c1.begin(); --i) {
    ASSERT_EQ(st.top(), *i);
    st.pop();
  }
}

TEST(test_list, list_2) {
  std::initializer_list<double> c1{-10000000000000000000.9999999999999999999,
                                   0.1,
                                   -1,
                                   +0,
                                   -0,
                                   0.0101010101010,
                                   0.000000000001,
                                   -1000.999999999999998,
                                   -1000000.00000000,
                                   -1000000};
  stl::stack<double> st(c1);
  for (auto i = c1.end() - 1; i != c1.begin(); --i) {
    ASSERT_EQ(st.top(), *i);
    st.pop();
  }
}

TEST(test_list, list_3) {
  std::initializer_list<double> c1{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  std::initializer_list<double> c4(c1);

  stl::stack<double> st(c4);
  for (auto i = c4.end() - 1; i != c4.begin(); --i) {
    ASSERT_EQ(st.top(), *i);
    st.pop();
  }
}

TEST(copy_test, copy_1) {
  std::initializer_list<int> c1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  stl::stack<int> st(c1);
  stl::stack<int> st_copy(st);
  for (auto i = c1.end() - 1; i != c1.begin(); --i) {
    ASSERT_EQ(st.top(), st_copy.top());
    st.pop();
    st_copy.pop();
  }
}

TEST(copy_test, copy_2) {
  std::initializer_list<double> c1{-10000000000000000000.9999999999999999999,
                                   0.1,
                                   -1,
                                   +0,
                                   -0,
                                   0.0101010101010,
                                   0.000000000001,
                                   -1000.999999999999998,
                                   -1000000.00000000,
                                   -1000000};
  stl::stack<double> st(c1);
  stl::stack<double> st_copy(st);
  for (auto i = c1.end() - 1; i != c1.begin(); --i) {
    ASSERT_EQ(st.top(), st_copy.top());
    st.pop();
    st_copy.pop();
  }
}

TEST(test_move_constr, move_constr_1) {
  std::initializer_list<double> c1{-10000000000000000000.9999999999999999999,
                                   0.1,
                                   -1,
                                   +0,
                                   -0,
                                   0.0101010101010,
                                   0.000000000001,
                                   -1000.999999999999998,
                                   -1000000.00000000,
                                   -1000000};
  stl::stack<double> st(c1);
  stl::stack<double> st_move(std::move(st));
  for (auto i = c1.end() - 1; i != c1.begin(); --i) {
    ASSERT_EQ(st_move.top(), *i);
    st_move.pop();
  }
}

TEST(test_push_constr, push_1) {
  stl::stack<double> st;
  for (auto i = 0.0; i < 10; ++i) {
    st.push(i);
    ASSERT_EQ(st.top(), i);
  }

  for (auto j = 111.0; j < 2000; ++j) {
    st.push(j);
    ASSERT_EQ(st.top(), j);
  }
}

TEST(test_push_constr, push_2) {
  stl::stack<double> st;
  for (auto i = 0.0; i < 10; ++i) {
    st.push(i);
    ASSERT_EQ(st.top(), i);
  }

  for (auto j = 111.0; j < 2000; ++j) {
    st.push(j);
    ASSERT_EQ(st.top(), j);
  }
}

TEST(test_size, size_1) {
  stl::stack<int> st;
  for (auto i = 0; i < 1000; ++i) {
    ASSERT_EQ(st.size(), i);
    st.push(i);
  }
}

TEST(test_empty, empty_1) {
  stl::stack<int> st;
  int a = 1;
  ASSERT_EQ(st.empty(), 1);
  st.push(a);
  ASSERT_EQ(st.empty(), 0);
  st.pop();
  ASSERT_EQ(st.empty(), 1);
}

TEST(test_swap, swap_1) {
  std::initializer_list<int> c1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::initializer_list<int> c2{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  stl::stack<int> st_1(c1);
  stl::stack<int> st_2(c2);
  st_1.swap(st_2);
  st_2.swap(st_1);
  ASSERT_EQ(st_1.top(), *c2.begin());
  ASSERT_EQ(st_2.top(), *c1.begin());
}

TEST(test_eq, eq_1) {
  std::initializer_list<int> c1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::initializer_list<int> c2{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  stl::stack<int> st_1(c1);
  stl::stack<int> st_2(c2);
  st_1 = std::move(st_2);
  st_2 = std::move(st_1);
  ASSERT_EQ(st_1.top(), *c2.begin());
  ASSERT_EQ(st_2.top(), *c1.begin());
}

TEST(bonus_test, test_emplace) {  //
  stl::stack<int> st_my;

  st_my.emplace_front(100);
  ASSERT_EQ(st_my.top(), 100);
  st_my.emplace_front(200);
  ASSERT_EQ(st_my.top(), 200);
  st_my.emplace_front(1000000);
  ASSERT_EQ(st_my.top(), 1000000);
}

//########################
//#                     ##
//#      QUEUE TEST     ##
//#                     ##
//########################

TEST(test_pop_push, push_and_pop) {
  stl::queue<double> my_q;
  std::queue<double> orig_q;
  double a = 3;
  double a_1 = 5;
  double a_2 = 36;
  double a_3 = 1.000001;
  double a_4 = -0;
  double a_5 = -0.1919191919191919191919;
  double a_6 = 0.111211111;
  my_q.push(a);
  my_q.push(a_1);
  my_q.push(a_2);
  my_q.push(a_3);
  my_q.push(a_4);
  my_q.push(a_5);
  my_q.push(a_6);
  orig_q.push(a);
  orig_q.push(a_1);
  orig_q.push(a_2);
  orig_q.push(a_3);
  orig_q.push(a_4);
  orig_q.push(a_5);
  orig_q.push(a_6);
  for (auto i = 0; i < 7; ++i) {
    ASSERT_EQ(my_q.front(), orig_q.front());
    ASSERT_EQ(my_q.back(), orig_q.back());
    my_q.pop();
    orig_q.pop();
  }
}

TEST(test_constructor_1, constructor_list) {
  std::initializer_list<double> c1{-10000000000000000000.9999999999999999999,
                                   0.1,
                                   -1,
                                   +0,
                                   -0,
                                   0.0101010101010,
                                   0.000000000001,
                                   -1000.999999999999998,
                                   -1000000.00000000,
                                   -1000000};
  stl::queue<double> q_1(c1);
  for (auto i = c1.begin(); i != c1.end() - 1; ++i) {
    ASSERT_EQ(q_1.front(), *i);
    q_1.pop();
  }
}

TEST(test_constructor_2, constructor_copy) {
  std::initializer_list<double> c1{-10000000000000000000.9999999999999999999,
                                   0.1,
                                   -1,
                                   +0,
                                   -0,
                                   0.0101010101010,
                                   0.000000000001,
                                   -1000.999999999999998,
                                   -1000000.00000000,
                                   -1000000};
  stl::queue<double> q_1(c1);
  stl::queue<double> q_2(q_1);
  for (auto i = c1.begin(); i != c1.end() - 1; ++i) {
    ASSERT_EQ(q_1.front(), q_2.front());
    q_1.pop();
    q_2.pop();
  }
}

TEST(test_constructor_3, constructor_move) {
  std::initializer_list<double> c1{1, 2, 3, 4, 5};
  stl::queue<double> q_1(c1);
  stl::queue<double> q_2(std::move(q_1));
  for (auto i = c1.begin(); i != c1.end() - 1; ++i) {
    ASSERT_EQ(q_2.front(), *i);
    q_2.pop();
  }
}

TEST(test_operator, operator_eq) {
  stl::queue<double> q_1;
  stl::queue<double> q_2;
  double a = 1.3;
  double b = 2.6;
  double c = 300.1;
  q_1.push(a);
  q_1.push(b);
  q_1.push(c);
  q_2 = std::move(q_1);
  ASSERT_EQ(q_2.front(), a);
  ASSERT_EQ(q_2.empty(), 0);
  q_2.pop();
  ASSERT_EQ(q_2.front(), b);
  ASSERT_EQ(q_2.empty(), 0);
  q_2.pop();
  ASSERT_EQ(q_2.front(), c);
  ASSERT_EQ(q_2.empty(), 0);
  q_2.pop();
  ASSERT_EQ(q_2.empty(), 1);
  ASSERT_EQ(q_2.size(), 0);
}

TEST(bonus_test_1, test_emplace) {
  stl::queue<int> oq_my;
  oq_my.emplace_back(100);
  oq_my.emplace_back(320);
  ASSERT_EQ(oq_my.front(), 100);
  ASSERT_EQ(oq_my.back(), 320);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
