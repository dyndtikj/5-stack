// Copyright 2021 Max

#include <gtest/gtest.h>

#include <m_stack1.hpp>
#include <m_stack2.hpp>
#include <stdexcept>

//--------Testing Stack1 ---------------

TEST(Stack1, Empty) {
  Stack1<int> stack;
  EXPECT_THROW(stack.head(),std::runtime_error);
  EXPECT_THROW(stack.pop(),std::runtime_error);
}

TEST(Stack1, PushValue) {
  Stack1<int> stack1;
  stack1.push(5);
  EXPECT_EQ(stack1.head(), 5);
  Stack1<std::string> stack2;
  std::string str{"ABCD"};
  stack2.push(std::move(str));
  EXPECT_EQ(stack2.head(), "ABCD");
  int a = 10;
  stack1.push(a);
  EXPECT_EQ(stack1.head(), a);
}

TEST(Stack1, PopValues) {
  Stack1<int> stack;
  stack.push(15);
  stack.push(20);
  int a = 25;
  int b = 30;
  stack.push(a);
  stack.push(b);
  stack.pop();
  EXPECT_EQ(stack.head(), 25);
  size_t size = stack.size();
  for (size_t i = 0; i < size; ++i) {
    EXPECT_NO_THROW(stack.pop());
  }
  EXPECT_THROW(stack.head(),std::runtime_error);
  EXPECT_THROW(stack.pop(),std::runtime_error);
}
// Некопируемый перемещаемый шаблон класса
TEST(Stack1, MovableClass) {
  EXPECT_TRUE(std::is_move_constructible<Stack1<int>>::value);
  EXPECT_TRUE(std::is_move_assignable<Stack1<int>>::value);
  EXPECT_TRUE(std::is_move_constructible<Stack1<std::string>>::value);
  EXPECT_TRUE(std::is_move_assignable<Stack1<std::string>>::value);
}
TEST(Stack, NonCopyedClass) {
  EXPECT_FALSE(std::is_copy_constructible<Stack1<int>>::value);
  EXPECT_FALSE(std::is_copy_assignable<Stack1<int>>::value);
  EXPECT_FALSE(std::is_copy_constructible<Stack1<std::string>>::value);
  EXPECT_FALSE(std::is_copy_assignable<Stack1<std::string>>::value);
}
//--------Testing Stack2 ---------------

