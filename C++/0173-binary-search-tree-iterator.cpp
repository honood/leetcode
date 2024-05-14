// HoNood
// 2024.05.14 14:08

// https://leetcode.com/problems/binary-search-tree-iterator/?envType=study-plan-v2&envId=top-interview-150

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
class BSTIterator {
public:
  BSTIterator(TreeNode* root) {
    pushLeftMostPath(root);
  }

  int next() {
    TreeNode* node = stack_.top();
    stack_.pop();
    pushLeftMostPath(node->right);
    return node->val;
  }

  bool hasNext() {
    return !stack_.empty();
  }

private:
  void pushLeftMostPath(TreeNode* root) {
    while (root != nullptr) {
      stack_.push(root);
      root = root->left;
    }
  }

  stack<TreeNode*> stack_{};
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
