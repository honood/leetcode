// HoNooD
// 2024.05.27 09:36

// 79. Word Search
// https://leetcode.com/problems/word-search/description/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Backtracking

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  bool exist(vector<vector<char>>& board, string word) {
    if (board.empty()) {
      return false;
    }

    int rows = board.size();
    int cols = board[0].size();

    if (word.empty()) {
      return true;
    }

    if (rows * cols < word.size()) {
      return false;
    }

    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        bool found = dfs(board, word, 0, i, j);
        if (found) {
          return true;
        }
      }
    }

    return false;
  }

private:
  bool dfs(vector<vector<char>>& board, string const& word, int index, int row, int col) {
    assert(!board.empty() && !word.empty());

    if (word.size() == index) {
      return true;
    }

    if (row < 0 || row >= board.size() || col < 0 || col >= board[0].size() || board[row][col] != word[index]) {
      return false;
    }

    // Mark the current cell as visited by changing its value
    char backup = board[row][col];
    board[row][col] = '#';

    // Explore the neighbors in DFS manner
    bool found = dfs(board, word, index + 1, row - 1, col) || // top
                 dfs(board, word, index + 1, row, col - 1) || // left
                 dfs(board, word, index + 1, row + 1, col) || // bottom
                 dfs(board, word, index + 1, row, col + 1);   // right

    // Restore the cell value after DFS
    board[row][col] = backup;

    return found;
  }
};
