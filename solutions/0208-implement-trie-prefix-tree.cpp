// HoNooD <honood@gmail.com>
// 2024.06.27 19:00

// 208. Implement Trie (Prefix Tree)
// https://leetcode.com/problems/implement-trie-prefix-tree/description/?envType=study-plan-v2&envId=top-interview-150
// https://leetcode.com/problems/implement-trie-prefix-tree/?envType=study-plan-v2&envId=leetcode-75

// trie / digital tree / prefix tree
// https://en.wikipedia.org/wiki/Trie
//
// radix tree
// https://en.wikipedia.org/wiki/Radix_tree

namespace v1 {
class Trie;
}
namespace v2 {
class Trie;
}

using Trie = v1::Trie;

namespace v1 {

class Trie {
public:
  Trie() : root_{new Node{}} {}
  ~Trie() {
    destroy_bfs_iterative();
    // destroy_dfs_iterative();
    // destroy_dfs_recursive(root_);
  }

  void insert(string word) {
    Node* curr = root_;
    for (auto const& c : word) {
      if (!curr->children.contains(c)) {
        curr->children[c] = new Node{};
      }
      curr = curr->children[c];
    }
    curr->is_end = true;
  }

  bool search(string word) {
    Node* curr = root_;
    for (auto const& c : word) {
      if (!curr->children.contains(c)) {
        return false;
      }
      curr = curr->children[c];
    }

    return curr->is_end;
  }

  bool startsWith(string prefix) {
    Node* curr = root_;
    for (auto const& c : prefix) {
      if (!curr->children.contains(c)) {
        return false;
      }
      curr = curr->children[c];
    }

    return true;
  }

private:
  struct Node {
    unordered_map<char, Node*> children{};
    bool is_end{false};
  };

  void destroy_bfs_iterative() {
    if (root_ == nullptr) {
      return;
    }

    queue<Node*> q{};
    q.emplace(root_);
    while (!q.empty()) {
      Node* curr = q.front();
      q.pop();

      for (auto const& [_, child] : curr->children) {
        if (child != nullptr) {
          q.emplace(child);
        }
      }

      delete curr;
    }
  }

  void destroy_dfs_iterative() {
    if (root_ == nullptr) {
      return;
    }

    stack<Node*> stack{};
    stack.emplace(root_);
    while (!stack.empty()) {
      Node* curr = stack.top();
      stack.pop();

      for (auto const& [_, child] : curr->children) {
        if (child != nullptr) {
          stack.emplace(child);
        }
      }

      delete curr;
    }
  }

  void destroy_dfs_recursive(Node* node) {
    if (node == nullptr) {
      return;
    }

    for (auto const& [_, child] : node->children) {
      destroy_dfs_recursive(child);
    }
    delete node;
  }

  Node* root_;
};

} // namespace v1

namespace v2 {

// Utilize `std::unique_ptr` for managing `Node*` pointers, introduced in C++11,
// to ensure automatic and exception-safe memory management.
class Trie {
public:
  Trie() : root_{make_unique<Node>()} {}

  void insert(string word) {
    Node* curr = root_.get();
    for (auto const& c : word) {
      if (!curr->children.contains(c)) {
        curr->children[c] = make_unique<Node>();
      }
      curr = curr->children[c].get();
    }
    curr->is_end = true;
  }

  bool search(string word) {
    Node* curr = root_.get();
    for (auto const& c : word) {
      if (!curr->children.contains(c)) {
        return false;
      }
      curr = curr->children[c].get();
    }

    return curr->is_end;
  }

  bool startsWith(string prefix) {
    Node* curr = root_.get();
    for (auto const& c : prefix) {
      if (!curr->children.contains(c)) {
        return false;
      }
      curr = curr->children[c].get();
    }

    return true;
  }

private:
  struct Node {
    unordered_map<char, unique_ptr<Node>> children{};
    bool is_end{false};
  };

  unique_ptr<Node> root_;
};

} // namespace v2

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
