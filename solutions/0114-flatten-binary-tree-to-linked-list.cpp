// HoNooD
// 2024.05.13 09:30

// https://leetcode.com/problems/flatten-binary-tree-to-linked-list/?envType=study-plan-v2&envId=top-interview-150

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *   int val;
 *   TreeNode *left;
 *   TreeNode *right;
 *   TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *   TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *   TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
public:
  void flatten(TreeNode* root) {
    if (root == nullptr) {
      return;
    }

    flatten(root->right);
    if (root->left == nullptr) {
      return;
    }

    flatten(root->left);
    TreeNode* left_flatten_tail = root->left;
    while (left_flatten_tail->right != nullptr) {
      left_flatten_tail = left_flatten_tail->right;
    }

    left_flatten_tail->right = root->right;
    root->right = root->left;
    root->left = nullptr;
  }
};

class Solution_2 {
public:
  void flatten(TreeNode* root) {
    while (root != nullptr) {
      if (root->left != nullptr) {
        TreeNode* leftSubtreeRightMost = root->left;
        while (leftSubtreeRightMost->right != nullptr) {
          leftSubtreeRightMost = leftSubtreeRightMost->right;
        }
        leftSubtreeRightMost->right = root->right;
        root->right = root->left;
        root->left = nullptr;
      }
      
      root = root->right;
    }
  }
};

// Explain: 
// 
//     1
//    / \
//   2   5
//  /   / \
// 3   4   6
//
// For the above binary tree, the node nodes will point to the following nodes
// in turn:
//   6, 4, 5, 3, 2, 1
// 
class Solution_3 {
public:
  void flatten(TreeNode* root) {
    if (root == nullptr) {
      return;
    }

    flatten(root->right);
    flatten(root->left);

    root->right = head;
    root->left = nullptr;
    head = root;
  }

private:
  TreeNode* head{nullptr};
};
