// HoNooD
// 2024.05.31 10:30

// 142. Linked List Cycle II
// https://leetcode.com/problems/linked-list-cycle-ii/description/
//
// Note:
// 1. Do not modify the linked list.
// 2. Can you solve it using O(1) (i.e. constant) memory?

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(nullptr) {}
};

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// NOT O(1) memory
class Solution {
public:
  ListNode *detectCycle(ListNode *head) {
    if (head == nullptr || head->next == nullptr) {
      return nullptr;
    }

    unordered_set<ListNode *> visited{};
    while (head != nullptr) {
      if (visited.contains(head)) {
        return head;
      }

      visited.emplace(head);
      head = head->next;
    }

    return nullptr;
  }
};

// Best
class Solution_2 {
public:
  ListNode *detectCycle(ListNode *head) {
    if (head == nullptr || head->next == nullptr) {
      return nullptr;
    }

    ListNode* slow = head;
    ListNode* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
      slow = slow->next;
      fast = fast->next->next;
      if (slow != fast) {
        continue;
      }

      // cycle detected
      ListNode* start = head;
      while (start != slow) {
        start = start->next;
        slow = slow->next;
      }
      return start;
    }

    return nullptr;
  }
};
