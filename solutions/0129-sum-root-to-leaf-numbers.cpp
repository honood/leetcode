// HoNooD
// 2024.05.13

// https://leetcode.com/problems/sum-root-to-leaf-numbers/description/?envType=study-plan-v2&envId=top-interview-150

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *   int val;
 *   TreeNode *left;
 *   TreeNode *right;
 *   TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *   TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *   TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
public:
  int sumNumbers(TreeNode* root) {
    int sum = 0;
    vector<int> path{};
    traversePath(root, path, sum);
    return sum;
  }

private:
  void traversePath(TreeNode* root, vector<int>& path, int& sum) {
    if (root == nullptr) {
      return;
    }

    path.push_back(root->val);

    if (root->left == nullptr && root->right == nullptr) {
      int pathSum = 0;
      for (int i = 0; i < path.size(); ++i) {
        pathSum = pathSum * 10 + path[i];
      }
      sum += pathSum;
    } else {
      traversePath(root->left, path, sum);
      traversePath(root->right, path, sum);
    }
    
    path.pop_back();
  }
};
