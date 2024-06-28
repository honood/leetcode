// HoNooD <honood@gmail.com>
// 2024.06.28 08:30

// 211. Design Add and Search Words Data Structure
// https://leetcode.com/problems/design-add-and-search-words-data-structure/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class WordDictionary {
public:
  WordDictionary() : root_{make_unique<TrieNode>()} {}

  void addWord(string const& word) {
    assert(std::none_of(word.cbegin(), word.cend(), [](char const& c) {
      return c == '.';
    }));

    TrieNode* curr = root_.get();
    for (char c : word) {
      if (!curr->children.contains(c)) {
        curr->children[c] = make_unique<TrieNode>();
      }
      curr = curr->children[c].get();
    }
    curr->is_end = true;
  }

  bool search(string const& word) {
    return search_recursive(word, 0, root_.get());
    // return search_iterative(word);
  }

private:
  struct TrieNode {
    std::unordered_map<char, unique_ptr<TrieNode>> children{};
    bool is_end{false};
  };

  bool search_recursive(string const& word, int index, TrieNode* node) const {
    // Note: NO need to check if `node` is `nullptr` because:
    // 1. `node` is always valid as it is passed from a valid parent;
    // 2. `node->children.contains()` checks existence before dereferencing.
    if (index == word.size()) {
      return node->is_end;
    }

    char c = word[index];
    if (c != '.') {
      if (node->children.contains(c)) {
        return search_recursive(word, index + 1, node->children[c].get());
      }
    } else {
      for (auto const& [_, child] : node->children) {
        if (search_recursive(word, index + 1, child.get())) {
          return true;
        }
      }
    }

    return false;
  }

  bool search_iterative(string const& word) const {
    // Note: alternatively, a `std::queue` can be employed for similar purposes:
    // queue<pair<TrieNode*, int>> to_visit{};
    stack<pair<TrieNode*, int>> to_visit{};
    to_visit.emplace(root_.get(), 0);
    while (!to_visit.empty()) {
      // Note: for `std::queue`, replace the following line with:
      // auto [node, index] = to_visit.front();
      auto [node, index] = to_visit.top();
      to_visit.pop();

      if (index == word.size()) {
        if (node->is_end) {
          return true;
        }
        continue;
      }

      char c = word[index];
      if (c != '.') {
        if (node->children.contains(c)) {
          to_visit.emplace(node->children[c].get(), index + 1);
        }
      } else {
        for (auto const& [_, child] : node->children) {
          to_visit.emplace(child.get(), index + 1);
        }
      }
    } // while

    return false;
  }

  unique_ptr<TrieNode> root_;
};

// manually managing memory
class WordDictionary_2 {
public:
  WordDictionary() : root_{new TrieNode{}} {}
  ~WordDictionary() {
    delete root_;
  }

  void addWord(string const& word) {
    assert(std::none_of(word.cbegin(), word.cend(), [](char const& c) {
      return c == '.';
    }));

    TrieNode* curr = root_;
    for (char c : word) {
      if (!curr->children.contains(c)) {
        curr->children[c] = new TrieNode{};
      }
      curr = curr->children[c];
    }
    curr->is_end = true;
  }

  bool search(string const& word) {
    return search_in_node(word, 0, root_);
  }

private:
  struct TrieNode {
    std::unordered_map<char, TrieNode*> children{};
    bool is_end{false};

    // Note: Although the `TrieNode` class doesn’t inherently verify the
    // allocation method of its children, the design relies on the assumption
    // and consistency that children are created with `new`. Therefore, using
    // `delete` in the destructor is considered safe in this context, adhering
    // to C++ memory management conventions.
    ~TrieNode() {
      for (auto const& [_, child] : children) {
        delete child;
      }
    }
  };

  bool search_in_node(string const& word, int index, TrieNode* node) const {
    // Note: NO need to check if `node` is `nullptr` because:
    // 1. `node` is always valid as it is passed from a valid parent;
    // 2. `node->children.contains()` checks existence before dereferencing.
    if (index == word.size()) {
      return node->is_end;
    }

    char c = word[index];
    if (c != '.') {
      if (node->children.contains(c)) {
        return search_in_node(word, index + 1, node->children[c]);
      }
    } else {
      for (auto const& [_, child] : node->children) {
        if (search_in_node(word, index + 1, child)) {
          return true;
        }
      }
    }

    return false;
  }

  TrieNode* root_;
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */
