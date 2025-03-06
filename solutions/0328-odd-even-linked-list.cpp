// HoNooD <honood@gmail.com>
// 2025.03:03 00:35

// 328. Odd Even Linked List
// https://leetcode.com/problems/odd-even-linked-list/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

// Definition for singly-linked list.
//
// struct ListNode {
//   int val;
//   ListNode* next;
//   ListNode() : val(0), next(nullptr) {}
//   ListNode(int x) : val(x), next(nullptr) {}
//   ListNode(int x, ListNode* next) : val(x), next(next) {}
// };

class Solution {
public:
  // 1 -> 2 -> 3 -> 4 -> 5         =>    1 -> 3 -> 5 -> 2 -> 4
  // 1 -> 2 -> 3 -> 4 -> 5 -> 6    =>    1 -> 3 -> 5 -> 2 -> 4 -> 6
  ListNode* oddEvenList(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
      return head;
    }

    ListNode* odd_curr = head;
    ListNode* even_curr = head->next;
    ListNode* even_head = head->next;

    while (even_curr != nullptr && even_curr->next != nullptr) {
      odd_curr->next = even_curr->next;
      odd_curr = odd_curr->next;

      even_curr->next = odd_curr->next;
      even_curr = even_curr->next;
    }
    odd_curr->next = even_head;

    return head;
  }
};
