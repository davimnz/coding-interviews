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
  DoublyLinkedList(std::initializer_list<int> init, bool reverse);
  ~DoublyLinkedList();
  void push_front(int data);
  void push_back(int data);
  void Print();
};

DoublyLinkedList::DoublyLinkedList(std::initializer_list<int> init, bool reverse) 
    : head(nullptr),
      tail(nullptr) {
  if (reverse) {
    for (const auto element : init) {
      push_front(element);  
    }
  }  
  else {
    for (const auto element : init) {
      push_back(element);
    }
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

/* 
  list_1 must be greater than list_2
  Time complexity : O(n)
  Memory complexity : O(n)
*/
DoublyLinkedList SumListsReverse(DoublyLinkedList &list_1, DoublyLinkedList &list_2) {
  DoublyLinkedList list_3;
  Node *ptr_1 = list_1.head;
  Node *ptr_2 = list_2.head;
  int carry = 0;
  while (ptr_2 != nullptr) {
    int sum = ptr_1->data + ptr_2->data + carry;
    if (sum >= 10) {
      carry = 1;
      list_3.push_back(sum - 10);            
    }
    else {
      carry = 0;  
      list_3.push_back(sum);
    }
    ptr_2 = ptr_2->next;
    ptr_1 = ptr_1->next;
  }
  while (ptr_1 != nullptr) {
    int sum = ptr_1->data + carry;
    if (sum >= 10) {
      carry = 1;
      list_3.push_back(sum - 10);
    }
    else {
      carry = 0;
      list_3.push_back(sum);  
    }
    ptr_1 = ptr_1->next;  
  }
  if (carry == 1) {
    list_3.push_back(carry);
  }
  return list_3;
}

/* 
  list_1 must be greater than list_2
  Time complexity : O(n)
  Memory complexity : O(n)
*/
DoublyLinkedList SumListsForward(DoublyLinkedList &list_1, DoublyLinkedList &list_2) {
  DoublyLinkedList list_3;
  Node *ptr_1 = list_1.tail;
  Node *ptr_2 = list_2.tail;
  int carry = 0;
  while (ptr_2 != nullptr) {
    int sum = ptr_1->data + ptr_2->data + carry;
    if (sum >= 10) {
      carry = 1;
      list_3.push_front(sum - 10);
    }
    else {
      carry = 0;
      list_3.push_front(sum);
    }
    ptr_1 = ptr_1->prev;
    ptr_2 = ptr_2->prev;
  }
  while (ptr_1 != nullptr) {
    int sum = ptr_1->data + carry;
    if (sum >= 10) {
      carry = 1;
      list_3.push_front(sum - 10);
    }
    else {
      carry = 0;
      list_3.push_front(sum);
    }
    ptr_1 = ptr_1->prev;
  }
  if (carry == 1) {
    list_3.push_front(carry);
  }
  return list_3;
}

int main() {
  DoublyLinkedList list_1({6, 1, 7}, true); // reverse
  DoublyLinkedList list_2({2, 9, 5}, true); // reverse
  DoublyLinkedList list_3 = SumListsReverse(list_1, list_2); // ok, 617 + 295 = 912
  list_1.Print();
  list_2.Print();
  list_3.Print();
  DoublyLinkedList list_4({9, 9, 9, 9, 9}, true); // reverse
  DoublyLinkedList list_5({1}, true); // reverse
  DoublyLinkedList list_6 = SumListsReverse(list_4, list_5); // ok, 99999 + 1 = 100000
  list_4.Print();
  list_5.Print();
  list_6.Print();
  DoublyLinkedList list_7({1, 3, 4, 5}, true); // reverse
  DoublyLinkedList list_8({1, 3, 2}, true); // reverse
  DoublyLinkedList list_9 = SumListsReverse(list_7, list_8); // ok, 1345 + 132 = 1477
  list_7.Print();
  list_8.Print();
  list_9.Print();
  DoublyLinkedList list_10({6, 1, 7}, false); // forward
  DoublyLinkedList list_11({2, 9, 5}, false); // forward
  DoublyLinkedList list_12 = SumListsForward(list_10, list_11); // ok, 617 + 295 = 912
  list_10.Print();
  list_11.Print();
  list_12.Print();
  DoublyLinkedList list_13({9, 9, 9, 9, 9}, false); // forward
  DoublyLinkedList list_14({1}, false); // forward
  DoublyLinkedList list_15 = SumListsForward(list_13, list_14); // ok, 99999 + 1 = 100000
  list_13.Print();
  list_14.Print();
  list_15.Print();
  DoublyLinkedList list_16({1, 3, 4, 5}, false); // forward
  DoublyLinkedList list_17({1, 3, 2}, false); // forward
  DoublyLinkedList list_18 = SumListsForward(list_16, list_17); // ok, 1345 + 132 = 1477
  list_16.Print();
  list_17.Print();
  list_18.Print();
  return 0;
}