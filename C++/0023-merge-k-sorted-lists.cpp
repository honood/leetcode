// HoNooD
// 2024.05.29 14:28

// 23. Merge k Sorted Lists
// https://leetcode.com/problems/merge-k-sorted-lists/?envType=study-plan-v2&envId=top-interview-150

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

// Not recommended!
class Solution {
public:
  ListNode* mergeKLists(vector<ListNode*>& lists) {
    if (lists.empty()) {
      return nullptr;
    }

    ListNode* merged = nullptr;
    for (auto const& list : lists) {
      merged = mergeTwoLists(merged, list);
    }

    return merged;
  }

private:
  ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if (l1 == nullptr) {
      return l2;
    }

    if (l2 == nullptr) {
      return l1;
    }

    ListNode dummyNode{};
    ListNode* tail = &dummyNode;
    while (l1 != nullptr && l2 != nullptr) {
      if (l1->val < l2->val) {
        tail->next = l1;
        l1 = l1->next;
      } else {
        tail->next = l2;
        l2 = l2->next;
      }

      tail = tail->next;
    }

    if (l1 != nullptr) {
      tail->next = l1;
    }

    if (l2 != nullptr) {
      tail->next = l2;
    }

    return dummyNode.next;
  }
};

class Solution_2 {
public:
  ListNode* mergeKLists(vector<ListNode*>& lists) {
    if (lists.empty()) {
      return nullptr;
    }

    return impl(lists, 0, lists.size() - 1);
  }

private:
  ListNode* impl(vector<ListNode*> const& lists, int first, int last) {
    if (first > last) {
      return nullptr;
    }

    if (first == last) {
      return lists[first];
    }

    int mid = (first + last) / 2;
    return mergeTwoLists(
      impl(lists, first, mid),
      impl(lists, mid + 1, last)
    );
  }

  ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if (l1 == nullptr) {
      return l2;
    }

    if (l2 == nullptr) {
      return l1;
    }

    ListNode dummyNode{};
    ListNode* tail = &dummyNode;
    while (l1 != nullptr && l2 != nullptr) {
      if (l1->val < l2->val) {
        tail->next = l1;
        l1 = l1->next;
      } else {
        tail->next = l2;
        l2 = l2->next;
      }

      tail = tail->next;
    }

    if (l1 != nullptr) {
      tail->next = l1;
    }

    if (l2 != nullptr) {
      tail->next = l2;
    }

    return dummyNode.next;
  }
};

class Solution_3 {
public:
  ListNode* mergeKLists(vector<ListNode*> &lists) {
    if (lists.empty()) {
      return nullptr;
    }

    struct Compare {
      bool operator()(ListNode* const& left, ListNode* const& right) {
        return left->val > right->val;
      }
    };
    priority_queue<ListNode*, vector<ListNode*>, Compare> minHeap{};
    for (auto const& list : lists) {
      if (list != nullptr) {
        minHeap.emplace(list);
      }
    }

    ListNode dummyNode{};
    ListNode* tail = &dummyNode;
    while (!minHeap.empty()) {
      ListNode* smallest = minHeap.top();
      minHeap.pop();

      tail->next = smallest;
      tail = tail->next;

      if (smallest->next != nullptr) {
        minHeap.emplace(smallest->next);
      }
    }

    return dummyNode.next;
  }
};
