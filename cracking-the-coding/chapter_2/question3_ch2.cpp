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
  void DeleteMiddleNode(Node *node_ptr);
  Node *get_node(unsigned int position);
  void push_front(int data);
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

void SinglyLinkedList::DeleteMiddleNode(Node *node_ptr) {
  if (node_ptr == nullptr || node_ptr->next == nullptr) {
    return; // Failure
  }
  Node *rm_ptr = node_ptr->next;
  node_ptr->data = rm_ptr->data;
  node_ptr->next = rm_ptr->next;
  delete rm_ptr;
  return;
}

Node *SinglyLinkedList::get_node(unsigned int position) {
  Node *ptr = head;
  for (unsigned int i = 0; i != position; ++i) {
    ptr = ptr->next;
  }
  return ptr;
}

void SinglyLinkedList::push_front(int data) {
  Node *node = new Node(data);
  node->next = head;
  head = node;
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
  list_1.DeleteMiddleNode(list_1.get_node(1)); // ok, list : 10, 5, 5, 20, 5, 10
  list_1.Print();
  list_1.DeleteMiddleNode(list_1.get_node(2)); // ok, list : 10, 5, 20, 5, 10
  list_1.Print();
  list_1.DeleteMiddleNode(list_1.get_node(3)); // ok, list : 10, 5, 20, 10
  list_1.Print();
  list_1.DeleteMiddleNode(list_1.get_node(0)); // works fine for the first node, list : 5, 20, 10
  list_1.Print();
  list_1.DeleteMiddleNode(list_1.get_node(2)); // failure, list must have dummy node at the end in this case
  list_1.Print();
  return 0;
}