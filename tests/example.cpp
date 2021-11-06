// Copyright 2021 Max

#include <gtest/gtest.h>

#include <m_stack1.hpp>
#include <m_stack2.hpp>
#include <stdexcept>

class NonCopEx {
  double data;

 public:
  NonCopEx() = default;
  NonCopEx(const NonCopEx&) = delete;
  NonCopEx(NonCopEx&&) = default;
  NonCopEx(double _data) :data (_data){
  }
  ~NonCopEx() = default;
  auto operator=(NonCopEx&&) -> NonCopEx& = default;
  auto operator=(const NonCopEx&) -> NonCopEx& = delete;
  double getData() const { return this->data; }
};

//--------Testing Stack1 ---------------

TEST(Stack1, Empty) {
  Stack1<int> stack;
  EXPECT_THROW(stack.head(),std::runtime_error);
  EXPECT_THROW(stack.pop(),std::runtime_error);
}



//--------Testing Stack2 ---------------

