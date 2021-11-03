#include <m_stack1.hpp>
#include <iostream>

int main() {
  Stack1<int> stack;
  stack.push(1);
  stack.push(3);

  std::cout << stack.size();
  return 0;
}
