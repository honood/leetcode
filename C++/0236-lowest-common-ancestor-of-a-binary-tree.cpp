// HoNooD <honood@gmail.com>
// 2025.03.06 15:10

// 236. Lowest Common Ancestor of a Binary Tree
// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/description/?envType=study-plan-v2&envId=leetcode-75
// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/?envType=study-plan-v2&envId=top-interview-150

// Lowest common ancestor
// https://en.wikipedia.org/wiki/Lowest_common_ancestor

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

// Definition for a binary tree node.
//
// struct TreeNode {
//   int val;
//   TreeNode* left;
//   TreeNode* right;
//   TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
// };

class Solution {
public:
  // Constraints:
  //   - The number of nodes in the tree is in the range [2, 10^5].
  //   - `p` and `q` will exist in the tree.
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    return lowest_common_ancestor_v2(root, p, q);
  }

private:
  // - Time complexity: O(n)
  // - Space complexity: O(h), h is the height of the tree.
  TreeNode* lowest_common_ancestor_v1(TreeNode* root, TreeNode* p,
                                      TreeNode* q) {
    vector<TreeNode*> path_to_p{};
    find_path_to_target(root, p, path_to_p);
    assert(!path_to_p.empty());
    vector<TreeNode*> path_to_q{};
    find_path_to_target(root, q, path_to_q);
    assert(!path_to_q.empty());

    auto result = std::mismatch(path_to_p.cbegin(), path_to_p.cend(),
                                path_to_q.cbegin(), path_to_q.cend());
    return *std::prev(result.first);

    // int i = 0;
    // while (i < path_to_p.size() && i < path_to_q.size()
    //        && path_to_p[i] == path_to_q[i]) {
    //   ++i;
    // }
    // assert(i >= 1);
    // return path_to_p[i - 1];
  }

  bool find_path_to_target(TreeNode* root, TreeNode* target,
                           vector<TreeNode*>& path) {
    if (root == nullptr) {
      return false;
    }

    path.push_back(root);

    if (root == target) {
      return true;
    }

    if (find_path_to_target(root->left, target, path)
        || find_path_to_target(root->right, target, path)) {
      return true;
    }

    // Backtrack
    path.pop_back();
    return false;
  }

  // - Time complexity: O(n)
  // - Space complexity: O(h), h is the height of the tree.
  TreeNode* lowest_common_ancestor_v2(TreeNode* root, TreeNode* p,
                                      TreeNode* q) {
    if (root == nullptr || root == p || root == q) {
      return root;
    }

    TreeNode* left_result = lowest_common_ancestor_v2(root->left, p, q);
    TreeNode* right_result = lowest_common_ancestor_v2(root->right, p, q);
    if (left_result == nullptr) {
      return right_result;
    }
    if (right_result == nullptr) {
      return left_result;
    }

    return root;
  }

  // - Time complexity: O(n)
  // - Space complexity: O(n)
  TreeNode* lowest_common_ancestor_v3(TreeNode* root, TreeNode* p,
                                      TreeNode* q) {
    unordered_map<TreeNode*, TreeNode*> child_to_parent{{root, nullptr}};
    stack<TreeNode*> stack{};

    stack.push(root);
    while (!child_to_parent.contains(p) || !child_to_parent.contains(q)) {
      TreeNode* node = stack.top();
      stack.pop();

      if (node->left != nullptr) {
        child_to_parent[node->left] = node;
        stack.push(node->left);
      }
      if (node->right != nullptr) {
        child_to_parent[node->right] = node;
        stack.push(node->right);
      }
    }

    unordered_set<TreeNode*> ancestors{};
    while (p != nullptr) {
      ancestors.insert(p);
      p = child_to_parent[p];
    }

    while (!ancestors.contains(q)) {
      q = child_to_parent[q];
    }
    return q;
  }
};
