#include <iostream>
#include <cassert>

class Node {
 public:
  int data;
  Node *next;
  Node(): data(), next(nullptr) {};
  Node(int data): data(data), next(nullptr) {};
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
  void Print();
};

Stack::Stack(): top(nullptr) {}

Stack::~Stack() {
  while (top != nullptr) {
    Node *ptr = top;
    top = top->next;
    delete ptr;  
  }
}

int Stack::Pop() {
  if (IsEmpty()) {
    // Stack is empty. Returning INT32_MAX as a default error value
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

void Stack::Push(int data) {
  Node *node = new Node(data);
  if (IsEmpty()) {
    top = node;
  }
  else {
    node->next = top;
    top = node;
  }
}

int Stack::Peek() {
  if (IsEmpty()) {
    // Stack is empty. Returning INT32_MAX as a default error value
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

void Stack::Print() {
  Node *ptr = top;
  if (top == nullptr) {
    std::cout << "Empty stack." << std::endl;
  }
  else {
    while (ptr != nullptr) {
      std::cout << ptr->data << " ";
      ptr = ptr->next;
    }
    std::cout << std::endl;
  }
}

Stack SortStack(Stack &stack) {
  Stack tmp_stack;
  while (!stack.IsEmpty()) {
    int new_data = stack.Pop();
    int elements_num = 0;
    while (new_data > tmp_stack.Peek()) {
      stack.Push(tmp_stack.Pop());
      ++elements_num;
    }
    tmp_stack.Push(new_data);
    for (int i = 0; i != elements_num; ++i) {
      tmp_stack.Push(stack.Pop());  
    }
  }
  return tmp_stack;
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
  // Testing SortStack
  Stack stack_1;
  stack_1.Push(10);
  stack_1.Push(5);
  stack_1.Push(6);
  stack_1.Push(12);
  stack_1.Push(1);
  stack_1.Push(17);
  stack_1.Push(5);
  stack_1.Push(3); // stack : 3 <- 5 <- 17 <- 1 <- 12 <- 6 <- 5 <- 10
  Stack sort_1 = SortStack(stack_1); // sort : 1 <- 3 <- 5 <- 5 <- 6 <- 10 <- 12 <- 17
  sort_1.Print(); // ok
  Stack stack_2; 
  stack_2.Push(1);
  stack_2.Push(1); // stack : 1 <- 1
  Stack sort_2 = SortStack(stack_2); // sort : 1 <- 1
  sort_2.Print(); // ok 
  Stack stack_3; 
  stack_3.Push(19);
  stack_3.Push(19);
  stack_3.Push(7);
  stack_3.Push(12);
  stack_3.Push(12);
  stack_3.Push(1);
  stack_3.Push(5); // stack : 5 <- 1 <- 12 <- 12 <- 7 <- 19 <- 19
  Stack sort_3 = SortStack(stack_3); // sort : 1 <- 5 <- 7 <- 12 <- 12 <- 19 <- 19
  sort_3.Print(); // ok
  return 0;
}