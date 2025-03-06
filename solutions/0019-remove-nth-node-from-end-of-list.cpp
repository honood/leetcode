// HoNooD
// 2022.06.10 20:23

// https://leetcode.cn/problems/remove-nth-node-from-end-of-list/

#include <iostream>

struct ListNode {
  int val;
  ListNode* next;

  ListNode() : ListNode(0) {}
  explicit ListNode(int x) : ListNode(x, nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}

  ~ListNode() {
    std::cout << __PRETTY_FUNCTION__ << ": " << val << std::endl;
  }
};

void print_list(ListNode* head) {
  if (!head) {
    return;
  }

  ListNode* curr = head;
  while (curr) {
    std::cout << curr->val << (curr->next == nullptr ? "\n" : " -> ");
    curr = curr->next;
  }
}

void destroy_list(ListNode* head) {
  if (!head) {
    return;
  }

  ListNode* to_del = head;
  while (to_del) {
    head = to_del->next;
    delete to_del;
    to_del = head;
  }
}

class Solution {
public:
  ListNode* removeNthFromEnd(ListNode* head, int n) {
    if (n <= 0) {
      return head;
    }

    ListNode* rear = head;
    ListNode* front = head;

    while (n--) {
      // n > list's size
      // or
      // head is nullptr
      if (!front) {
        return head;
      }

      front = front->next;
    }

    // n == list's size
    if (!front) {
      head = head->next;
      delete rear;

      return head;
    }

    while (front->next) {
      front = front->next;
      rear = rear->next;
    }

    ListNode* to_del = rear->next;
    rear->next = to_del->next;
    delete to_del;

    return head;
  }
};

int main(int argc, char* argv[]) {
  ListNode* head = new ListNode(
    1,
    new ListNode(
      2,
      new ListNode(
        3,
        new ListNode(
          4,
          new ListNode(5)
        )
      )
    )
  );

  print_list(head);

  Solution solution;
  head = solution.removeNthFromEnd(head, 5);

  print_list(head);
  destroy_list(head);

  return 0;
}
