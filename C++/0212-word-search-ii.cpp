// HoNooD <honood@gmail.com>
// 2024.06.28 21:29

// 212. Word Search II
// https://leetcode.com/problems/word-search-ii/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// Note:
// 1. `board[i][j]` is a lowercase English letter.
// 2. `words[i]` consists of lowercase English letters.
class Solution {
public:
  vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
    if (words.empty() || board.empty() || board[0].empty()) {
      return {};
    }

    int m = board.size();
    int n = board[0].size();
    unordered_map<char, vector<pair<int, int>>> board_uniq_char_coords{};
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        board_uniq_char_coords[board[i][j]].emplace_back(i, j);
      }
    }

    int max_word_len = m * n;
    unordered_set<string> uniq_words{};
    for (auto& word : words) {
      if (word.size() > max_word_len) {
        continue;
      }

      int word_char_freq[26]{};
      bool must_not_found = false;
      for (auto const& c : word) {
        ++word_char_freq[c - 'a'];
        if (word_char_freq[c - 'a'] > board_uniq_char_coords[c].size()) {
          must_not_found = true;
          continue;
        }
      }
      if (must_not_found) {
        continue;
      }

      uniq_words.emplace(std::move(word));
    }

    if (uniq_words.empty()) {
      return {};
    }

    vector<string> res{};
    TrieNode* root = buildTrie(uniq_words);
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        dfs(board, i, j, root, res);
      }
    }

    destroyTrie(root);
    return res;
  }

private:
  struct TrieNode {
    TrieNode* children[26]{};
    string word{};
  };

  int const directions[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

  void dfs(vector<vector<char>>& board, int row, int col, TrieNode* node, vector<string>& res) {
    char c = board[row][col];
    assert(node != nullptr);
    node = node->children[c - 'a'];
    if (node == nullptr) {
      return;
    }

    if (!node->word.empty()) {
      res.emplace_back(std::move(node->word));
      node->word.clear();
    }

    board[row][col] = '#'; // mark the cell as visited
    for (auto const& [dRow, dCol] : directions) {
      int newRow = row + dRow;
      int newCol = col + dCol;
      if (newRow >= 0 && newRow < board.size() &&
          newCol >= 0 && newCol < board[0].size() &&
          board[newRow][newCol] != '#') {
        dfs(board, newRow, newCol, node, res);
      }
    }
    board[row][col] = c; // restore the cell
  }

  TrieNode* buildTrie(unordered_set<string>& uniq_words) {
    TrieNode* root = new TrieNode{};
    assert(root != nullptr);
    for (auto const& word : uniq_words) {
      TrieNode* node = root;
      for (auto const& c : word) {
        if (node->children[c - 'a'] == nullptr) {
          node->children[c - 'a'] = new TrieNode{};
        }
        node = node->children[c - 'a'];
      }
      node->word = word;
    }

    return root;
  }

  void destroyTrie(TrieNode* root) {
    if (root == nullptr) {
      return;
    }

    for (auto const& child : root->children) {
      destroyTrie(child);
    }
    delete root;
  }
};
