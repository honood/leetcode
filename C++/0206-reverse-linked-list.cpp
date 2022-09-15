// HoNooD
// 2022.09.16 00:11

// https://leetcode.com/problems/reverse-linked-list/
// https://leetcode.cn/problems/reverse-linked-list/

#include <iostream>

struct ListNode {
  int val;
  ListNode* next;

  // Delegating constructor
  // https://en.cppreference.com/w/cpp/language/constructor#Delegating_constructor
  //
  ListNode(int x, ListNode* next) : val(x), next(next) {}
  explicit ListNode(int x) : ListNode(x, nullptr) {}
  ListNode() : ListNode(0) {}
};

class Solution {
 public:
  ListNode* reverseList(ListNode* head) {
    if (!head) {
      return nullptr;
    }

    ListNode* res = nullptr;
    while (head) {
      ListNode* pre_node = head;
      head = head->next;

      pre_node->next = res;
      res = pre_node;
    }

    return res;
  }
};

static void printList(ListNode* head) {
  if (!head) {
    return;
  }

  while (head) {
    std::cout << head->val << ' ';
    head = head->next;
  }
  std::cout << '\n';
}

int main() {
  ListNode* head = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));

  std::cout << "Before reversing list: ";
  printList(head);

  std::cout << "After reversing list: ";
  head = Solution{}.reverseList(head);
  printList(head);

  while (head) {
    ListNode* tmp = head;
    head = head->next;

    delete tmp;
  }

  return 0;
}