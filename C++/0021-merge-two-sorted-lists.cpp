// HoNooD
// 2024.05.08 11:33:50

// https://leetcode.com/problems/merge-two-sorted-lists/?envType=study-plan-v2&envId=top-interview-150

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
class Solution {
public:
	ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
		if (list1 == nullptr) {
			return list2;
		}

		if (list2 == nullptr) {
			return list1;
		}

		ListNode* head = nullptr;
		ListNode* tail = nullptr;
		while (list1 != nullptr && list2 != nullptr) {
			ListNode* tmp = nullptr;
			if (list1->val < list2->val) {
				tmp = list1;
				list1 = list1->next;
			} else {
				tmp = list2;
				list2 = list2->next;
			}

			if (head == nullptr) {
				head = tmp;
				tail = tmp;
			}
			tail->next = tmp;
			tail = tail->next;
		}

		tail->next = list1 != nullptr ? list1 : list2;

		return head;
	}
};
