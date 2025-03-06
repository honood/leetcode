// HoNooD
// 2024.05.12 15:50

// https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/description/?envType=study-plan-v2&envId=top-interview-150
// https://leetcode.com/problems/populating-next-right-pointers-in-each-node/description/

/*
// Definition for a Node.
class Node {
public:
  int val;
  Node* left;
  Node* right;
  Node* next;

  Node() : val(0), left(NULL), right(NULL), next(NULL) {}
  Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}
  Node(int _val, Node* _left, Node* _right, Node* _next)
    : val(_val), left(_left), right(_right), next(_next) {}
};
*/
class Solution {
public:
  Node* connect(Node* root) {
    if (root == nullptr) {
      return nullptr;
    }

    queue<Node*> queue{};
    queue.push(root);
    while (!queue.empty()) {
      Node* prev = nullptr;
      int sz = queue.size();
      for (int i = 0; i < sz; ++i) {
        Node* node = queue.front();
        queue.pop();
        if (prev != nullptr) {
          prev->next = node;
        }
        prev = node;
        // No need to set the `next` pointer of the last node in each level 
        // as `nullptr`, because it is.
        // if (i == sz - 1) {
        //   node->next = nullptr;
        // }

        if (node->left != nullptr) {
          queue.push(node->left);
        }
        if (node->right != nullptr) {
          queue.push(node->right);
        }
      } // for
    } // while

    return root;
  }
};

//       1
//      / \
//     2   3
//    /\    \
//   4  5    7
//  /   \   /
// 8     9 10
// 
class Solution_2 {
public:
  Node* connect(Node* root) {
    if (root == nullptr) {
      return nullptr;
    }

    Node* curr_level_head = root;
    Node* first_child = nullptr;
    Node* curr_child = nullptr;
    do {
      while (curr_level_head != nullptr) {
        for (Node* child : {curr_level_head->left, curr_level_head->right}) {
          if (child != nullptr) {
            if (curr_child != nullptr) {
              curr_child->next = child;
            } else {
              first_child = child;
            }
            curr_child = child;
          }
        }
        
        curr_level_head = curr_level_head->next;
      } // while

      if (first_child == nullptr) {
        break;
      }

      curr_level_head = first_child;
      first_child = nullptr;
      curr_child = nullptr;
    } while (true);

    return root;
  }
};
