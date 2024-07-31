// HoNooD <honood@gmail.com>
// 2024.07.31 15:13

// 24. Swap Nodes in Pairs
// https://leetcode.com/problems/swap-nodes-in-pairs/description/

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
  ListNode* swapPairs(ListNode* head) {
    return swap_pairs_v1(head);
  }

private:
  ListNode* swap_pairs_v1(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
      return head;
    }

    ListNode dummy{0, head};
    ListNode* dummy_head = &dummy;

    ListNode* curr = dummy_head;
    while (curr->next != nullptr && curr->next->next != nullptr) {
      ListNode* first = curr->next;
      ListNode* second = curr->next->next;

      first->next = second->next;
      second->next = first;
      curr->next = second;

      curr = first;
    }

    return dummy_head->next;
  }

  ListNode* swap_pairs_v2(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
      return head;
    }

    ListNode* curr = head;
    head = head->next;
    ListNode* prev = nullptr;

    while (curr != nullptr && curr->next != nullptr) {
      ListNode* first = curr;
      ListNode* second = curr->next;

      first->next = second->next;
      second->next = first;
      if (prev != nullptr) {
        prev->next = second;
      }

      prev = first;
      curr = first->next;
    }

    return head;
  }
};
