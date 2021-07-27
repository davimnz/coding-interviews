#include <iostream>
#include <cassert>
#include <unordered_set>
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
  Node *tail;
  SinglyLinkedList() : head(nullptr), tail(nullptr) {};
  SinglyLinkedList(std::initializer_list<int> init);
  ~SinglyLinkedList();
  void push_front(int data);
};

class CircularLinkedList : public SinglyLinkedList {
 public:
  int loop_node; // This info cannot be used in the solution. It is used only in print method. 
  CircularLinkedList(std::initializer_list<int>, int loop_node);
  ~CircularLinkedList();
  void Print();
};

SinglyLinkedList::SinglyLinkedList(std::initializer_list<int> init)
    : head(nullptr),
      tail(nullptr) {
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
    std::cout << "Hello" << std::endl;
  }
  tail = nullptr;
}

void SinglyLinkedList::push_front(int data) {
  Node *node = new Node(data);
  node->next = head;
  if (head == nullptr && tail == nullptr) {
    head = node;
    tail = node;
  }
  else {
    head = node;  
  }
}

CircularLinkedList::CircularLinkedList(std::initializer_list<int> init, int loop_node)
    : loop_node(loop_node) {
  std::initializer_list<int>::iterator it = init.begin();
  while (it != init.end()) {
    push_front(*it);
    ++it;
  }
  Node *node_ptr = head;
  for (int i = 0; i != loop_node; ++i) {
    node_ptr = node_ptr->next;
  }
  tail->next = node_ptr;
}

CircularLinkedList::~CircularLinkedList() {
  Node *node_ptr = head;
  while (head != nullptr) {
    node_ptr = head;
    if (head == tail) {
      head = nullptr;
    }
    else {
      head = head->next;
    }
    delete node_ptr;
  }
  tail = nullptr;
}

void CircularLinkedList::Print() {
  Node *ptr_1 = head;
  Node *ptr_2 = head;
  for (int i = 0; i != loop_node; ++i) {
    std::cout << ptr_2->data << " ";
    ptr_2 = ptr_2->next;
  }
  ptr_1 = ptr_2;
  bool end = false;
  while (!end) {
    std::cout << ptr_1->data << " ";
    ptr_1 = ptr_1->next;
    if (ptr_1 == ptr_2) {
      std::cout << ptr_1->data << " " << std::endl;
      end = true;
    }
  }
}

/*
  Time complexity : O(n)
  Memory complexity : O(n)
  Optimal solution has O(1) memory complexity.
*/
Node *LoopBegin(CircularLinkedList &list) {
  std::unordered_set<Node*> Nodes;
  bool not_found = true;
  Node *ptr = list.head;
  while (not_found) {
    if (Nodes.find(ptr) == Nodes.end()) {
      Nodes.insert(ptr);
      ptr = ptr->next;
    }
    else {
      not_found = false;
    }
  }
  return ptr;    
}

int main() {
  // SinglyLinkedList only supports front insertion. Therefore, the elements in the
  // initialization list will be in reverse order in the list.
  CircularLinkedList list_1({1, 2, 3, 4, 5, 6}, 3); // list : 6 -> 5 -> 4 -> 3 -> 2 -> 1 -> 3
  CircularLinkedList list_2({1, 2, 3, 4, 5}, 1); // list : 5 -> 4 -> 3 -> 2 -> 1 -> 4
  CircularLinkedList list_3({1, 2, 3, 4, 6}, 2); // list : 6 -> 4 -> 3 -> 2 -> 1 -> 3
  list_1.Print();
  list_2.Print();
  list_3.Print();
  Node *node_1 = LoopBegin(list_1);
  Node *node_2 = LoopBegin(list_2);
  Node *node_3 = LoopBegin(list_3);
  assert(node_1->data == 3); // ok
  assert(node_2->data == 4); // ok
  assert(node_3->data == 3); // ok
  return 0;
}