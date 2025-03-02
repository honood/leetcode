// HoNooD <honood@gmail.com>
// 2025.03.02 23:44

// 206. Reverse Linked List
// https://leetcode.com/problems/reverse-linked-list/description/?envType=study-plan-v2&envId=leetcode-75

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
  ListNode* reverseList(ListNode* head) {
    return reverse_list_v2(head);
  }

private:
  // In-place Reversal / Three Pointers Technique
  //
  // - Time complexity: O(n)
  // - Space complexity: O(1)
  ListNode* reverse_list_v1(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;

    while (curr != nullptr) {
      ListNode* next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
    }

    return prev;
  }

  // Head Insertion
  //
  // - Time complexity: O(n)
  // - Space complexity: O(1)
  ListNode* reverse_list_v2(ListNode* head) {
    ListNode dummy_head{};
    while (head != nullptr) {
      ListNode* temp = head->next;
      head->next = dummy_head.next;
      dummy_head.next = head;
      head = temp;
    }
    return dummy_head.next;
  }

  // - Time complexity: O(n)
  // - Space complexity: O(n)
  ListNode* reverse_list_v3(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
      return head;
    }

    // After reversal, the node pointed by `head->next` becomes the tail
    // of the reversed sublist.
    ListNode* new_head = reverse_list_v3(head->next);
    head->next->next = head;
    head->next = nullptr;
    return new_head;
  }
};
