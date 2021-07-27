#include <iostream>
#include <initializer_list>
#include <unordered_set>

class Node {
 public:
  int data;
  Node *next;
  Node(int data): data(data), next(nullptr) {};
};

class SinglyLinkedList {
 public:
  Node *head;
  SinglyLinkedList(): head(nullptr) {};
  SinglyLinkedList(std::initializer_list<int> init);
  ~SinglyLinkedList();
  void push_front(int data);
  void RemoveDuplicatesWithHash();
  void RemoveDuplicatesWithoutExtraMem();
  void Print();
};

SinglyLinkedList::SinglyLinkedList(std::initializer_list<int> init): head(nullptr) {
  for (const auto element : init) {
    push_front(element);
  }
}

SinglyLinkedList::~SinglyLinkedList()
{
  Node *node_ptr = head;
  while (head != nullptr)
  {
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
  Memory complexity : O(n)
*/
void SinglyLinkedList::RemoveDuplicatesWithHash() {
  std::unordered_set<int> in_list;
  Node *previous_ptr = nullptr;
  Node *current_ptr = head;
  while (current_ptr != nullptr) {
    if (in_list.count(current_ptr->data) == 0) { // O(1) on average
      in_list.insert(current_ptr->data); // O(1) on average
      previous_ptr = current_ptr;
      current_ptr = current_ptr->next;
    }
    else {
      previous_ptr->next = current_ptr->next;
      delete current_ptr;
      current_ptr = previous_ptr->next;
    }
  } 
}

/*
  Time complexity : O(n^2)
  Memory complexity: O(1)
*/
void SinglyLinkedList::RemoveDuplicatesWithoutExtraMem() {
  Node *node_ptr = head;
  while (node_ptr != nullptr) {
    Node *previous_ptr = node_ptr;
    Node *rm_ptr = node_ptr->next;
    while (rm_ptr != nullptr) {
      if (rm_ptr->data == node_ptr->data) {
        previous_ptr->next = rm_ptr->next;
        delete rm_ptr;
        rm_ptr = previous_ptr->next;
      }
      else {
        previous_ptr = previous_ptr->next;
        rm_ptr = rm_ptr->next;
      }
    }
    node_ptr = node_ptr->next;
  }
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
  SinglyLinkedList list_1{10, 5, 20, 5, 5, 10, 10},
                   list_2{10, 5, 20, 10, 10, 10},
                   list_3{},
                   list_4{1, 1, 0, 0, 5, 5, 4, 4, -1, -20},
                   list_5{1, 1, 1, 1, 0, 1, 1, 1};
  list_1.Print();
  list_1.RemoveDuplicatesWithHash(); // ok
  list_1.Print();
  list_2.Print();
  list_2.RemoveDuplicatesWithoutExtraMem(); // ok 
  list_2.Print();
  list_3.RemoveDuplicatesWithHash(); // ok, function supports null input
  list_3.RemoveDuplicatesWithoutExtraMem(); // ok, function supports null input
  list_4.Print();
  list_4.RemoveDuplicatesWithHash(); // ok
  list_4.Print();
  list_5.Print();
  list_5.RemoveDuplicatesWithoutExtraMem(); // ok
  list_5.Print();
  return 0;
}