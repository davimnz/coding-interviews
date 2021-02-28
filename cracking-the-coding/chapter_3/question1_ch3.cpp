#include <array>
#include <cassert>
#include <iostream>

/*
  Similar to the single stack implementation, we could define a capacity for each stack
  such that capacity[0] + capacity[1] + capacity[2] ==  MAX_SIZE. These values determine the
  offset between the stacks. Hence, the class' methods could modify the specified stack.
  class ThreeStack {
   public: 
    const int capacity[3];
    int size[3];
    std::array <int, MAX_SIZE> items;
    ThreeStack();
    int Pop(int stack_num);
    bool Push(int stack_num, int item);
    int Peek(int stack_num);
    bool IsEmpty(int stack_num);
  }
*/

const int MAX_SIZE = 100;

class SingleStack {
 public:
  const int capacity;
  int size;
  std::array<int, MAX_SIZE> items;      
  SingleStack();
  int Pop();
  bool Push(int item);
  int Peek();
  bool IsEmpty();
  void Print();
};

SingleStack::SingleStack(): capacity(MAX_SIZE), size(0), items() {}

int SingleStack::Pop() {
  if (IsEmpty()) {
    std::cout << "Stack does not have an element at the top. " << 
                 "Returning INT32_MAX as default." << std::endl;  
    return INT32_MAX;
  }
  else {
    --size;
    return items[size];
  }
}

bool SingleStack::Push(int item) {
  if (size == capacity) {
    return false;      
  }
  else {
    items[size] = item;
    ++size;
    return true;
  }
}

int SingleStack::Peek() {
  if (IsEmpty()) {
    std::cout << "Stack does not have an element at the top. "
              << "Returning INT32_MAX as default." << std::endl;
    return INT32_MAX;
  }
  else {
    return items[size - 1];  
  }
}

bool SingleStack::IsEmpty() {
  if (size == 0) {
    return true;  
  }
  return false;
}

void SingleStack::Print() {
  if (IsEmpty()) {
    std::cout << "Empty stack." << std::endl; 
  }
  else {
    for (int i = size - 1; i >= 0; --i) {
      std::cout << items[i] << " ";
    }
    std::cout << std::endl;
  }
}

int main() {
  SingleStack stack;
  assert(stack.IsEmpty() == true);
  assert(stack.Peek() == INT32_MAX); // error message
  assert(stack.Pop() == INT32_MAX); // error message
  assert(stack.Push(10) == true);
  assert(stack.IsEmpty() == false);
  assert(stack.Peek() == 10);
  stack.Print(); 
  assert(stack.Push(20) == true);
  assert(stack.IsEmpty() == false);
  assert(stack.Peek() == 20);
  stack.Print();
  assert(stack.Push(30) == true);
  assert(stack.IsEmpty() == false);
  assert(stack.Peek() == 30);
  stack.Print();
  assert(stack.Pop() == 30);
  assert(stack.Peek() == 20);
  assert(stack.IsEmpty() == false);
  assert(stack.Pop() == 20);
  assert(stack.Peek() == 10);
  assert(stack.IsEmpty() == false);
  assert(stack.Pop() == 10);
  assert(stack.Peek() == INT32_MAX); // error message
  assert(stack.IsEmpty() == true);
  stack.Print();
  for (int i = 0; i != MAX_SIZE; ++i) {
    stack.Push(i);    
  }
  assert(stack.Peek() == 99);
  assert(stack.Push(0) == false); // error message
  assert(stack.Peek() == 99);
  return 0;
}