// HoNooD <honood@gmail.com>
// 2024.06.16 23:50

// 61. Rotate List
// https://leetcode.com/problems/rotate-list/description/?envType=study-plan-v2&envId=top-interview-150

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  ListNode *rotateRight(ListNode* head, int k) {
    if (k <= 0 || head == nullptr || head->next == nullptr) {
      return head;
    }

    ListNode* tail = head;
    int len = 1;
    while (tail->next != nullptr) {
      ++len;
      tail = tail->next;
    }

    k %= len;
    if (k == 0) {
      return head;
    }

    ListNode* newTail = head;
    for (int i = 1; i < len - k; ++i) {
      newTail = newTail->next;
    }

    ListNode* newHead = newTail->next;
    newTail->next = nullptr;
    tail->next = head;

    return newHead;
  }
};
