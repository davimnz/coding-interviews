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

void SwapNode(Node *node_1, Node *node_2) {
  int tmp = node_1->data;
  node_1->data = node_2->data;
  node_2->data = tmp;
}

/*
  Time complexity : O(n)
  Memory complexity : O(1)
*/
void Partition(DoublyLinkedList &list, int value) {
  Node *ptr_1 = list.head;
  Node *ptr_2 = list.tail;
  while (ptr_1 < ptr_2) {
    if (ptr_1->data >= value) {
      while (ptr_2->data >= value && ptr_2 > ptr_1) {
        ptr_2 = ptr_2->prev;
      }
      SwapNode(ptr_1, ptr_2);
    }
    ptr_1 = ptr_1->next; 
  }
}

int main() {
  DoublyLinkedList list_1{3, 5, 8, 5, 10, 2, 1};
  DoublyLinkedList list_2{3, 6, 1, 1, 11, 1, 2, 2};
  list_1.Print();
  Partition(list_1, 5); // ok
  list_1.Print();
  Partition(list_1, 3); // ok
  list_1.Print();
  Partition(list_1, 8); // ok
  list_1.Print();
  list_2.Print();
  Partition(list_2, 2); // ok
  list_2.Print();
  Partition(list_2, 11); // ok
  list_2.Print();
  Partition(list_2, 6); // ok
  list_2.Print();
  return 0;
}