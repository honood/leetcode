// HoNooD <honood@gmail.com>
// 2025.03.06 10:00

// 1372. Longest ZigZag Path in a Binary Tree
// https://leetcode.com/problems/longest-zigzag-path-in-a-binary-tree/?envType=study-plan-v2&envId=leetcode-75

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
  int longestZigZag(TreeNode* root) {
    return longest_zigzag_v2(root);
  }

private:
  // - Time complexity: O(n)
  // - Space complexity: O(h), h is the height of the tree.
  int longest_zigzag_v1(TreeNode* root) {
    if (root == nullptr) {
      return -1;
    }

    int max_length = 0;
    longest_zigzag_v1_dfs(root, true, 0, max_length);
    longest_zigzag_v1_dfs(root, false, 0, max_length);
    return max_length;
  }

  // go_left: Direction to explore from current node (true=left, false=right)
  void longest_zigzag_v1_dfs(TreeNode* node, bool go_left, int curr_length, int& max_length) {
    if (node == nullptr) {
      return;
    }

    max_length = std::max(max_length, curr_length);

    if (go_left) {
      longest_zigzag_v1_dfs(node->left, false, curr_length + 1, max_length);
      longest_zigzag_v1_dfs(node->right, true, 1, max_length);
    } else {
      longest_zigzag_v1_dfs(node->right, true, curr_length + 1, max_length);
      longest_zigzag_v1_dfs(node->left, false, 1, max_length);
    }
  }

  // - Time complexity: O(n)
  // - Space complexity: O(h), h is the height of the tree.
  int longest_zigzag_v2(TreeNode* root) {
    if (root == nullptr) {
      return -1;
    }

    int max_length = 0;
    longest_zigzag_v2_dfs(root->left, true, 1, max_length);
    longest_zigzag_v2_dfs(root->right, false, 1, max_length);
    return max_length;
  }

  // is_left: Direction from which current node was reached (true=from parent's
  // left, false=from parent's right)
  void longest_zigzag_v2_dfs(TreeNode* node, bool is_left, int curr_length, int& max_length) {
    if (node == nullptr) {
      return;
    }

    max_length = std::max(max_length, curr_length);

    if (is_left) {
      longest_zigzag_v2_dfs(node->right, false, curr_length + 1, max_length);
      longest_zigzag_v2_dfs(node->left, true, 1, max_length);
    } else {
      longest_zigzag_v2_dfs(node->left, true, curr_length + 1, max_length);
      longest_zigzag_v2_dfs(node->right, false, 1, max_length);
    }
  }

  // Bottom-up DP approach
  // Time: O(n), Space: O(h)
  int longest_zigzag_v3(TreeNode* root) {
    if (root == nullptr) {
      return -1;
    }

    int max_length = 0;
    longest_zigzag_v3_dfs(root, max_length);
    return max_length;
  }

  // Returns pair {left_length, right_length}
  // left_length: max zigzag length when starting by going left
  // right_length: max zigzag length when starting by going right
  std::pair<int, int> longest_zigzag_v3_dfs(TreeNode* node, int& max_length) {
    if (node == nullptr) {
      return {-1, -1}; // -1 to account for the null node
    }

    auto [left_left, left_right] = longest_zigzag_v3_dfs(node->left, max_length);
    auto [right_left, right_right] = longest_zigzag_v3_dfs(node->right, max_length);

    // Calculate max zigzag lengths from current node
    int left_path = left_right + 1;  // Go left then zigzag
    int right_path = right_left + 1; // Go right then zigzag

    // Update global maximum
    max_length = std::max({max_length, left_path, right_path});

    return {left_path, right_path};
  }
};
