// Copyright 2021 Slava-100 <svat.strel.2001@gmail.com>

#include <gtest/gtest.h>

#include <type_traits>

#include "Stack.hpp"

// class for stack testing
class Point {
 public:
  Point() : _x(0), _y(0) {}
  Point(int x, int y) : _x(x), _y(y) {}

  Point(Point &&other) noexcept {
    _x = other._x;
    _y = other._y;

    other._x = 0;
    other._y = 0;
  }

  Point(const Point &) = default;

  ~Point() = default;

  int x() const { return _x; }

  int y() const { return _y; }

 private:
  int _x;
  int _y;
};

TEST(StackTest, PushLValue) {
  const int elements_count = 123;
  Stack<int> s;

  for (int i = 0; i != elements_count; ++i) s.push(i);

  for (int i = elements_count - 1; i != -1; --i) {
    if (s.empty())
      FAIL() << "elements count in stack mismatch with elements count pushed";
    auto el = s.pop();
    EXPECT_EQ(el, i);
  }
  EXPECT_TRUE(s.empty());
}

TEST(StackTest, PushRValue) {
  const int elements_count = 123;
  Stack<Point> s;

  for (int i = 0; i != elements_count; ++i) s.push(Point(i, 2 * i));
  for (int i = elements_count - 1; i != -1; --i) {
    if (s.empty())
      FAIL() << "elements count in stack mismatch with elements count pushed";
    auto el = s.pop();
    EXPECT_EQ(el.x(), i);
    EXPECT_EQ(el.y(), 2 * i);
  }
  EXPECT_TRUE(s.empty());
}

TEST(StackTest, Emplace) {
  const int elements_count = 123;
  Stack<Point> s;

  for (int i = 0; i != elements_count; ++i) s.emplace(i, 2 * i);
  for (int i = elements_count - 1; i != -1; --i) {
    if (s.empty())
      FAIL() << "elements count in stack mismatch with elements count pushed";
    auto el = s.pop();
    EXPECT_EQ(el.x(), i);
    EXPECT_EQ(el.y(), 2 * i);
  }
  EXPECT_TRUE(s.empty());
}

TEST(StackTest, Size) {
  Stack<int> s;
  EXPECT_EQ(0, s.size());
  const int elem = 123;
  s.push(elem);
  EXPECT_EQ(1, s.size());
}

TEST(StackTest, Empty) {
  Stack<int> s;
  EXPECT_TRUE(s.empty());
  const int elem = 123;
  s.push(elem);
  EXPECT_FALSE(s.empty());
}

TEST(StackTest, MoveConstructor) {
  EXPECT_TRUE(std::is_move_constructible_v<Stack<int>>);
  Stack<int> s1;
  const int s1_elements_count = 123;

  for (int i = 0; i != s1_elements_count; ++i) s1.push(i);

  Stack<int> s2(std::move(s1));
  EXPECT_EQ(s1_elements_count, s2.size());

  for (int i = s1_elements_count - 1; i != -1; --i) {
    if (s2.empty())
      FAIL() << "elements count in stack mismatch with elements count pushed";
    auto el = s2.pop();
    EXPECT_EQ(el, i);
  }
}

TEST(StackTest, MoveAssign) {
  EXPECT_TRUE(std::is_move_assignable_v<Stack<int>>);
  Stack<int> s1;
  const int s1_elements_count = 12;

  Stack<int> s2;
  const int s2_elements_count = 21;

  for (int i = 0; i != s1_elements_count; ++i) s1.push(i);

  for (int i = 0; i != s2_elements_count; ++i) s2.push(i);

  s2 = std::move(s1);
  EXPECT_EQ(s2.size(), s1_elements_count);

  for (int i = s1_elements_count - 1; i != -1; --i) {
    if (s2.empty())
      FAIL() << "elements count in stack mismatch with elements count pushed";
    auto el = s2.pop();
    EXPECT_EQ(el, i);
  }
}

TEST(ErrorHandling, PopFromEmptyStack) {
  Stack<int> s;
  EXPECT_THROW(s.pop(), std::runtime_error);
}
