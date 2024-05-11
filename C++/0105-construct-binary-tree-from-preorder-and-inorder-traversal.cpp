// HoNooD
// 2024.05.11 14:31

// https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/?envType=study-plan-v2&envId=top-interview-150

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
  TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    if (preorder.empty()) {
      return nullptr;
    }

    int rootVal = preorder.front();
    auto inorderRootIt = std::find(inorder.cbegin(), inorder.cend(), rootVal);
    assert(inorderRootIt != inorder.cend());
    auto temp = std::next(preorder.cbegin(), std::distance(inorder.cbegin(), inorderRootIt) + 1);
    vector<int> leftSubtreePreorder{std::next(preorder.cbegin()), temp};
    vector<int> rightSubtreePreorder{temp, preorder.cend()};
    vector<int> leftSubtreeInorder(inorder.cbegin(), inorderRootIt);
    vector<int> rightSubtreeInorder(std::next(inorderRootIt), inorder.cend());

    return new TreeNode{
      rootVal, 
      buildTree(leftSubtreePreorder, leftSubtreeInorder),
      buildTree(rightSubtreePreorder, rightSubtreeInorder)
    };
  }
};

// Optimizations:
// 1. Use a helper unordered_map to accelerate finding root in inorder vector;
// 2. Use indices simulating view on vectors to reduce memory footprint.
class Solution_2 {
public:
  TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    int nodesNum = preorder.size();
    unordered_map<int, int> lookupTable{};
    lookupTable.reserve(nodesNum);
    for (int i = 0; i < nodesNum; ++i) {
      lookupTable[inorder[i]] = i;
    }

    return impl(0, nodesNum - 1, 0, nodesNum - 1, preorder, inorder, lookupTable);
  }

private:
  TreeNode* impl(
    int preorderFirstIdx, int preorderLastIdx,
    int inorderFirstIdx, int inorderLastIdx,
    vector<int> const& preorder, vector<int> const& inorder,
    unordered_map<int, int>& lookupTable
  ) {
    if (preorderFirstIdx > preorderLastIdx || inorderFirstIdx > inorderLastIdx) {
      return nullptr;
    }

    int rootVal = preorder[preorderFirstIdx];
    int inorderRootIdx = lookupTable[rootVal];
    int leftSubtreeNodesNum = inorderRootIdx - inorderFirstIdx;
    return new TreeNode{
      rootVal,
      impl(preorderFirstIdx + 1, preorderFirstIdx + leftSubtreeNodesNum, inorderFirstIdx, inorderRootIdx - 1, preorder, inorder, lookupTable),
      impl(preorderFirstIdx + leftSubtreeNodesNum + 1, preorderLastIdx, inorderRootIdx + 1, inorderLastIdx, preorder, inorder, lookupTable)
    };
  }
};
