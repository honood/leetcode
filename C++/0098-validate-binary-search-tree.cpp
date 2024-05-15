// HoNooD
// 2024.05.15 15:55

// 98. Validate Binary Search Tree
// https://leetcode.com/problems/validate-binary-search-tree/description/?envType=study-plan-v2&envId=top-interview-150

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
public:
  bool isValidBST(TreeNode* root) {
    assert(root != nullptr);

    stack<TreeNode*> stack{};
    TreeNode* curr = root;
    TreeNode* prev = nullptr;
    while (curr != nullptr || !stack.empty()) {
      while (curr != nullptr) {
        stack.push(curr);
        curr = curr->left;
      }

      curr = stack.top();
      stack.pop();

      if (prev != nullptr && prev->val >= curr->val) {
        return false;
      }
      prev = curr;

      curr = curr->right;
    }

    return true;
  }
};

class Solution_2 {
public:
  bool isValidBST(TreeNode* root) {
    assert(root != nullptr);

    bool valid = true;
    TreeNode* prev = nullptr;
    inorderDFS(root, prev, valid);
    return valid;
  }

private:
  void inorderDFS(TreeNode* root, TreeNode*& prev, bool& valid) {
    if (!valid || root == nullptr) {
      return;
    }

    inorderDFS(root->left, prev, valid);
    if (prev != nullptr && prev->val >= root->val) {
      valid = false;
      return;
    }
    prev = root;
    inorderDFS(root->right, prev, valid);
  }
};

class Solution_3 {
public:
  bool isValidBST(TreeNode* root) {
    assert(root != nullptr);
    // Note: 
    // 
    // 1. Will get incorrect result when using `std::numeric_limits<int>::max()` 
    // as `maxVal` for single node tree whose `val` is `2147483647` (i.e. 
    // `std::numeric_limits<int>::max()`).
    // 
    // 2. Will get incorrect result when using `std::numeric_limits<int>::min()` 
    // as `maxVal` for single node tree whose `val` is `-2147483648` (i.e. 
    // `std::numeric_limits<int>::min()`).
    return impl(root, std::numeric_limits<long>::min(), std::numeric_limits<long>::max());
  }

private:
  bool impl(TreeNode* root, long minVal, long maxVal) {
    if (root == nullptr) {
      return true;
    }

    if (root->val <= minVal || root->val >= maxVal) {
      return false;
    }

    return impl(root->left, minVal, root->val) && impl(root->right, root->val, maxVal);
  }
};
