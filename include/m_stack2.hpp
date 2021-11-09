// Copyright 2021 Max

#ifndef INCLUDE_M_STACK2_HPP_
#define INCLUDE_M_STACK2_HPP_

#include "m_stack1.hpp"
#include <utility>

// Для некопируемых перемещаемых типов
template <typename T>
class Stack2 : public Stack1<T> {
 public:
  template <typename... Args>
  void push_emplace(Args&&... value);
  void push(T& value) = delete;
  void push(T&& value);
  T pop();
  // head is similar, no need in rewriting
};

template <typename T>
template <typename ... Args>
void Stack2<T>::push_emplace(Args&&... value) {
  // Если тип некопируемый
  if ((std::is_copy_constructible<T>::value) ||
      (std::is_copy_assignable<T>::value)) {
    throw std::runtime_error("Expected non copy type for push_emplace");
  }
  auto* elem = new Node<T>{{std::forward<Args>(value)...}, Stack1<T>::Head};
  Stack1<T>::Head = elem;
}

template <typename T>
void Stack2<T>::push(T&& value) {
  // Если тип некопируемый
  if ((std::is_copy_constructible<T>::value) ||
      (std::is_copy_constructible<T>::value)) {
    throw std::runtime_error("Expected non copy type for push");
  }
  auto* elem = new Node<T>{std::forward<T>(value), Stack1<T>::Head};
  Stack1<T>::Head = elem;
}

template <typename T>
T Stack2<T>::pop() {
  if (Stack1<T>::Head == nullptr) {
    throw std::runtime_error("Pop from empty denied");;
  }
  auto * temp = Stack1<T>::Head;
  T val = std::move(Stack1<T>::Head->val);
  Stack1<T>::Head = Stack1<T>::Head->prev;
  delete temp;
  return val;
}

#endif  // INCLUDE_M_STACK2_HPP_
