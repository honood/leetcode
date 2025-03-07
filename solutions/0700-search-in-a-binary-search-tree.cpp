// HoNooD <honood@gmail.com>
// 2025.03.07 08:41

// 700. Search in a Binary Search Tree
// https://leetcode.com/problems/search-in-a-binary-search-tree/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

// Definition for a binary tree node.
// struct TreeNode {
//   int val;
//   TreeNode* left;
//   TreeNode* right;
//   TreeNode() : val(0), left(nullptr), right(nullptr) {}
//   TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//   TreeNode(int x, TreeNode* left, TreeNode* right)
//       : val(x), left(left), right(right) {}
// };

class Solution {
public:
  TreeNode* searchBST(TreeNode* root, int val) {
    return search_bst_v2(root, val);
  }

private:
  // - Time complexity: O(h), h is the height of the tree.
  // - Space complexity: O(h)
  TreeNode* search_bst_v1(TreeNode* root, int val) {
    return search_bst_v1_helper(root, val);
  }

  TreeNode* search_bst_v1_helper(TreeNode* root, int val) {
    if (root == nullptr || root->val == val) {
      return root;
    }

    return val < root->val ? search_bst_v1_helper(root->left, val)
                           : search_bst_v1_helper(root->right, val);
  }

  // - Time complexity: O(h), h is the height of the tree.
  // - Space complexity: O(1)
  TreeNode* search_bst_v2(TreeNode* root, int val) {
    while (root != nullptr && root->val != val) {
      root = val < root->val ? root->left : root->right;
    }

    return root;
  }
};
