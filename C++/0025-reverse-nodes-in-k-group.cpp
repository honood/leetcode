// HoNooD <honood@gmail.com>
// 2024.08.01 14:31

// 25. Reverse Nodes in k-Group
// https://leetcode.com/problems/reverse-nodes-in-k-group/description/?envType=study-plan-v2&envId=top-interview-150

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
  ListNode* reverseKGroup(ListNode* head, int k) {
    return reverse_k_group_v1(head, k);
  }

private:
  ListNode* reverse_k_group_v1(ListNode* head, int k) {
    if (k <= 1 || head == nullptr || head->next == nullptr) {
      return head;
    }

    int count = 0;
    ListNode* curr = head;
    while (curr != nullptr) {
      ++count;
      curr = curr->next;
    }

    if (count < k) {
      return head;
    }

    ListNode dummy{0, head};
    ListNode* group_dummy_head = &dummy;
    ListNode* next = head;

    while (count >= k) {
      curr = next;
      next = curr->next;

      //          (dummy)-->[1)-->(2)-->(3)-->(4]-->[5)-->(6)-->(7)-->(8]-->(9)
      //             ^       ^     ^
      //             |       |     |
      // group_dummy_head   curr  next
      //
      //          (dummy)-->[2)-->(1)-->(3)-->(4]-->[5)-->(6)-->(7)-->(8]-->(9)
      //             ^             ^     ^
      //             |             |     |
      // group_dummy_head         curr  next
      //
      //          (dummy)-->[4)-->(3)-->(2)-->(1]-->[5)-->(6)-->(7)-->(8]-->(9)
      //                                       ^     ^     ^
      //                                       |     |     |
      //                         group_dummy_head   curr  next
      //
      //          (dummy)-->[4)-->(3)-->(2)-->(1]-->[7)-->(6)-->(5)-->(8]-->(9)
      //                                       ^                 ^     ^
      //                                       |                 |     |
      //                         group_dummy_head               curr  next

      for (int i = 1; i < k; ++i) {
        curr->next = next->next;
        next->next = group_dummy_head->next;
        group_dummy_head->next = next;

        next = curr->next;
      }

      //          (dummy)-->[4)-->(3)-->(2)-->(1]-->[5)-->(6)-->(7)-->(8]-->(9)
      //             ^                         ^     ^
      //             |                         |     |
      // group_dummy_head                     curr  next

      group_dummy_head = curr;
      count -= k;
    }

    return dummy.next;
  }

  ListNode* reverse_k_group_v2(ListNode* head, int k) {
    if (k <= 1 || head == nullptr || head->next == nullptr) {
      return head;
    }

    ListNode dummy{0, head};
    ListNode* group_dummy_head = &dummy;
    ListNode* group_end = head;

    while (true) {
      // find the end of the current group
      int i = 0;
      for (; i < k && group_end != nullptr; ++i) {
        group_end = group_end->next;
      }
      // less than `k` nodes, no need to reverse
      if (i < k) {
        break;
      }

      // reverse the current group
      ListNode* group_start = group_dummy_head->next;
      ListNode* next_group_start = group_end;
      ListNode* reversed_group_start = reverse(group_start, group_end);

      // connect the previous group with the newly reversed group
      group_dummy_head->next = reversed_group_start;
      group_start->next = next_group_start;

      // move `group_dummy_head` to the end of the newly reversed group
      group_dummy_head = group_start;
      group_end = group_dummy_head->next; // /*OR*/ group_end = next_group_start;
    }

    return dummy.next;
  }

  // reverse the sublist from `start` to `end`
  ListNode* reverse(ListNode* start, ListNode* end) {
    assert(start != end);
    ListNode* prev = nullptr;
    ListNode* curr = start;
    while (curr != end) {
      ListNode* next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
    }

    return prev;
  }
};
