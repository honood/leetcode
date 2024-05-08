// HoNooD
// 2024.05.08 15:35

// https://leetcode.com/problems/maximum-depth-of-binary-tree/?envType=study-plan-v2&envId=top-interview-150

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
	int maxDepth(TreeNode* root) {
		if (root == nullptr) {
			return 0;
		}

		return 1 + max(maxDepth(root->left), maxDepth(root->right));
	}
};

class Solution_2 {
public:
	int maxDepth(TreeNode* root) {
		if (root == nullptr) {
			return 0;
		}

		queue<TreeNode*> queue{};
		queue.push(root);
		int depth = 0;
		while (!queue.empty()) {
			int sz = queue.size();
			for (int i = 0; i < sz; ++i) {
				TreeNode* node = queue.front();
				queue.pop();
				if (node->left != nullptr) {
					queue.push(node->left);
				}
				if (node->right != nullptr) {
					queue.push(node->right);
				}
			}
			++depth;
		}

		return depth;
	}
};

class Solution_3 {
public:
	int maxDepth(TreeNode* root) {
		if (root == nullptr) {
			return 0;
		}

		stack<pair<TreeNode*, int>> stack{};
		stack.push(make_pair(root, 1));
		int maxDepth = 1;
		while (!stack.empty()) {
			auto top = stack.top();
			stack.pop();
			TreeNode* node = top.first;
			int depth = top.second;
			if (depth > maxDepth) {
				maxDepth = depth;
			}
			if (node->right != nullptr) {
				stack.push(make_pair(node->right, depth + 1));
			}
			if (node->left != nullptr) {
				stack.push(make_pair(node->left, depth + 1));
			}
		}

		return maxDepth;
	}
};
