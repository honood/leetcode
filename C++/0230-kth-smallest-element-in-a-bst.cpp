// HoNooD
// 2024.05.15 12:30

// 230. Kth Smallest Element in a BST
// https://leetcode.com/problems/kth-smallest-element-in-a-bst/description/?envType=study-plan-v2&envId=top-interview-150

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
public:
  int kthSmallest(TreeNode* root, int k) {
    assert(root != nullptr);

    stack<TreeNode*> stack{};
    TreeNode* curr = root;
    while (curr != nullptr || !stack.empty()) {
      while (curr != nullptr) {
        stack.push(curr);
        curr = curr->left;
      }

      curr = stack.top();
      stack.pop();
      if (--k == 0) {
        return curr->val;
      }

      curr = curr->right;
    }

    assert(false);
    return 0;
  }
};

class Solution_2 {
public:
  int kthSmallest(TreeNode* root, int k) {
    assert(root != nullptr);

    int res = 0;
    inorderDFS(root, k, res);
    return res;
  }

private:
  void inorderDFS(TreeNode* root, int& k, int& res) {
    if (k == 0 || root == nullptr) {
      return;
    }

    inorderDFS(root->left, k, res);
    if (--k == 0) {
      res = root->val;
    }
    inorderDFS(root->right, k, res);
  }
};
