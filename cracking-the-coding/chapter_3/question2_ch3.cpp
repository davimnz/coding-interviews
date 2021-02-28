#include <iostream>
#include <cassert>

class Node {
 public:
  int data;
  Node *next;
  int substack_min;
  Node(): data(), next(nullptr), substack_min() {};
  Node(int data): data(data), next(nullptr), substack_min() {};
};

class Stack {
 public:
  Node *top;
  Stack();
  ~Stack();
  int Pop();
  void Push(int data);
  int Peek();
  bool IsEmpty();
  int Minimum();
};

Stack::Stack(): top(nullptr) {}

Stack::~Stack() {
  while (top != nullptr) {
    Node *ptr = top;
    top = top->next;
    delete ptr;  
  }
}

/*
  Time complexity : O(1)
*/
int Stack::Pop() {
  if (IsEmpty()) {
    std::cout << "Stack is empty. Returning INT32_MAX as a default error value." << std::endl;
    return INT32_MAX;
  }
  else {
    Node *ptr = top;
    int data = top->data;
    top = top->next;
    delete ptr;
    return data;
  }
}

/*
  Time complexity : O(1)
*/
void Stack::Push(int data) {
  Node *node = new Node(data);
  if (IsEmpty()) {
    top = node;
    node->substack_min = node->data;
  }
  else {
    if (node->data < top->substack_min) {
      node->substack_min = node->data; 
    }
    else {
      node->substack_min = top->substack_min;  
    }
    node->next = top;
    top = node;
  }
}

int Stack::Peek() {
  if (IsEmpty()) {
    std::cout << "Stack is empty. Returning INT32_MAX as a default error value." << std::endl;
    return INT32_MAX;  
  }  
  else {
    return top->data;  
  }
}

bool Stack::IsEmpty() {
  if (top == nullptr) {
    return true;  
  }
  return false;  
}

/*
  Time complexity : O(1)
*/
int Stack::Minimum() {
  if (IsEmpty()) {
    std::cout << "Stack is empty. Returning INT32_MAX as a default error value." << std::endl;
    return INT32_MAX;  
  }
  else {
    return top->substack_min;
  }  
}

int main() {
  Stack stack;
  // Testing methods
  assert(stack.IsEmpty() == true);
  assert(stack.Peek() == INT32_MAX); // error message
  assert(stack.Pop() == INT32_MAX);  // error message
  stack.Push(10);
  assert(stack.IsEmpty() == false);
  assert(stack.Peek() == 10);
  stack.Push(20);
  assert(stack.IsEmpty() == false);
  assert(stack.Peek() == 20);
  stack.Push(30);
  assert(stack.IsEmpty() == false);
  assert(stack.Peek() == 30);
  assert(stack.Pop() == 30);
  assert(stack.Peek() == 20);
  assert(stack.IsEmpty() == false);
  assert(stack.Pop() == 20);
  assert(stack.Peek() == 10);
  assert(stack.IsEmpty() == false);
  assert(stack.Pop() == 10);
  assert(stack.Peek() == INT32_MAX); // error message
  assert(stack.IsEmpty() == true);
  // Testing minimum method
  stack.Push(6);
  stack.Push(3);
  stack.Push(1);
  stack.Push(2);
  stack.Push(2);
  stack.Push(0);
  stack.Push(7);
  assert(stack.Minimum() == 0); // ok, stack : 7 <- 0 <- 2 <- 2 <- 1 <- 3 <- 6
  assert(stack.Pop() == 7);
  assert(stack.Minimum() == 0); // ok, stack : 0 <- 2 <- 2 <- 1 <- 3 <- 6
  assert(stack.Pop() == 0);
  assert(stack.Minimum() == 1); // ok, stack : 2 <- 2 <- 1 <- 3 <- 6
  assert(stack.Pop() == 2);
  assert(stack.Minimum() == 1); // ok, stack : 2 <- 1 <- 3 <- 6
  assert(stack.Pop() == 2);
  assert(stack.Minimum() == 1); // ok, stack : 1 <- 3 <- 6
  assert(stack.Pop() == 1);
  assert(stack.Minimum() == 3); // ok, stack : 3 <- 6
  assert(stack.Pop() == 3);
  assert(stack.Minimum() == 6); // ok, stack : 6
  assert(stack.Pop() == 6);
  assert(stack.IsEmpty() == true);
  return 0;
}