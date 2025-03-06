// HoNooD <honood@gmail.com>
// 2025.03.07 00:20

// 199. Binary Tree Right Side View
// https://leetcode.com/problems/binary-tree-right-side-view/?envType=study-plan-v2&envId=leetcode-75
// https://leetcode.com/problems/binary-tree-right-side-view/?envType=study-plan-v2&envId=top-interview-150

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
  vector<int> rightSideView(TreeNode* root) {
    return right_side_view_v2(root);
  }

private:
  vector<int> right_side_view_v1(TreeNode* root) {
    if (root == nullptr) {
      return {};
    }

    vector<int> result{};

    std::queue<TreeNode*> queue{{root}};
    while (!queue.empty()) {
      int level_size = queue.size();
      for (int i = 0; i < level_size; ++i) {
        TreeNode* node = queue.front();
        queue.pop();

        if (level_size - 1 == i) {
          result.push_back(node->val);
        }

        if (node->left != nullptr) {
          queue.push(node->left);
        }
        if (node->right != nullptr) {
          queue.push(node->right);
        }
      }
    }

    return result;
  }

  // Depth-First Search (DFS)
  //
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
  vector<int> right_side_view_v2(TreeNode* root) {
    vector<int> result{};
    right_side_view_v2_helper(root, 0, result);
    return result;
  }

  void right_side_view_v2_helper(TreeNode* root, int depth,
                                 vector<int>& result) {
    if (root == nullptr) {
      return;
    }

    // Add to result when first visiting this depth
    // Since we visit right subtree first, this will be the rightmost node at
    // this depth
    if (result.size() == depth) {
      result.push_back(root->val);
    }

    // Visit right subtree before left to prioritize rightmost nodes
    right_side_view_v2_helper(root->right, depth + 1, result);
    right_side_view_v2_helper(root->left, depth + 1, result);
  }
};
