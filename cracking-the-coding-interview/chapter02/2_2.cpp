#include <iostream>
#include <initializer_list>

class Node {
 public:
  int data;
  Node *next;
  Node(int data) : data(data), next(nullptr){};
};

class SinglyLinkedList {
 public:
  Node *head;
  SinglyLinkedList() : head(nullptr){};
  SinglyLinkedList(std::initializer_list<int> init);
  ~SinglyLinkedList();
  void push_front(int data);
  int ReturnKthToLast(unsigned int k);
  void Print();
};

SinglyLinkedList::SinglyLinkedList(std::initializer_list<int> init) : head(nullptr) {
  for (const auto element : init) {
    push_front(element);
  }
}

SinglyLinkedList::~SinglyLinkedList() {
  Node *node_ptr = head;
  while (head != nullptr) {
    node_ptr = head;
    head = head->next;
    delete node_ptr;
  }
}

void SinglyLinkedList::push_front(int data) {
  Node *node = new Node(data);
  node->next = head;
  head = node;
}
/*
  Time complexity : O(n)
  Memory complexity : O(1)
*/ 
int SinglyLinkedList::ReturnKthToLast(unsigned int k) {
  Node *ptr_1 = head;
  Node *ptr_2 = head;
  for (unsigned int i = 0; i != k; ++i) {
    if (ptr_2 == nullptr) {
      break;  
    }
    ptr_2 = ptr_2->next;  
  }
  if (ptr_2 == nullptr) {
    std::cout << "K is out of range. Returning INT32_MAX as default error result." << std::endl;
    return INT32_MAX; // Corner case
  }
  while (ptr_2->next != nullptr) { // "Runner" technique
    ptr_1 = ptr_1->next;
    ptr_2 = ptr_2->next;
  }
  return ptr_1->data;
}

void SinglyLinkedList::Print() {
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
  // SinglyLinkedList only supports front insertion. Therefore, the elements in the
  // initialization list will be in reverse order in the list.
  SinglyLinkedList list_1{10, 5, 20, 5, 5, 10, 10}; // list_1 : 10, 10, 5, 5, 20, 5, 10
  list_1.Print();
  std::cout << list_1.ReturnKthToLast(0) << std::endl; // ok
  std::cout << list_1.ReturnKthToLast(1) << std::endl; // ok
  std::cout << list_1.ReturnKthToLast(2) << std::endl; // ok
  std::cout << list_1.ReturnKthToLast(3) << std::endl; // ok
  std::cout << list_1.ReturnKthToLast(4) << std::endl; // ok
  std::cout << list_1.ReturnKthToLast(5) << std::endl; // ok
  std::cout << list_1.ReturnKthToLast(6) << std::endl; // ok
  std::cout << list_1.ReturnKthToLast(7) << std::endl; // ok
  return 0;
}