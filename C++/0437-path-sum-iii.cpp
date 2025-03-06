// HoNooD <honood@gmail.com>
// 2025.03.05 19:03

// 437. Path Sum III
// https://leetcode.com/problems/path-sum-iii/?envType=study-plan-v2&envId=leetcode-75

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
  int pathSum(TreeNode* root, int targetSum) {
    return path_sum_v2(root, targetSum);
  }

private:
  // Double recursion
  //
  // - Time complexity: O(n^2)
  // - Space complexity: O(h), h is the height of the tree.
  int path_sum_v1(TreeNode* root, int target_sum) {
    if (root == nullptr) {
      return 0;
    }

    // clang-format off
    return count_paths(root, target_sum)
           + path_sum_v1(root->left, target_sum)
           + path_sum_v1(root->right, target_sum);
    // clang-format on
  }

  // Constraints:
  //   - `-10^9 <= Node.val <= 10^9`
  int count_paths(TreeNode* root, long target_sum) {
    if (root == nullptr) {
      return 0;
    }

    int count = root->val == target_sum ? 1 : 0;

    // Note: Use `long` type to avoid integer overflow since `Node.val` can
    // exceed `int` range.
    long remaining = target_sum - root->val;
    count += count_paths(root->left, remaining);
    count += count_paths(root->right, remaining);

    return count;
  }

  // Prefix sum + Hash Map + Backtrack
  //
  // - Time complexity: O(n)
  // - Space complexity: O(h), h is the height of the tree.
  int path_sum_v2(TreeNode* root, int target_sum) {
    unordered_map<long, int> prefix_sum_freq{{0, 1}};
    return dfs(root, 0, target_sum, prefix_sum_freq);
  }

  int dfs(TreeNode* root, long curr_sum, int target_sum,
          unordered_map<long, int>& prefix_sum_freq) {
    if (root == nullptr) {
      return 0;
    }

    curr_sum += root->val;

    long complement_sum = curr_sum - target_sum;
    int count = prefix_sum_freq[complement_sum];

    ++prefix_sum_freq[curr_sum];

    count += dfs(root->left, curr_sum, target_sum, prefix_sum_freq);
    count += dfs(root->right, curr_sum, target_sum, prefix_sum_freq);

    --prefix_sum_freq[curr_sum];

    return count;
  }
};
