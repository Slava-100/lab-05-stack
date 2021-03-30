#include <Stack.hpp>
#include <iostream>

class Point {
 public:
  Point(int x, int y) : _x(x), _y(y) {}
  int x() const { return _x; }
  int y() const { return _y; }
 private:
  int _x;
  int _y;
};

int main() {
  Stack<Point> s;
  for (int i = 0; i != 10; ++i)
    s.emplace(i, 2 * i);
  while (!s.empty()) {
    auto point = s.pop();
    std::cout << "x: " << point.x() << " y: " << point.y() << std::endl;
  }
  return 0;
}

