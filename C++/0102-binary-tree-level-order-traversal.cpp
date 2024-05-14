// HoNooD
// 2024.05.15 01:28

// 102. Binary Tree Level Order Traversal
// https://leetcode.com/problems/binary-tree-level-order-traversal/?envType=study-plan-v2&envId=top-interview-150

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
  vector<vector<int>> levelOrder(TreeNode* root) {
    if (root == nullptr) {
      return {};
    }

    vector<vector<int>> res{};
    queue<TreeNode*> q{};
    q.push(root);
    while (!q.empty()) {
      int sz = q.size();
      res.emplace_back();
      res.back().reserve(sz);
      for (int i = 0; i < sz; ++i) {
        TreeNode* node = q.front();
        q.pop();

        res.back().push_back(node->val);

        if (node->left != nullptr) {
          q.push(node->left);
        }
        if (node->right != nullptr) {
          q.push(node->right);
        }
      }
    }

    return res;
  }
};

class Solution_2 {
public:
  vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> res{};
    recursiveBFS(root, 0, res);
    return res;
  }

private:
  void recursiveBFS(TreeNode* root, int level, vector<vector<int>>& res) {
    if (root == nullptr) {
      return;
    }

    if (res.size() <= level) {
      res.emplace_back();
    }
    res[level].push_back(root->val);

    recursiveBFS(root->left, level + 1, res);
    recursiveBFS(root->right, level + 1, res);
  }
};
