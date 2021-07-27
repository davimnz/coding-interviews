#include <vector>
#include <cassert>
#include <iostream>

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
  int size;
  Stack();
  ~Stack();
  int Pop();
  void Push(int data);
  int Peek();
  bool IsEmpty();
};

class SetOfStacks {
 public:
  int threshold;
  std::vector<Stack> stacks;
  SetOfStacks(int threshold);
  ~SetOfStacks();
  int Pop();
  void Push(int item);
  int Peek();
  bool IsEmpty();
};

Stack::Stack(): top(nullptr), size(0) {}

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
    --size;
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
  ++size;
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

SetOfStacks::SetOfStacks(int threshold): threshold(threshold), stacks() {}

SetOfStacks::~SetOfStacks() {
  
}

int SetOfStacks::Pop() {
  if (IsEmpty()) {
    // Stack is empty. Returning INT32_MAX as a default error value
    return INT32_MAX;
  }
  else {
    std::vector<Stack>::iterator it = stacks.begin();
    while (it + 1 != stacks.end()) {
      ++it;
    }
    int data = it->Pop();
    if (it->IsEmpty()) {
      stacks.erase(it);
    }
    return data;
  }
}

void SetOfStacks::Push(int item) {
  if (IsEmpty()) {
    stacks.push_back(Stack());
    stacks[0].Push(item);
  }
  else {
    std::vector<Stack>::iterator it = stacks.begin();
    while (it->size == threshold) {
      ++it;
    }
    if (it != stacks.end()) {
      it->Push(item);
    }
    else {
      stacks.push_back(Stack());
      it = stacks.begin();
      while (it->size == threshold) {
        ++it;
      }
      it->Push(item);
    }
  }
}

int SetOfStacks::Peek() {
  if (IsEmpty()) {
    // Stack is empty. Returning INT32_MAX as a default error value
    return INT32_MAX;
  }
  else {
    std::vector<Stack>::iterator it = stacks.begin();
    while (it + 1 != stacks.end()) {
      ++it;
    }
    return it->Peek();
  }
}

bool SetOfStacks::IsEmpty() {
  return stacks.empty();
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
  // Testing SetOfStacks methods
  SetOfStacks stacks(4);
  assert(stacks.IsEmpty() == true);
  assert(stacks.Peek() == INT32_MAX);
  assert(stacks.Pop()== INT32_MAX);
  stacks.Push(1);
  assert(stacks.IsEmpty() == false);
  assert(stacks.Peek() == 1);
  stacks.Push(2);
  assert(stacks.IsEmpty() == false);
  assert(stacks.Peek() == 2);
  stacks.Push(3);
  assert(stacks.IsEmpty() == false);
  assert(stacks.Peek() == 3);
  assert(stacks.Pop() == 3);
  assert(stacks.Peek() == 2);
  assert(stacks.IsEmpty() == false);
  assert(stacks.Pop() == 2);
  assert(stacks.Peek() == 1);
  assert(stacks.IsEmpty() == false);
  assert(stacks.Pop() == 1);
  assert(stacks.Peek() == INT32_MAX); // error message
  assert(stacks.IsEmpty() == true);
  return 0;
}