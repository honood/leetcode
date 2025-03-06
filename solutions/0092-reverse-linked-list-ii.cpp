// HoNooD
// 2022.09.16 00:52

// https://leetcode.com/problems/reverse-linked-list-ii/
// https://leetcode.cn/problems/reverse-linked-list-ii/

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
  ListNode* reverseBetween(ListNode* head, int left, int right) {
    if (!head) {
      return nullptr;
    }

    if (left < 0 || right < 0 || left >= right) {
      return head;
    }

    assert(left < right && left >= 0);

    ListNode* span_head = head;
    ListNode* pre_span_head = span_head;
    right = right - left + 1;
    while (--left > 0 && nullptr != span_head) {
      pre_span_head = span_head;
      span_head = span_head->next;
    }

    if (!span_head || !span_head->next) {
      return head;
    }

    ListNode* reversed_span_head = nullptr;
    ListNode* reversed_span_tail = span_head;
    while (right-- > 0 && nullptr != span_head) {
      ListNode* pre_node = span_head;
      span_head = span_head->next;

      pre_node->next = reversed_span_head;
      reversed_span_head = pre_node;
    }

    if (pre_span_head != reversed_span_tail) {
      pre_span_head->next = reversed_span_head;
    } else {
      head = reversed_span_head;
    }

    reversed_span_tail->next = span_head;

    return head;
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
  head = Solution{}.reverseBetween(head, 1, 4);
  printList(head);

  while (head) {
    ListNode* tmp = head;
    head = head->next;

    delete tmp;
  }

  return 0;
}
