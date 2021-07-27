#include <iostream>
#include <vector>
#include <cassert>
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
  int get_size() const;
  void push_front(int data);
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
  }
  tail = nullptr;
}

int SinglyLinkedList::get_size() const {
  int size = 0;
  if (head == nullptr && tail == nullptr) {
    return size;
  }
  else {
    size = 1;
    Node *ptr = head;
    while (ptr->next != nullptr) {
      ptr = ptr->next;
      ++size; 
    }
  }
  return size;
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

/*
  Intersection point cannot be the end of the lists. Otherwise, the lists would be the same object.
  init_1 must be greater than init_2.
*/
std::vector<SinglyLinkedList*> CreateIntersectionLists(std::initializer_list<int> init_1, 
                                                      std::initializer_list<int> init_2, 
                                                      int intersection) {
  SinglyLinkedList *list_1 = new SinglyLinkedList();
  SinglyLinkedList *list_2 = new SinglyLinkedList();
  std::initializer_list<int>::const_iterator it_1 = init_1.begin();
  std::initializer_list<int>::const_iterator it_2 = init_2.begin();
  for (int i = 0; i != intersection + 1; ++i) {
    list_1->push_front(*it_1);
    ++it_1;
    ++it_2;
  }
  list_2->head = list_1->head;
  list_2->tail = list_1->tail;
  while (it_1 != init_1.end()) {
    list_1->push_front(*it_1);
    ++it_1;
  }
  while (it_2 != init_2.end()) {
    list_2->push_front(*it_2);
    ++it_2;
  }
  std::vector<SinglyLinkedList*> Lists{list_1, list_2};
  return Lists;
}

void DeleteIntersectionLists(std::vector<SinglyLinkedList*> &lists, int intersection) {
  Node *ptr_1 = lists[0]->head;
  Node *ptr_2 = ptr_1;
  for (int i = 0; i != intersection + 1; ++i) {
    ptr_2 = ptr_2->next;
  }
  while (ptr_2 != lists[0]->tail) {
    ptr_1 = ptr_1->next;
    ptr_2 = ptr_2->next;
  }
  ptr_1->next = nullptr;
  lists[0]->tail = ptr_1;
  delete lists[0];
  delete lists[1];
}

/*
  Time complexity : O(A + B)
                    A : list_1 length
                    B : list_2 length
  Memory complexity : O(1)
  list_1 must be greater than list_2                  
*/
int FindIntersection(const SinglyLinkedList &list_1, const SinglyLinkedList &list_2) {
  if (list_1.tail == list_2.tail) {
    int size_difference = list_1.get_size() - list_2.get_size();
    Node *ptr_1 = list_1.head;
    Node *ptr_2 = list_2.head;
    for(int i = 0; i != size_difference; ++i) {
      ptr_1 = ptr_1->next;
    }
    while (ptr_1 != ptr_2) {
      ptr_1 = ptr_1->next;
      ptr_2 = ptr_2->next;
    }
    return ptr_1->data;
  }
  else {
    std::cout << "Lists do not intersect. Returning INT32_MAX as default." << std::endl;
    return INT32_MAX;
  }
}

int main() {
  // SinglyLinkedList only supports front insertion. Therefore, the elements in the
  // initialization list will be in reverse order in the list.
  std::vector<SinglyLinkedList*> IntersectionLists_1 = CreateIntersectionLists(
      {1, 2, 5, 8, 9}, // list : 9 -> 8 -> 5 -> 2 -> 1
      {1, 2, 5, 3}, // list : 3 -> 5 -> 2 -> 1
      2); // intersection : 5
  std::vector<SinglyLinkedList *> IntersectionLists_2 = CreateIntersectionLists(
      {1, 3, 5}, // list : 1 -> 3 -> 5
      {1, 3, 5}, // list : 1 -> 3 -> 5
      1); // intersection : 3
  IntersectionLists_1[0]->Print();
  IntersectionLists_1[1]->Print();
  IntersectionLists_2[0]->Print();
  IntersectionLists_2[1]->Print();
  assert(FindIntersection(*IntersectionLists_1[0], *IntersectionLists_1[1]) == 5); // ok 
  assert(FindIntersection(*IntersectionLists_2[0], *IntersectionLists_2[1]) == 3); // ok
  assert(FindIntersection(*IntersectionLists_1[0], *IntersectionLists_2[0]) == INT32_MAX); // ok
  assert(FindIntersection(*IntersectionLists_1[0], *IntersectionLists_2[1]) == INT32_MAX); // ok
  assert(FindIntersection(*IntersectionLists_1[1], *IntersectionLists_2[0]) == INT32_MAX); // ok
  assert(FindIntersection(*IntersectionLists_1[1], *IntersectionLists_2[1]) == INT32_MAX); // ok
  DeleteIntersectionLists(IntersectionLists_1, 2);
  DeleteIntersectionLists(IntersectionLists_2, 1);
  return 0;
}