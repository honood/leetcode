// HoNooD
// 2024.05.10 15:55

#include <iostream>
#include <vector>

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;

  explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void traverse_paths(TreeNode* root, std::vector<int>& path) {
  if (root == nullptr) {
    return;
  }

  path.push_back(root->val);

  if (root->left == nullptr && root->right == nullptr) {
    std::cout << "Path: ";
    for (int val: path) {
      std::cout << val << " ";
    }
    std::cout << '\n';
  } else {
    if (root->left != nullptr) {
      traverse_paths(root->left, path);
    }
    if (root->right != nullptr) {
      traverse_paths(root->right, path);
    }
  }

  path.pop_back();
}

int main() {
#define CREATE_NODE(val) TreeNode* node_##val = new TreeNode(val);
  CREATE_NODE(1);
  CREATE_NODE(2);
  CREATE_NODE(3);
  CREATE_NODE(4);
  CREATE_NODE(5);
  CREATE_NODE(6);
  CREATE_NODE(7);
  CREATE_NODE(8);
  CREATE_NODE(9);
  CREATE_NODE(10);
  CREATE_NODE(11);

  TreeNode* root = node_6;
  node_6->left = node_2;
  node_6->right = node_7;
  node_2->left = node_1;
  node_2->right = node_5;
  node_5->left = node_3;
  node_3->right = node_4;
  node_7->right = node_10;
  node_10->left = node_9;
  node_10->right = node_11;
  node_9->left = node_8;

  std::vector<int> path;
  traverse_paths(root, path);

  delete node_1;
  delete node_2;
  delete node_3;
  delete node_4;
  delete node_5;
  delete node_6;
  delete node_7;
  delete node_8;
  delete node_9;
  delete node_10;
  delete node_11;

  return 0;
}

// Path: 6 2 1 
// Path: 6 2 5 3 4 
// Path: 6 7 10 9 8 
// Path: 6 7 10 11 
