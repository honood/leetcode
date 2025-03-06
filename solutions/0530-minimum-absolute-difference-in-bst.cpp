// HoNooD
// 2024.05.15 10:53

// 530. Minimum Absolute Difference in BST
// https://leetcode.com/problems/minimum-absolute-difference-in-bst/description/?envType=study-plan-v2&envId=top-interview-150
//
// Note: This question is the same as: 
// 783. Minimum Distance Between BST Nodes
// https://leetcode.com/problems/minimum-distance-between-bst-nodes/

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
  int getMinimumDifference(TreeNode* root) {
    vector<int> res{};
    inorderTraversal(root, res);
    assert(res.size() >= 2);
    int minDiff = 100000 + 1; // 10**5 + 1
    for (int i = 1; i < res.size(); ++i) {
      int diff = res[i] - res[i - 1];
      diff = diff < 0 ? ~diff + 1 : diff; // abs
      if (minDiff > diff) {
        minDiff = diff;
      }
    }

    return minDiff;
  }

private:
  void inorderTraversal(TreeNode* root, vector<int>& res) {
    if (root == nullptr) {
      return;
    }

    inorderTraversal(root->left, res);
    res.push_back(root->val);
    inorderTraversal(root->right, res);
  }
};

class Solution_2 {
public:
  int getMinimumDifference(TreeNode* root) {
    int minDiff = std::numeric_limits<int>::max();

    stack<TreeNode*> stack{};
    TreeNode* curr = root;
    TreeNode* prev = nullptr;
    while (curr != nullptr || !stack.empty()) {
      while (curr != nullptr) {
        stack.push(curr);
        curr = curr->left;
      }

      curr = stack.top();
      stack.pop();

      if (prev != nullptr) {
        if (int diff = abs(curr->val - prev->val); minDiff > diff) {
          minDiff = diff;
        }
      }
      prev = curr;

      curr = curr->right;
    }

    return minDiff;
  }
};
