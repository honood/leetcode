// HoNooD <honood@gmail.com>
// 2025.03.03 09:22

// 2095. Delete the Middle Node of a Linked List
// https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/?envType=study-plan-v2&envId=leetcode-75

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
  ListNode* deleteMiddle(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
      return nullptr;
    }

    ListNode* slow = head;
    ListNode* fast = head->next->next;
    while (fast != nullptr && fast->next != nullptr) {
      slow = slow->next;
      fast = fast->next->next;
    }

    // Note: Memory management consideration
    // The deleted node might need to be deallocated depending on the memory
    // ownership model
    slow->next = slow->next->next;

    return head;
  }
};
