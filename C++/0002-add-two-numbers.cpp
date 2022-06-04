// HoNooD
// 2022.06.04 18:39

// https://leetcode.com/problems/add-two-numbers/


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
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
    ListNode* result_head = nullptr;
    ListNode* result_cur = nullptr;
    
    ListNode* l1_cur = l1;
    ListNode* l2_cur = l2;
    int carry = 0;
    while (l1_cur != nullptr && l2_cur  != nullptr) {
      int sum = l1_cur->val + l2_cur->val + carry;
      carry = sum / 10;
      
      ListNode *tmp = new ListNode{sum % 10};
      if (result_cur != nullptr) {
        result_cur->next = tmp;
      }
      result_cur = tmp;
      
      if (result_head == nullptr) {
        result_head = tmp;
      }
      
      l1_cur = l1_cur->next;
      l2_cur = l2_cur->next;
    }
    
    ListNode* left_cur = l1_cur;
    if (l1_cur == nullptr) {
      left_cur = l2_cur;
    }
    
    while (left_cur != nullptr) {
      int sum = left_cur->val + carry;
      carry = sum / 10;
      
      ListNode *tmp = new ListNode{sum % 10};
      result_cur->next = tmp;
      result_cur = tmp;
      
      left_cur = left_cur->next;
    }
    
    if (carry > 0) {
      result_cur->next = new ListNode{carry};
      result_cur = result_cur->next;
    }
    
    return result_head;
  }
};

// 算法与上面一致。
// 通过新增一个 dummy 头节点，简化了代码的写法。
class Solution2 {
public:
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode* dummy_head = new ListNode{0};
    ListNode* curr = dummy_head;
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
    
    return dummy_head->next;
  }
};
