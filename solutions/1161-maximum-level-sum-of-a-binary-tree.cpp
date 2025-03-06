// HoNooD <honood@gmail.com>
// 2025.02.04 01:32

// 1161. Maximum Level Sum of a Binary Tree
// https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree/description/?envType=study-plan-v2&envId=leetcode-75

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  int maxLevelSum(TreeNode* root) {
    if (!root) { return 0; }

    std::queue<TreeNode*> queue{};
    queue.push(root);
    int level = 1;
    int max_level = 1;
    int max_sum = root->val;

    while (!queue.empty()) {
      int curr_level_sum = 0;
      int size = queue.size();
      for (int i = 0; i < size; ++i) {
        TreeNode* node = queue.front();
        curr_level_sum += node->val;
        if (node->left) { queue.push(node->left); }
        if (node->right) { queue.push(node->right); }
        queue.pop();
      }

      if (curr_level_sum > max_sum) {
        max_level = level;
        max_sum = curr_level_sum;
      }

      ++level;
    }

    return max_level;
  }
};
