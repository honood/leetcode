// HoNooD <honood@gmail.com>
// 2025.03.07 01:05

// 1161. Maximum Level Sum of a Binary Tree
// https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree/description/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// Definition for a binary tree node.
//
// struct TreeNode {
//   int val;
//   TreeNode* left;
//   TreeNode* right;
//   TreeNode() : val(0), left(nullptr), right(nullptr) {}
//   TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//   TreeNode(int x, TreeNode* left, TreeNode* right)
//       : val(x), left(left), ght(right) {}
// };

class Solution {
public:
  int maxLevelSum(TreeNode* root) {
    return max_level_sum_v1(root);
  }

private:
  // Level-order traversal (BFS)
  int max_level_sum_v1(TreeNode* root) {
    if (root == nullptr) {
      return 0;
    }

    int curr_level = 1;
    int max_level = 1;
    int max_sum = root->val;

    std::queue<TreeNode*> queue{{root}};
    while (!queue.empty()) {
      int level_sum = 0;
      int level_size = queue.size();

      for (int i = 0; i < level_size; ++i) {
        TreeNode* node = queue.front();
        queue.pop();

        level_sum += node->val;
        if (node->left) {
          queue.push(node->left);
        }
        if (node->right) {
          queue.push(node->right);
        }
      }

      if (level_sum > max_sum) {
        max_sum = level_sum;
        max_level = curr_level;
      }

      ++curr_level;
    }

    return max_level;
  }

  // Depth-First Search (DFS)
  int max_level_sum_v2(TreeNode* root) {
    vector<int> level_sums{};
    max_level_sum_v2_dfs(root, 0, level_sums);

    int max_level = 0;
    int max_sum = std::numeric_limits<int>::min();

    for (int i = 0; i < level_sums.size(); ++i) {
      if (level_sums[i] > max_sum) {
        max_sum = level_sums[i];
        max_level = i;
      }
    }

    // Level is 1-indexed in the problem
    return max_level + 1;
  }

  void max_level_sum_v2_dfs(TreeNode* node, int level,
                            vector<int>& level_sums) {
    if (node == nullptr) {
      return;
    }

    // Expand level_sums if needed
    if (level >= level_sums.size()) {
      level_sums.resize(level + 1, 0);
    }

    // Add current node's value to its level sum
    level_sums[level] += node->val;

    max_level_sum_v2_dfs(node->left, level + 1, level_sums);
    max_level_sum_v2_dfs(node->right, level + 1, level_sums);
  }
};
