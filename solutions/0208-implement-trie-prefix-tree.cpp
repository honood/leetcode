// HoNooD <honood@gmail.com>
// 2024.06.27 19:00
// 2025.04.18 18:35

// 208. Implement Trie (Prefix Tree)
// https://leetcode.com/problems/implement-trie-prefix-tree/description/?envType=study-plan-v2&envId=top-interview-150
// https://leetcode.com/problems/implement-trie-prefix-tree/?envType=study-plan-v2&envId=leetcode-75

// https://en.wikipedia.org/wiki/Trie
// https://en.wikipedia.org/wiki/Radix_tree
// https://en.wikipedia.org/wiki/Suffix_tree
// https://en.wikipedia.org/wiki/Ternary_search_tree

namespace trie {

namespace v1 {
class Trie;
}

namespace v2 {
class Trie;
}

} // namespace trie

using namespace trie::v1;

namespace trie::v1 {
// clang-format off
class Trie {
private:
  struct Node {
    std::unordered_map<char, Node*> children;
    bool isEndOfWord;

    Node() : isEndOfWord{false} {}
    ~Node() {
      for (auto const& [c, child] : children) {
        delete child;
      }
    }

    // Disable copy and move operations
    Node(Node const&) = delete;
    Node& operator=(Node const&) = delete;
    Node(Node&&) = delete;
    Node& operator=(Node&&) = delete;
  };

  Node* root_;

public:
  Trie() : root_{new Node{}} {}
  ~Trie() {
    delete root_;
  }

  void insert(std::string const& word) const {
    Node* curr = root_;
    for (char c : word) {
      if (!curr->children.contains(c)) {
        curr->children.emplace(c, new Node{});
      }
      curr = curr->children[c];
    }
    curr->isEndOfWord = true;
  }

  [[nodiscard]] bool search(std::string const& word) const {
    Node* node = findNode(word);
    return node != nullptr && node->isEndOfWord;
  }

  [[nodiscard]] bool startsWith(std::string const& prefix) const {
    return findNode(prefix) != nullptr;
  }

  void remove(std::string const& word) {
    removeHelper(root_, word, 0);
  }

  [[nodiscard]] std::vector<std::string> getAllWords() const {
    std::vector<std::string> result{};
    std::string currWord{};
    collectWords(root_, currWord, result);
    return result;
  }

  [[nodiscard]] std::vector<std::string> getWordsWithPrefix(std::string const& prefix) const {
    std::vector<std::string> result{};
    Node* prefixNode = findNode(prefix);
    if (prefixNode != nullptr) {
      std::string currWord = prefix;
      collectWords(prefixNode, currWord, result);
    }
    return result;
  }

private:
  [[nodiscard]] Node* findNode(std::string const& str) const {
    Node* curr = root_;
    for (char c : str) {
      if (!curr->children.contains(c)) {
        return nullptr;
      }
      curr = curr->children[c];
    }
    return curr;
  }

  // Traverses the Trie based on the characters in `word`. After reaching the
  // end of the word, it potentially unmarks the node. Then, on the way back up
  // the recursion stack, it checks if nodes have become redundant (no children
  // and not marking the end of another word) and can be deleted.
  //
  // Return true if the current `node` should be deleted by its parent, false
  // otherwise.
  bool removeHelper(Node* node, std::string const& word, int depth) {
    if (depth == word.length()) {
      if (!node->isEndOfWord) {
        return false;
      }

      node->isEndOfWord = false;
      return node->children.empty();
    }

    char c = word[depth];
    if (!node->children.contains(c)) {
      return false;
    }

    Node* child = node->children[c];
    bool shouldDeleteChild = removeHelper(child, word, depth + 1);
    if (shouldDeleteChild) {
      delete child;
      node->children.erase(c);

      return !node->isEndOfWord && node->children.empty();
    }

    return false;
  }

  void collectWords(Node* node, std::string& currentWord, std::vector<std::string>& result) const {
    if (node->isEndOfWord) {
      result.emplace_back(currentWord);
    }

    for (auto const& [c, child] : node->children) {
      currentWord.push_back(c);
      collectWords(child, currentWord, result);
      currentWord.pop_back();
    }
  }
};
// clang-format on
} // namespace trie::v1

namespace trie::v2 {
class Trie {
private:
  struct Node {
    Node* children[26];
    bool isEndOfWord;

    Node() : isEndOfWord{false} {
      for (int i = 0; i < 26; ++i) {
        children[i] = nullptr;
      }
    }

    ~Node() {
      for (int i = 0; i < 26; ++i) {
        delete children[i];
      }
    }

    // Disable copy and move operations
    Node(Node const&) = delete;
    Node& operator=(Node const&) = delete;
    Node(Node&&) = delete;
    Node& operator=(Node&&) = delete;
  };

  Node* root_;

public:
  Trie() : root_{new Node{}} {}
  ~Trie() {
    delete root_;
  }

  void insert(std::string const& word) {
    Node* curr = root_;
    for (char c : word) {
      int index = c - 'a';
      if (curr->children[index] == nullptr) {
        curr->children[index] = new Node{};
      }
      curr = curr->children[index];
    }
    curr->isEndOfWord = true;
  }

  bool search(std::string const& word) {
    Node* node = findNode(word);
    return node != nullptr && node->isEndOfWord;
  }

  bool startsWith(std::string const& prefix) {
    return findNode(prefix) != nullptr;
  }

private:
  Node* findNode(std::string const& key) {
    Node* curr = root_;
    for (char c : key) {
      int index = c - 'a';
      if (curr->children[index] == nullptr) {
        return nullptr;
      }
      curr = curr->children[index];
    }
    return curr;
  }
};
} // namespace trie::v2

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
