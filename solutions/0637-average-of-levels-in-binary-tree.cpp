// HoNooD
// 2024.05.15 00:55

// 637. Average of Levels in Binary Tree
// https://leetcode.com/problems/average-of-levels-in-binary-tree/description/?envType=study-plan-v2&envId=top-interview-150

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
  vector<double> averageOfLevels(TreeNode* root) {
    if (root == nullptr) {
      return {};
    }

    vector<double> res{};
    queue<TreeNode*> q{};
    q.push(root);
    while (!q.empty()) {
      int sz = q.size();
      double sum = 0.0;
      for (int i = 0; i < sz; ++i) {
        TreeNode* node = q.front();
        q.pop();

        sum += node->val;

        if (node->left != nullptr) {
          q.push(node->left);
        }
        if (node->right != nullptr) {
          q.push(node->right);
        }
      }
      res.push_back(sum / sz);
    }

    return res;
  }
};

class Solution_2 {
public:
  vector<double> averageOfLevels(TreeNode* root) {
    vector<double> res{};
    vector<vector<int>> levelVals{};
    recursiveBFS(root, 0, levelVals);
    for (auto const& v : levelVals) {
      assert(!v.empty());
      double sum = 0.0;
      for (int const& val : v) {
        sum += val;
      }
      res.push_back(sum / v.size());
    }

    return res;
  }

private:
  void recursiveBFS(TreeNode* root, int level, vector<vector<int>>& res) {
    if (root == nullptr) {
      return;
    }

    if (res.size() <= level) {
      res.emplace_back();
    }
    res[level].push_back(root->val);

    recursiveBFS(root->left, level + 1, res);
    recursiveBFS(root->right, level + 1, res);
  }
};
