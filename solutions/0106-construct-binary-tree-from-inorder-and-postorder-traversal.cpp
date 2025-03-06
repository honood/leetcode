// HoNooD
// 2024.05.12 15:08

// https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/description/?envType=study-plan-v2&envId=top-interview-150

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *   int val;
 *   TreeNode *left;
 *   TreeNode *right;
 *   TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *   TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *   TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
  TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    if (inorder.empty()) {
      return nullptr;
    }

    int n = inorder.size();
    unordered_map<int, int> lookup{};
    lookup.reserve(n);
    for (int i = 0; i < n; ++i) {
      lookup[inorder[i]] = i;
    }

    return impl(0, n - 1, 0, n - 1, inorder, postorder, lookup);
  }

private:
  TreeNode* impl(int ifirst, int ilast, 
                 int pfirst, int plast, 
                 vector<int> const& inorder, 
                 vector<int> const& postorder, 
                 unordered_map<int, int> const& lookup) {
    if (ifirst > ilast || pfirst > plast) {
      return nullptr;
    }

    int rootVal = postorder[plast];
    int rootIdx = lookup.at(rootVal);
    int lsubtreeCnt = rootIdx - ifirst;

    return new TreeNode{
      rootVal,
      impl(ifirst, rootIdx - 1, pfirst, pfirst + lsubtreeCnt - 1, inorder, postorder, lookup),
      impl(rootIdx + 1, ilast, pfirst + lsubtreeCnt, plast - 1, inorder, postorder, lookup)
    };
  }
};
