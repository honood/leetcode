// HoNooD <honood@gmail.com>
// 2025.03.05 15:00

// 1448. Count Good Nodes in Binary Tree
// https://leetcode.com/problems/count-good-nodes-in-binary-tree/?envType=study-plan-v2&envId=leetcode-75

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
//   TreeNode(int x, TreeNode* left, TreeNode* right)
//       : val(x), left(left), right(right) {}
// };

class Solution {
public:
  int goodNodes(TreeNode* root) {
    return good_nodes_v1(root);
  }

private:
  int good_nodes_v1(TreeNode* root) {
    return good_nodes_v1_helper(root, std::numeric_limits<int>::min());
  }

  int good_nodes_v1_helper(TreeNode* root, int path_max) {
    if (root == nullptr) {
      return 0;
    }

    // Check if current node is good
    int count = root->val >= path_max ? 1 : 0;

    path_max = std::max(path_max, root->val);

    count += good_nodes_v1_helper(root->left, path_max);
    count += good_nodes_v1_helper(root->right, path_max);

    return count;
  }

  int good_nodes_v2(TreeNode* root) {
    if (root == nullptr) {
      return 0;
    }

    int count = 0;

    std::stack<std::pair<TreeNode*, int>> stack{{{root, root->val}}};
    while (!stack.empty()) {
      auto [node, path_max] = stack.top();
      stack.pop();

      if (node->val >= path_max) {
        path_max = node->val;
        ++count;
      }

      if (node->right != nullptr) {
        stack.emplace(node->right, path_max);
      }
      if (node->left != nullptr) {
        stack.emplace(node->left, path_max);
      }
    }

    return count;
  }
};
