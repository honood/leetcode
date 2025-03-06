// HoNooD <honood@gmail.com>
// 2025.03.03 10:20

// 2130. Maximum Twin Sum of a Linked List
// https://leetcode.com/problems/maximum-twin-sum-of-a-linked-list/?envType=study-plan-v2&envId=leetcode-75

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
  // Constraints:
  //   - The number of nodes in the list is an even integer in the range [2, 105].
  int pairSum(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
      slow = slow->next;
      fast = fast->next->next;
    }

    ListNode* reversed_second_half_head = reverse_list(slow);

    int result = std::numeric_limits<int>::min();
    ListNode* first = head;
    ListNode* second = reversed_second_half_head;
    while (second != nullptr) {
      result = std::max(result, first->val + second->val);

      first = first->next;
      second = second->next;
    }
    return result;
  }

private:
  ListNode* reverse_list(ListNode* head) {
    ListNode dummy_head{};
    while (head != nullptr) {
      ListNode* temp = head->next;
      head->next = dummy_head.next;
      dummy_head.next = head;
      head = temp;
    }
    return dummy_head.next;
  }
};
