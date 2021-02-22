#include <iostream>
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
  Node *node = new Node(data);
  if (head == nullptr && tail == nullptr) {
    push_front(data);
    return;
  }
  else {
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
  DoublyLinkedList list_1{10, 5, 20, 5, 5, 10, 10};
  list_1.Print();
  return 0;
}