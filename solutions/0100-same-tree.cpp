// HoNooD
// 2024.05.08 16:55

// https://leetcode.com/problems/same-tree/description/?envType=study-plan-v2&envId=top-interview-150

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *	 int val;
 *	 TreeNode *left;
 *	 TreeNode *right;
 *	 TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *	 TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *	 TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
	bool isSameTree(TreeNode* p, TreeNode* q) {
		if (p == nullptr || q == nullptr) {
			return p == q;
		}

		return p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
	}
};

class Solution_2 {
public:
	bool isSameTree(TreeNode* p, TreeNode* q) {
		stack<TreeNode*> stack_p{};
		stack<TreeNode*> stack_q{};
		stack_p.push(p);
		stack_q.push(q);

		while (!stack_p.empty() && !stack_q.empty()) {
			TreeNode* node_p = stack_p.top();
			TreeNode* node_q = stack_q.top();
			stack_p.pop();
			stack_q.pop();

			if (node_p == nullptr && node_q == nullptr) {
				continue;
			}

			if (node_p == nullptr || node_q == nullptr) {
				return false;
			}

			if (node_p->val != node_q->val) {
				return false;
			}

			stack_p.push(node_p->right);
			stack_p.push(node_p->left);
			stack_q.push(node_q->right);
			stack_q.push(node_q->left);
		}

		return stack_p.empty() && stack_q.empty();
	}
};
