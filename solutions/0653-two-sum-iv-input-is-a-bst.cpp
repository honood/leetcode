// HoNooD <honood@gmail.com>
// 2025.04.24 00:15
//
// 653. Two Sum IV - Input is a BST
// https://leetcode.com/problems/two-sum-iv-input-is-a-bst/description/

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

// // Definition for a binary tree node.
// struct TreeNode {
//   int val;
//   TreeNode* left;
//   TreeNode* right;
//   TreeNode() : val{0}, left{nullptr}, right{nullptr} {}
//   TreeNode(int x) : val{x}, left{nullptr}, right{nullptr} {}
//   TreeNode(int x, TreeNode* left, TreeNode* right)
//       : val{x}, left{left}, right{right} {}
// };

class Solution {
public:
  bool findTarget(TreeNode* root, int k) {
    return find_target_v3(root, k);
  }

private:
  // - Time complexity: O(n)
  // - Space complexity: O(n)
  bool find_target_v1(TreeNode* root, int k) {
    if (root == nullptr) {
      return false;
    }

    vector<int> nums{};
    inorder_traversal(root, nums);

    int left = 0;
    int right = nums.size() - 1;
    while (left < right) {
      int sum = nums[left] + nums[right];
      if (sum == k) {
        return true;
      } else if (sum < k) {
        ++left;
      } else {
        --right;
      }
    }

    return false;
  }

  // - Time complexity: O(n)
  // - Space complexity: O(max_tree_height) (best case O(log(n)), O(n) worst
  //   case)
  void inorder_traversal(TreeNode* root, vector<int>& nums) {
    if (root == nullptr) {
      return;
    }

    inorder_traversal(root->left, nums);
    nums.push_back(root->val);
    inorder_traversal(root->right, nums);
  }

  // - Time complexity: O(n)
  // - Space complexity: O(n)
  bool find_target_v2(TreeNode* root, int k) {
    unordered_set<int> seen_values{};
    return find(root, k, seen_values);
  }

  bool find(TreeNode* root, int k, unordered_set<int>& seen_values) {
    if (root == nullptr) {
      return false;
    }

    int complement = k - root->val;
    if (seen_values.contains(complement)) {
      return true;
    }

    seen_values.insert(root->val);

    return find(root->left, k, seen_values)
           || find(root->right, k, seen_values);
  }

  // - Time complexity: O(n)
  // - Space complexity: O(n)
  bool find_target_v2_2(TreeNode* root, int k) {
    if (root == nullptr) {
      return false;
    }

    unordered_set<int> seen_values{};
    std::queue<TreeNode*> queue{{root}};
    while (!queue.empty()) {
      TreeNode* node = queue.front();
      queue.pop();

      int complement = k - node->val;
      if (seen_values.contains(complement)) {
        return true;
      }

      seen_values.insert(node->val);

      if (node->left != nullptr) {
        queue.push(node->left);
      }
      if (node->right != nullptr) {
        queue.push(node->right);
      }
    }

    return false;
  }

  // - Time complexity: O(n)
  // - Space complexity: O(max_tree_height) (best case O(log(n)), O(n) worst
  //   case)
  bool find_target_v3(TreeNode* root, int k) {
    if (root == nullptr) {
      return false;
    }

    std::stack<TreeNode*> left_stack{}; // For forward in-order traversal
    std::stack<TreeNode*> right_stack{}; // For reverse in-order traversal

    push_left(left_stack, root);
    push_right(right_stack, root);

    TreeNode* left_node = left_stack.top();
    TreeNode* right_node = right_stack.top();
    while (left_node != right_node) { // Stop if pointers meet (or cross)
      int sum = left_node->val + right_node->val;
      if (sum == k) {
        return true;
      } else if (sum < k) {
        // Need a larger sum, advance the left pointer (get next smallest)
        left_stack.pop();
        // Push its right child and subsequent left children
        push_left(left_stack, left_node->right);
        if (left_stack.empty()) {
          // No more elements from left
          break;
        }
        left_node = left_stack.top();
      } else {
        // Need a smaller sum, advance the right pointer (get next largest)
        right_stack.pop();
        // Push its left child and subsequent right children
        push_right(right_stack, right_node->left);
        if (right_stack.empty()) {
          // No more elements from right
          break;
        }
        right_node = right_stack.top();
      }
    }

    return false;
  }

  void push_left(std::stack<TreeNode*>& stack, TreeNode* node) {
    while (node != nullptr) {
      stack.push(node);
      node = node->left;
    }
  }

  void push_right(std::stack<TreeNode*>& stack, TreeNode* node) {
    while (node != nullptr) {
      stack.push(node);
      node = node->right;
    }
  }
};
