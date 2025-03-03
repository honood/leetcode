// HoNooD <honood@gmail.com>
// 2025.03.03 14:20

// 104. Maximum Depth of Binary Tree
// https://leetcode.com/problems/maximum-depth-of-binary-tree/?envType=study-plan-v2&envId=leetcode-75
// https://leetcode.com/problems/maximum-depth-of-binary-tree/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

// Definition for a binary tree node.
//
// struct TreeNode {
//   int val;
//   TreeNode* left;
//   TreeNode* right;
//   TreeNode() : val(0), left(nullptr), right(nullptr) {}
//   TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//   TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left),
//   right(right) {}
// };

class Solution {
public:
  int maxDepth(TreeNode* root) {
    return max_depth_v1(root);
  }

private:
  int max_depth_v1(TreeNode* root) {
    if (root == nullptr) {
      return 0;
    }

    int left_depth = max_depth_v1(root->left);
    int right_depth = max_depth_v1(root->right);

    return 1 + std::max(left_depth, right_depth);
  }

  int max_depth_v2(TreeNode* root) {
    if (root == nullptr) {
      return 0;
    }

    int depth = 0;
    std::queue<TreeNode*> queue{};
    queue.push(root);

    while (!queue.empty()) {
      int level_size = queue.size();
      while (level_size-- > 0) {
        TreeNode* node = queue.front();
        queue.pop();

        if (node->left != nullptr) {
          queue.push(node->left);
        }
        if (node->right != nullptr) {
          queue.push(node->right);
        }
      }

      ++depth;
    }

    return depth;
  }

  int max_depth_v3(TreeNode* root) {
    if (root == nullptr) {
      return 0;
    }

    int max_depth = 0;
    std::stack<std::pair<TreeNode*, int>> stack{{{root, 1}}};

    while (!stack.empty()) {
      auto [node, depth] = stack.top();
      stack.pop();

      max_depth = std::max(max_depth, depth);

      if (node->right != nullptr) {
        stack.emplace(node->right, depth + 1);
      }
      if (node->left != nullptr) {
        stack.emplace(node->left, depth + 1);
      }
    }

    return max_depth;
  }
};
