// HoNooD <honood@gmail.com>
// 2024.08.01 21:50

// 124. Binary Tree Maximum Path Sum
// https://leetcode.com/problems/binary-tree-maximum-path-sum/description/?envType=study-plan-v2&envId=top-interview-150

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  int maxPathSum(TreeNode* root) {
    return max_path_sum_v1(root);
  }

public:
  int max_path_sum_v1(TreeNode* root) {
    int max_sum = std::numeric_limits<int>::min();
    max_path_down(root, max_sum);
    return max_sum;
  }

  int max_path_down(TreeNode* node, int& max_sum) {
    if (node == nullptr) {
      return 0;
    }

    int left_max = std::max(0, max_path_down(node->left, max_sum));
    int right_max = std::max(0, max_path_down(node->right, max_sum));
    max_sum = std::max(max_sum, left_max + node->val + right_max);

    return node->val + std::max(left_max, right_max);
  }
};
