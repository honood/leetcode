// HoNooD <honood@gmail.com>
// 2025.03.07 09:01

// 450. Delete Node in a BST
// https://leetcode.com/problems/delete-node-in-a-bst/?envType=study-plan-v2&envId=leetcode-75

// Binary search tree (BST) - Deletion
// https://en.wikipedia.org/wiki/Binary_search_tree#Deletion

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
  // Constraints:
  //   - Each node has a unique value.
  //   - `root` is a valid binary search tree.
  TreeNode* deleteNode(TreeNode* root, int key) {
    return delete_node_v1(root, key);
  }

private:
  // - Time complexity: O(h), h is the height of the tree.
  // - Space complexity: O(1)
  TreeNode* delete_node_v1(TreeNode* root, int key) {
    if (root == nullptr) {
      return nullptr;
    }

    TreeNode* parent = nullptr;
    TreeNode* to_del = root;
    while (to_del != nullptr && to_del->val != key) {
      parent = to_del;
      if (key < to_del->val) {
        to_del = to_del->left;
      } else {
        to_del = to_del->right;
      }
    }

    // Not found
    if (to_del == nullptr) {
      return root;
    }

    TreeNode* replacement = nullptr;
    if (to_del->left == nullptr) {
      replacement = to_del->right;
    } else if (to_del->right == nullptr) {
      replacement = to_del->left;
    } else {
      TreeNode* successor = to_del->right;
      TreeNode* successor_parent = to_del;
      while (successor->left != nullptr) {
        successor_parent = successor;
        successor = successor->left;
      }

      if (successor != to_del->right) {
        successor_parent->left = successor->right;
        successor->right = to_del->right;
      }

      successor->left = to_del->left;
      replacement = successor;
    }

    if (parent == nullptr) {
      root = replacement;
    } else if (parent->left == to_del) {
      parent->left = replacement;
    } else if (parent->right == to_del) {
      parent->right = replacement;
    }

    free_deleted(to_del);

    return root;
  }

  // - Time complexity: O(h), h is the height of the tree.
  // - Space complexity: O(h)
  TreeNode* delete_node_v2(TreeNode* root, int key) {
    if (root == nullptr) {
      return nullptr;
    }

    if (key < root->val) {
      root->left = delete_node_v2(root->left, key);
    } else if (key > root->val) {
      root->right = delete_node_v2(root->right, key);
    } else {
      if (root->left == nullptr) {
        TreeNode* temp = root->right;
        free_deleted(root);
        return temp;
      }

      if (root->right == nullptr) {
        TreeNode* temp = root->left;
        free_deleted(root);
        return temp;
      }

      TreeNode* successor = find_min(root->right);
      root->val = successor->val;
      root->right = delete_node_v2(root->right, successor->val);
    }

    return root;
  }

  TreeNode* find_min(TreeNode* root) {
    assert(root != nullptr);
    while (root->left != nullptr) {
      root = root->left;
    }
    return root;
  }

  // Memory management consideration：The deleted node might need to be
  // deallocated depending on the memory ownership model
  void free_deleted(TreeNode* node) {
    delete node;
  }
};
