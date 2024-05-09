// HoNooD
// 2024.05.09 16:43

// https://leetcode.com/problems/path-sum/?envType=study-plan-v2&envId=top-interview-150

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
	bool hasPathSum(TreeNode* root, int targetSum) {
		if (root == nullptr) {
			return false;
		}

		if (root->left == nullptr && root->right == nullptr) {
			return root->val == targetSum;
		}

		int subtreeTargetSum = targetSum - root->val;
		if (hasPathSum(root->left, subtreeTargetSum)) {
			return true;
		}
 
		if (hasPathSum(root->right, subtreeTargetSum)) {
			return true;
		}

		return false;
	}
};

class Solution_2 {
public:
	bool hasPathSum(TreeNode* root, int sum) {
		if (root == nullptr) {
			return false;
		}

		stack<TreeNode*> nodeStack{};
		nodeStack.push(root);
		stack<int> remainingSumStack{};
		remainingSumStack.push(sum - root->val);
		while (!nodeStack.empty()) {
			TreeNode* node = nodeStack.top();
			nodeStack.pop();
			int remainingSum = remainingSumStack.top();
			remainingSumStack.pop();

			if (node->left == nullptr && node->right == nullptr && remainingSum == 0) {
				return true;
			}

			if (node->right) {
				nodeStack.push(node->right);
				remainingSumStack.push(remainingSum - node->right->val);
			}

			if (node->left) {
				nodeStack.push(node->left);
				remainingSumStack.push(remainingSum - node->left->val);
			}
		}

		return false;
	}
};
