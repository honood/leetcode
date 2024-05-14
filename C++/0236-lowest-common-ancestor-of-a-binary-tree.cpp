// HoNooD
// 2024.05.14 17:03

// 236. Lowest Common Ancestor of a Binary Tree
// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/?envType=study-plan-v2&envId=top-interview-150
// https://en.wikipedia.org/wiki/Lowest_common_ancestor

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == nullptr || root == p || root == q) {
      return root;
    }

    TreeNode* leftRes = lowestCommonAncestor(root->left, p, q);
    TreeNode* rightRes = lowestCommonAncestor(root->right, p, q);
    if (leftRes == nullptr) {
      return rightRes;
    }
    if (rightRes == nullptr) {
      return leftRes;
    }

    return root;
  }
};

class Solution_2 {
public:
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    unordered_map<TreeNode*, TreeNode*> childToParent{{root, nullptr}};
    stack<TreeNode*> stack{};

    stack.push(root);
    while (!childToParent.contains(p) || !childToParent.contains(q)) {
      TreeNode* node = stack.top();
      stack.pop();
      if (node->left != nullptr) {
        childToParent[node->left] = node;
        stack.push(node->left);
      }
      if (node->right != nullptr) {
        childToParent[node->right] = node;
        stack.push(node->right);
      }
    }

    unordered_map<TreeNode*, bool> ancestors{};
    while (p != nullptr) {
      ancestors[p] = true;
      p = childToParent[p];
    }

    while (!ancestors.contains(q)) {
      q = childToParent[q];
    }
    return q;
  }
};
