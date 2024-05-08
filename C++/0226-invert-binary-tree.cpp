// HoNooD
// 2024.05.08 19:15

// https://leetcode.com/problems/invert-binary-tree/?envType=study-plan-v2&envId=top-interview-150

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
	TreeNode* invertTree(TreeNode* root) {
		if (root == nullptr) {
			return nullptr;
		}

		TreeNode* temp = root->left;
		root->left = invertTree(root->right);
		root->right = invertTree(temp);

		return root;
	}
};

// https://en.wikipedia.org/wiki/Tree_traversal
// DFS (pre-order, in-order, post-order all OK)

// Post-order, LRN (use 2 stacks)
class Solution_2 {
public:
	TreeNode* invertTree(TreeNode* root) {
		if (root == nullptr) {
			return nullptr;
		}

		stack<TreeNode*> walk_stack{};
		stack<TreeNode*> result_stack{};
		walk_stack.push(root);
		while (!walk_stack.empty()) {
			TreeNode* node = walk_stack.top();
			walk_stack.pop();
			result_stack.push(node);
			// NOTE: push `node->left` before `node->right` for post-order-LRN
			if (node->left != nullptr) {
				walk_stack.push(node->left);
			}
			if (node->right != nullptr) {
				walk_stack.push(node->right);
			}
		}

		while (!result_stack.empty()) {
			TreeNode* node = result_stack.top();
			result_stack.pop();
			TreeNode* temp = node->left;
			node->left = node->right;
			node->right = temp;
		}

		return root;
	}
};

// Post-order, LRN (use 1 stack only)
class Solution_2_2 {
public:
	TreeNode* invertTree(TreeNode* root) {
		if (root == nullptr) {
			return nullptr;
		}

		stack<TreeNode*> walk_stack{};
		TreeNode* curr = root;
		TreeNode* lastVisited = nullptr;
		while (curr != nullptr || !walk_stack.empty()) {
			if (curr != nullptr) {
				walk_stack.push(curr);
				curr = curr->left;
				continue;
			}

			TreeNode* node = walk_stack.top();
			if (node->right != nullptr && node->right != lastVisited) {
				curr = node->right;
				continue;
			}

			lastVisited = node;
			walk_stack.pop();

			TreeNode* temp = node->left;
			node->left = node->right;
			node->right = temp;
		}

		return root;
	}
};

// Pre-order, NLR
class Solution_3 {
public:
	TreeNode* invertTree(TreeNode* root) {
		if (root == nullptr) {
			return nullptr;
		}

		stack<TreeNode*> walk_stack{};
		walk_stack.push(root);
		while (!walk_stack.empty()) {
			TreeNode* invertNode = walk_stack.top();
			walk_stack.pop();

			if (invertNode->right != nullptr) {
				walk_stack.push(invertNode->right);
			}
			if (invertNode->left != nullptr) {
				walk_stack.push(invertNode->left);
			}

			TreeNode* temp = invertNode->left;
			invertNode->left = invertNode->right;
			invertNode->right = temp;
		}

		return root;
	}
};

// In-order, NLR
class Solution_4 {
public:
	TreeNode* invertTree(TreeNode* root) {
		if (root == nullptr) {
			return nullptr;
		}

		std::stack<TreeNode*> walk_stack;
		TreeNode* curr = root;
		while (curr != nullptr || !walk_stack.empty()) {
			while (curr != nullptr) {
				walk_stack.push(curr);
				curr = curr->left;
			}

			curr = walk_stack.top();
			walk_stack.pop();
			TreeNode* invertNode = curr;
			curr = curr->right;

			TreeNode* temp = invertNode->left;
			invertNode->left = invertNode->right;
			invertNode->right = temp;
		}

		return root;
	}
};
