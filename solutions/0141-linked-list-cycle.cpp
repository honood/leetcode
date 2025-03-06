// HoNooD
// 2024.05.08 10:33:50

// https://leetcode.com/problems/linked-list-cycle/?envType=study-plan-v2&envId=top-interview-150

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *	 int val;
 *	 ListNode *next;
 *	 ListNode(int x) : val(x), next(NULL) {}
 * };
 */

auto init_io = [] {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	return 0;
}();

class Solution {
public:
	bool hasCycle(ListNode* head) {
		if (head == nullptr || head->next == nullptr) {
			return false;
		}

		ListNode* slow = head;
		ListNode* fast = head;
		while (fast != nullptr && fast->next != nullptr) {
			slow = slow->next;
			fast = fast->next->next;
			if (fast == slow) {
				return true;
			}
		}

		return false;
	}
};

class Solution_1 {
public:
	bool hasCycle(ListNode* head) {
		if (head == nullptr) {
			return false;
		}

		unordered_set<ListNode*> walkedNodes{};
		while (head != nullptr) {
			auto res = walkedNodes.insert(head);
			if (!res.second) {
				return true;
			}

			head = head->next;
		}

		return false;
	}
};
