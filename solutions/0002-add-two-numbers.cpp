// HoNooD
// 2022.06.04 18:39
// 2024.05.08 15:24 update

// https://leetcode.com/problems/add-two-numbers/submissions/1252447352/?envType=study-plan-v2&envId=top-interview-150

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *	 int val;
 *	 ListNode *next;
 *	 ListNode() : val(0), next(nullptr) {}
 *	 ListNode(int x) : val(x), next(nullptr) {}
 *	 ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

// [2,4,3], [5,6,4] -> [7,0,8]
// [2,4,5], [5,6,4] -> [7,0,0,1]
// [2,4,9], [5,6,4] -> [7,0,4,1]
// [2,4,5,6], [5,6,4] -> [7,0,0,7]
// [2,4,5,9], [5,6,4] -> [7,0,0,0,1]
// [9], [1,9,9,9,9,9,9,9,9,9] -> [0,0,0,0,0,0,0,0,0,0,1]

class Solution {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode dummyHeadNode{};
		ListNode* dummyHead = &dummyHeadNode;
		ListNode* curr = dummyHead;
		int carry = 0;
		while (l1 != nullptr || l2 != nullptr) {
			int sum = (l1 != nullptr ? l1->val : 0) + (l2 != nullptr ? l2->val : 0) + carry;
			carry = sum / 10;
			curr->next = new ListNode{sum % 10};
			curr = curr->next;

			if (l1 != nullptr) {
				l1 = l1->next;
			}

			if (l2 != nullptr) {
				l2 = l2->next;
			}
		}

		if (carry > 0) {
			curr->next = new ListNode{carry};
		}

		return dummyHead->next;
	}
};
