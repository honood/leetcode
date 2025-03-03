// HoNooD <honood@gmail.com>
// 2025.03.03 17:27

// 872. Leaf-Similar Trees
// https://leetcode.com/problems/leaf-similar-trees/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

// Definition for a binary tree node.
// struct TreeNode {
//   int val;
//   TreeNode *left;
//   TreeNode *right;
//   TreeNode() : val(0), left(nullptr), right(nullptr) {}
//   TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//   TreeNode(int x, TreeNode* left, TreeNode* right)
//       : val(x), left(left), right(right) {}
// };

class Solution {
public:
  bool leafSimilar(TreeNode* root1, TreeNode* root2) {
    return leaf_similar_v3(root1, root2);
  }

private:
  bool leaf_similar_v1(TreeNode* root1, TreeNode* root2) {
    vector<int> leaf_value_sequence1{};
    leaf_similar_v1_helper(root1, leaf_value_sequence1);

    vector<int> leaf_value_sequence2{};
    leaf_similar_v1_helper(root2, leaf_value_sequence2);

    return leaf_value_sequence1 == leaf_value_sequence2;
  }

  void leaf_similar_v1_helper(TreeNode* root,
                              vector<int>& leaf_value_sequence) {
    if (root == nullptr) {
      return;
    }

    if (root->left == nullptr && root->right == nullptr) {
      leaf_value_sequence.push_back(root->val);
      return;
    }

    leaf_similar_v1_helper(root->left, leaf_value_sequence);
    leaf_similar_v1_helper(root->right, leaf_value_sequence);
  }

  bool leaf_similar_v2(TreeNode* root1, TreeNode* root2) {
    return leaf_similar_v2_helper(root1) == leaf_similar_v2_helper(root2);
  }

  vector<int> leaf_similar_v2_helper(TreeNode* root) {
    if (root == nullptr) {
      return {};
    }

    vector<int> leaf_value_sequence{};
    std::stack<TreeNode*> stack{{root}};

    while (!stack.empty()) {
      auto node = stack.top();
      stack.pop();

      if (node->left == nullptr && node->right == nullptr) {
        leaf_value_sequence.push_back(node->val);
        continue;
      }

      if (node->right != nullptr) {
        stack.push(node->right);
      }
      if (node->left != nullptr) {
        stack.push(node->left);
      }
    }

    return leaf_value_sequence;
  }

  bool leaf_similar_v3(TreeNode* root1, TreeNode* root2) {
    if (root1 == nullptr || root2 == nullptr) {
      return root1 == root2;
    }

    std::stack<TreeNode*> stack1{{root1}};
    std::stack<TreeNode*> stack2{{root2}};
    while (!stack1.empty() && !stack2.empty()) {
      auto leaf1 = get_next_leaf_value(stack1);
      auto leaf2 = get_next_leaf_value(stack2);
      if (!leaf1 || !leaf2 || leaf1 != leaf2) {
        return false;
      }
    }

    return stack1.empty() && stack2.empty();
  }

  // Constraints:
  //   - Both of the given trees will have values in the range `[0, 200]`.
  std::optional<int> get_next_leaf_value(std::stack<TreeNode*>& stack) {
    while (!stack.empty()) {
      auto node = stack.top();
      stack.pop();

      if (node->left == nullptr && node->right == nullptr) {
        return node->val;
      }

      if (node->right != nullptr) {
        stack.push(node->right);
      }
      if (node->left != nullptr) {
        stack.push(node->left);
      }
    }

    return std::nullopt;
  }
};
