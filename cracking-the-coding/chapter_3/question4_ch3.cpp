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

class MyQueue {
 public:
  Node *first;
  Node *last;
  Stack main_stack;
  Stack auxiliary_stack;
  MyQueue();
  void Add(int item);
  int Remove();
  int Peek();
  bool IsEmpty();
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

MyQueue::MyQueue(): first(nullptr), last(nullptr), main_stack(), auxiliary_stack() {}

void MyQueue::Add(int item) {
  if (main_stack.IsEmpty()) {
    main_stack.Push(item);
    first = main_stack.top;
    last = main_stack.top;    
  }
  else {
    main_stack.Push(item);
    last = main_stack.top;  
  }
}

int MyQueue::Remove() {
  if (IsEmpty()) {
    // Queue is empty. Returning INT32_MAX as a default error value
    return INT32_MAX;  
  }
  else {
    while (!main_stack.IsEmpty()) {
      auxiliary_stack.Push(main_stack.Pop());    
    }
    int data = auxiliary_stack.Pop();
    while (!auxiliary_stack.IsEmpty()) {
      main_stack.Push(auxiliary_stack.Pop());  
    }
    last = main_stack.top;
    Node *ptr = main_stack.top;
    if (ptr != nullptr) {
      while (ptr->next != nullptr) {
        ptr = ptr->next;  
      }
    }
    first = ptr;
    return data;
  }
}

int MyQueue::Peek() {
  if (first == nullptr) {
    // Queue is empty. Returning INT32_MAX as a default error value
    return INT32_MAX;
  }
  else {
    return first->data;  
  }
}

bool MyQueue::IsEmpty() {
  return main_stack.IsEmpty();
}

int main() {
  Stack stack;
  // Testing Stack methods 
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
  // Testing MyQueue methods
  MyQueue queue;
  assert(queue.IsEmpty() == true);
  assert(queue.Peek() == INT32_MAX); // error message
  assert(queue.Remove() == INT32_MAX);  // error message
  queue.Add(10);
  assert(queue.IsEmpty() == false);
  assert(queue.Peek() == 10);
  queue.Add(20);
  assert(queue.IsEmpty() == false);
  assert(queue.Peek() == 10);
  queue.Add(30);
  assert(queue.IsEmpty() == false);
  assert(queue.Peek() == 10);
  assert(queue.Remove() == 10);
  assert(queue.Peek() == 20);
  assert(queue.IsEmpty() == false);
  assert(queue.Remove() == 20);
  assert(queue.Peek() == 30);
  assert(queue.IsEmpty() == false);
  assert(queue.Remove() == 30);
  assert(queue.Peek() == INT32_MAX); // error message
  assert(queue.IsEmpty() == true);
  return 0;
}