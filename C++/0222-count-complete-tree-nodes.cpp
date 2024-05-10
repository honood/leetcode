// HoNooD
// 2024.05.10 17:48

// https://leetcode.com/problems/count-complete-tree-nodes/description/?envType=study-plan-v2&envId=top-interview-150

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

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
	int countNodes(TreeNode* root) {
		if (root == nullptr) {
			return 0;
		}

		return 1 + countNodes(root->left) + countNodes(root->right);
	}
};

class Solution_2 {
public:
	int countNodes(TreeNode* root) {
		if (root == nullptr) {
			return 0;
		}

		int leftMostPathCount = 0;
		TreeNode* left = root;
		while (left != nullptr) {
			++leftMostPathCount;
			left = left->left;
		}

		int rightMostPathCount = 0;
		TreeNode* right = root;
		while (right != nullptr) {
			++rightMostPathCount;
			right = right->right;
		}

		if (leftMostPathCount == rightMostPathCount) {
			// https://en.wikipedia.org/wiki/Geometric_progression
			// S(n) = a0 * (1 - q ** n) / (1 - q) /* q != 1 */
			return (1 << leftMostPathCount) - 1; 
		}

		return 1 + countNodes(root->left) + countNodes(root->right);
	}
};

class Solution_3 {
public:
	int countNodes(TreeNode* root) {
		if (root == nullptr) {
			return 0;
		}

		int height = getHeight(root);
		int count = 0;
		while (root != nullptr) {
			int rightHeight = getHeight(root->right);
			if (rightHeight == height - 1) {
				// 左子树是满的，右子树可能是满的
				// 
				// 节点数增加左子树的节点数和当前 root 节点数，即：
				// ((1 << (height - 1)) - 1) + 1  =>  1 << (height - 1)
				count += 1 << (height - 1);
				root = root->right;
			} else {
				// 右子树是满的，左子树可能是满的。例如：
				//       1
				//      / \
				//     2   3
				//    / \ / \
				//   4  5 6  7
				//  / \
				// 8   9
				assert(rightHeight == height - 2);
				// 节点数增加右子树的节点数和当前 root 节点数，即：
				// ((1 << (height - 2)) - 1) + 1  =>  1 << (height - 2)
				count += 1 << (height - 2);
				root = root->left;
			}
			--height;
		}

		return count;
	}

private:
	int getHeight(TreeNode* root) {
		int height = 0;
		while (root) {
			++height;
			root = root->left;
		}
		return height;
	}
};
