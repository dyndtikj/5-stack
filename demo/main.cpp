#include <m_stack1.hpp>
#include <iostream>
#include <stdexcept>

int main() {
  Stack1<int> stack;

  stack.push(1);
  stack.push(3);
  int value = 10;
  stack.push(value);

  std::cout << stack.head() << " "<< stack.size() << std::endl;
  stack.pop();
  std::cout << stack.head() << " "<< stack.size() << std::endl;
  stack.pop();
  std::cout << stack.head() << " "<< stack.size() << std::endl;
  stack.pop();

  try {
    std::cout << stack.head() << " " << stack.size() << std::endl;
  } catch (std::runtime_error& ex){
    std::cerr << ex.what();
  }

  return 0;
}
