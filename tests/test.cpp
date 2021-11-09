// Copyright 2021 Max

#include <gtest/gtest.h>
#include <stack>
#include <m_stack1.hpp>
#include <m_stack2.hpp>
#include <stdexcept>

//--------Testing Stack1 ---------------

TEST(Stack1, Empty) {
  Stack1<int> stack;
  EXPECT_THROW(stack.head(),std::runtime_error);
  EXPECT_THROW(stack.pop(),std::runtime_error);
}

TEST(Stack1, Push) {
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

TEST(Stack1, Pop) {
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
TEST(Stack1, Movable) {
  EXPECT_TRUE(std::is_move_constructible<Stack1<int>>::value);
  EXPECT_TRUE(std::is_move_assignable<Stack1<int>>::value);
  EXPECT_TRUE(std::is_move_constructible<Stack1<std::string>>::value);
  EXPECT_TRUE(std::is_move_assignable<Stack1<std::string>>::value);
}
TEST(Stack1, No_copy) {
  EXPECT_FALSE(std::is_copy_constructible<Stack1<int>>::value);
  EXPECT_FALSE(std::is_copy_assignable<Stack1<int>>::value);
  EXPECT_FALSE(std::is_copy_constructible<Stack1<std::string>>::value);
  EXPECT_FALSE(std::is_copy_assignable<Stack1<std::string>>::value);
}
//--------Testing Stack2 ---------------

// Создадим некоторый класс для тестирования стэка из 2 задания

struct Test_class{
  double a;
  char b;
  Test_class(const Test_class &T1) = delete;

  Test_class(Test_class&& T1) : a(T1.a),b(T1.b) {
    std::cout << "Move constructed" << std::endl;
  }

  Test_class(const double& a1, const char& b1): a(a1), b(b1){
      std::cout << "was constructed" << std::endl;
  }

  auto operator=(const Test_class&) -> Test_class& = delete; // without copy
  auto operator=(Test_class &&) noexcept -> Test_class& = default;

  ~Test_class(){
    std::cout << "was destructed" << std::endl;
  }
};

TEST(Test_class, Is_correct_for_stack2) {
  EXPECT_TRUE(std::is_move_constructible<Test_class>::value);
  EXPECT_TRUE(std::is_move_assignable<Test_class>::value);
  EXPECT_FALSE(std::is_copy_constructible<Test_class>::value);
  EXPECT_FALSE(std::is_copy_assignable<Test_class>::value);
}

TEST(Stack2, Push_pop){
  Stack2<Test_class> st;
  st.push(Test_class(1.2,'a'));
  EXPECT_EQ(st.head().a, 1.2);
  st.push(Test_class(2.2, 'b'));
  EXPECT_EQ(st.head().a, 2.2);
  EXPECT_EQ(st.head().b, 'b');
  EXPECT_EQ(st.pop().b, 'b');
  EXPECT_EQ(st.head().b, 'a');
  EXPECT_EQ(st.pop().a, 1.2);
  EXPECT_THROW(st.pop(),std::runtime_error);
}

TEST(Stack2, Push_emplace){
  Stack2<Test_class> st;
  st.push_emplace(2.2, 'b');
  EXPECT_EQ(st.head().a, 2.2);
  EXPECT_EQ(st.head().b, 'b');
  st.push_emplace(3.2, 'c');
  EXPECT_EQ(st.head().a, 3.2);
  EXPECT_EQ(st.head().b, 'c');
  st.pop();
  EXPECT_EQ(st.head().a, 2.2);
  EXPECT_EQ(st.head().b, 'b');
}

