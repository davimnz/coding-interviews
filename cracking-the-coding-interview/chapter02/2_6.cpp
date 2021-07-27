#include <iostream>
#include <cassert>
#include <initializer_list>

class Node {
 public:
  int data;
  Node *next;
  Node *prev;
  Node(int data) : data(data), next(nullptr), prev(nullptr) {};
};

class DoublyLinkedList {
 public:
  Node *head;
  Node *tail;
  DoublyLinkedList() : head(nullptr), tail(nullptr) {};
  DoublyLinkedList(std::initializer_list<int> init);
  ~DoublyLinkedList();
  bool IsPalindrome();
  void push_front(int data);
  void push_back(int data);
  void Print();
};

DoublyLinkedList::DoublyLinkedList(std::initializer_list<int> init) 
    : head(nullptr),
      tail(nullptr) {
  for (const auto element : init) {
    push_back(element);
  }
}

DoublyLinkedList::~DoublyLinkedList() {
  Node *node_ptr = head;
  while (head != tail) {
    node_ptr = head;
    head = head->next;
    node_ptr->next = nullptr;
    head->prev = nullptr;
    delete node_ptr;
  }
  node_ptr = head;
  head = nullptr;
  tail = nullptr;
  delete node_ptr;
}

/*
  Time complexity : O(n)
  Memory complexity : O(1)
*/
bool DoublyLinkedList::IsPalindrome() {
  Node *ptr_1 = head;
  Node *ptr_2 = tail;
  bool palindrome = true;
  while (ptr_1 != ptr_2) {
    if (ptr_1->data < ptr_2->data) {
      palindrome = false;
      break;
    }
    ptr_1 = ptr_1->next;
    ptr_2 = ptr_2->prev;
  }
  return palindrome;
}

void DoublyLinkedList::push_front(int data) {
  Node *node = new Node(data);
  node->next = head;
  if (head != nullptr) {
    head->prev = node;
  }
  node->prev = nullptr;
  head = node;
  if (tail == nullptr) {
    tail = head;
  }
}

void DoublyLinkedList::push_back(int data) {
  if (head == nullptr && tail == nullptr) {
    push_front(data);
    return;
  }
  else {
    Node *node = new Node(data);
    tail->next = node;
    node->prev = tail;
    node->next = nullptr;
    tail = node;
  }
}

void DoublyLinkedList::Print() {
  Node *node_ptr = head;
  if (node_ptr == nullptr) {
    std::cout << "Empty list" << std::endl;
  }
  while (node_ptr != nullptr) {
    std::cout << node_ptr->data << " ";
    node_ptr = node_ptr->next;
  }
  std::cout << std::endl;
}

int main() {
  DoublyLinkedList list_1{1, 3, 5, 5, 3, 1},
                   list_2{5},
                   list_3{1, 2, 1},
                   list_4{1, 1},
                   list_5{0, 1, 2, 3};
  list_1.Print();
  list_2.Print();
  list_3.Print();
  list_4.Print();
  list_5.Print();
  assert(list_1.IsPalindrome() == true); // ok
  assert(list_2.IsPalindrome() == true); // ok
  assert(list_3.IsPalindrome() == true); // ok
  assert(list_4.IsPalindrome() == true); // ok
  assert(list_5.IsPalindrome() == false); // ok
  return 0;
}