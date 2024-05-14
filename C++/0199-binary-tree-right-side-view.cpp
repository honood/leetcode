// HoNooD
// 2024.05.14 21:35

// 199. Binary Tree Right Side View
// https://leetcode.com/problems/binary-tree-right-side-view/?envType=study-plan-v2&envId=top-interview-150

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
  vector<int> rightSideView(TreeNode* root) {
    if (root == nullptr) {
      return {};
    }

    vector<int> res{};
    queue<TreeNode*> q{};
    q.push(root);
    while (!q.empty()) {
      int sz = q.size();
      for (int i = 0; i < sz; ++i) {
        TreeNode* node = q.front();
        q.pop();

        if (sz - 1 == i) {
          res.push_back(node->val);
        }

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

// Reverse pre-order, NRL
// https://en.wikipedia.org/wiki/Tree_traversal#Reverse_pre-order,_NRL
// 
//         5
//      ╱     ╲
//    1         8
//  ╱   ╲     ╱   ╲
// 0     3   6     9
//      ╱ ╲   ╲
//     2   4   7
//
class Solution_2 {
public:
  vector<int> rightSideView(TreeNode* root) {
    vector<int> res{};
    impl(root, res, 0);
    return res;
  }

private:
  void impl(TreeNode* root, vector<int>& res, int level) {
    if (root == nullptr) {
      return;
    }

    // For the above binary tree, `5 8 9 6 7 1 3 4 2 0 ` will be printed out 
    // with the following output code:
    // std::cout << root->val << ' ';
    if (res.size() == level) {
      res.push_back(root->val);
    }

    if (root->right != nullptr) {
      impl(root->right, res, level + 1);
    }
    if (root->left != nullptr) {
      impl(root->left, res, level + 1);
    }
  }
};
