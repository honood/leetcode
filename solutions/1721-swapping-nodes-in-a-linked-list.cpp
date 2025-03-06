// HoNooD <honood@gmail.com>
// 2024.08.01 13:51

// 1721. Swapping Nodes in a Linked List
// https://leetcode.com/problems/swapping-nodes-in-a-linked-list/description/

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
  ListNode* swapNodes(ListNode* head, int k) {
    return swap_nodes_v1(head, k);
  }

private:
  ListNode* swap_nodes_v1(ListNode* head, int k) {
    if (k <= 0 || head == nullptr || head->next == nullptr) {
      return head;
    }

    ListNode* fast = head;
    ListNode* slow = head;
    while (fast != nullptr && --k > 0) {
      fast = fast->next;
    }
    if (fast == nullptr) {
      return head;
    }

    ListNode* kth = fast;

    while (fast->next != nullptr) {
      fast = fast->next;
      slow = slow->next;
    }

    std::swap(kth->val, slow->val);

    return head;
  }
};
