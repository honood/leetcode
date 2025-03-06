// HoNooD
// 2024.05.09 14:51

// https://leetcode.com/problems/symmetric-tree/description/?envType=study-plan-v2&envId=top-interview-150

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
	bool isSymmetric(TreeNode* root) {
		if (root == nullptr) {
			return true;
		}

		queue<TreeNode*> queue{};
		queue.push(root);
		while (!queue.empty()) {
			auto sz = queue.size();
			vector<TreeNode*> temp{};
			temp.reserve(sz);
			for (auto i = 0; i < sz; ++i) {
				TreeNode* node = queue.front();
				queue.pop();
				temp.push_back(node);

				if (node != nullptr) {
					queue.push(node->left);
					queue.push(node->right);
				}
			}

			if (!isVectorSymmetric(temp)) {
				return false;
			}
		}

		return true;
	}

private:
	bool isVectorSymmetric(vector<TreeNode*> const& vec) {
		if (vec.empty()) {
			return true;
		}

		for (int l = 0, r = vec.size() - 1; l < r; ++l, --r) {
			if (vec[l] == nullptr && vec[r] == nullptr) {
				continue;
			}

			if (vec[l] != nullptr && vec[r] != nullptr && vec[l]->val == vec[r]->val) {
				continue;
			}

			return false;
		}

		return true;
	}
};

// Best solution
class Solution_2 {
public:
	bool isSymmetric(TreeNode* root) {
		if (root == nullptr) {
			return true;
		}

		queue<TreeNode*> queue{};
		queue.push(root->left);
		queue.push(root->right);
		while (!queue.empty()) {
			TreeNode* left = queue.front();
			queue.pop();
			TreeNode* right = queue.front();
			queue.pop();

			if (left == nullptr && right == nullptr) {
				continue;
			}

			if (left == nullptr || right == nullptr) {
				return false;
			}

			if (left->val != right->val) {
				return false;
			}

			queue.push(left->left);
			queue.push(right->right);

			queue.push(left->right);
			queue.push(right->left);
		}

		return true;
	}
};

// recursive implementation
class Solution_2_2 {
public:
	bool isSymmetric(TreeNode* root) {
		return root == nullptr || isNodeEqual(root->left, root->right);
	}

private:
	bool isNodeEqual(TreeNode* left, TreeNode* right) {
		if (left == nullptr || right == nullptr) {
			return left == right;
		}

		if (left->val != right->val) {
			return false;
		}

		return isNodeEqual(left->left, right->right) && isNodeEqual(left->right, right->left);
	}
};
