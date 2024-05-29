// HoNooD
// 2024.05.28 17:28

// 148. Sort List
// https://leetcode.com/problems/sort-list/description/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Divide-and-conquer_algorithm

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
  ListNode* sortList(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
      return head;
    }

    // find the middle of the list
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast->next != nullptr && fast->next->next != nullptr) {
      slow = slow->next;
      fast = fast->next->next;
    }
    ListNode* mid = slow->next;
    slow->next = nullptr;

    return merge(sortList(head), sortList(mid));
  }

private:
  ListNode* merge(ListNode* l1, ListNode* l2) {
    if (l1 == nullptr) {
      return l2;
    }

    if (l2 == nullptr) {
      return l1;
    }

    ListNode dummyNode{};
    ListNode* curr = &dummyNode;
    while (l1 != nullptr && l2 != nullptr) {
      if (l1->val < l2->val) {
        curr->next = l1;
        l1 = l1->next;
      } else {
        curr->next = l2;
        l2 = l2->next;
      }

      curr = curr->next;
    }

    if (l1 != nullptr) {
      curr->next = l1;
    }

    if (l2 != nullptr) {
      curr->next = l2;
    }

    return dummyNode.next;
  }
};
