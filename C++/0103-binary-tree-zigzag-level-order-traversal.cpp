// HoNooD
// 2024.05.15 01:41

// 103. Binary Tree Zigzag Level Order Traversal
// https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/description/?envType=study-plan-v2&envId=top-interview-150

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
  vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    if (root == nullptr) {
      return {};
    }

    vector<vector<int>> res{};
    queue<TreeNode*> q{};
    q.push(root);
    bool l2r = true;
    while (!q.empty()) {
      int sz = q.size();
      res.emplace_back();
      res.back().reserve(sz);
      for (int i = 0; i < sz; ++i) {
        TreeNode* node = q.front();
        q.pop();

        if (l2r) {
          res.back().push_back(node->val);
        } else {
          res.back().insert(res.back().cbegin(), node->val);
        }

        if (node->left != nullptr) {
          q.push(node->left);
        }
        if (node->right != nullptr) {
          q.push(node->right);
        }
      }

      l2r = !l2r;
    }

    return res;
  }
};
