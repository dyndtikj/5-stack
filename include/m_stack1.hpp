// Copyright 2021 Max

#ifndef INCLUDE_M_STACK1_HPP_
#define INCLUDE_M_STACK1_HPP_

#include <algorithm>
#include <utility>
#include <stdexcept>

template <typename T>
struct Node {
  T val;
  Node<T>* prev;
};

template <typename T>
class Stack1 {
 public:
  Stack1() = default;
  Stack1(const Stack1&) = delete; // without copy
  Stack1(Stack1&&) noexcept = default;
  ~Stack1();

  auto operator=(const Stack1<T>&) -> Stack1<T>& = delete; // without copy
  auto operator=(Stack1<T>&&) noexcept -> Stack1<T>& = default;

  void push(T&& value);
  void push(const T& value);
  void pop();
  const T& head() const;
  [[nodiscard]]size_t size() const;

 private:
  Node<T>* Head = nullptr;
  size_t _size = 0;
};

template <typename T>
void Stack1<T>::push(T&& value) {
  Node<T>* temp = Head;
  Head = new Node<T>{std::forward<T>(value), temp};
  _size++;
}

template <typename T>
void Stack1<T>::push(const T& value) {
  Node<T>* temp = Head;
  Head = new Node<T>{value, temp};
  _size++;
}

template <typename T>
void Stack1<T>::pop() {
  if (Head == nullptr) {
    throw std::runtime_error("Pop from empty denied");
  }
  Node<T>* temp = Head;
  Head = Head->prev;
  delete temp;
  _size--;
}

template <typename T>
const T& Stack1<T>::head() const {
  if (Head == nullptr) {
    throw std::runtime_error("Stack is empty, can't return head");
  }
  return Head->val;
}

template <typename T>
size_t Stack1<T>::size() const {
  return _size;
}

template <typename T>
Stack1<T>::~Stack1() {
  while (Head != nullptr) {
    pop();
  }
}

#endif // INCLUDE_M_STACK1_HPP_
