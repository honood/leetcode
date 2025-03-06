// HoNooD
// 2024.05.16 14:43

// 130. Surrounded Regions
// https://leetcode.com/problems/surrounded-regions/description/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Adjacency_matrix
// https://en.wikipedia.org/wiki/Adjacency_list
// https://en.wikipedia.org/wiki/Connectivity_(graph_theory)
// https://en.wikipedia.org/wiki/Graph_theory
// https://en.wikipedia.org/wiki/Glossary_of_graph_theory

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  void solve(vector<vector<char>>& board) {
    if (board.empty()) {
      return;
    }

    int rows = board.size();
    int cols = board[0].size();

    // Check and mark 'O's on the borders and connected 'O's
    for (int i = 0; i < rows; ++i) {
      if (board[i][0] == 'O') {
        dfs(board, i, 0);
      }
      if (board[i][cols - 1] == 'O') {
        dfs(board, i, cols - 1);
      }
    }

    for (int j = 0; j < cols; ++j) {
      if (board[0][j] == 'O') {
        dfs(board, 0, j);
      }
      if (board[rows - 1][j] == 'O') {
        dfs(board, rows - 1, j);
      }
    }

    // Flip 'O's to 'X's and revert 'V's back to 'O's
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        if (board[i][j] == 'O') {
          board[i][j] = 'X';
        } else if (board[i][j] == visited_) {
          board[i][j] = 'O';
        }
      }
    }
  }

private:
  void dfs(vector<vector<char>>& board, int row, int col) {
    if (board.empty()) {
      return;
    }

    int rows = board.size();
    int cols = board[0].size();
    if (row < 0 || row >= rows || col < 0 || col >= cols || board[row][col] != 'O') {
      return;
    }

    // Mark as visited
    board[row][col] = visited_;

    // DFS in all four directions
    dfs(board, row - 1, col); // top
    dfs(board, row, col - 1); // left
    dfs(board, row + 1, col); // bottom
    dfs(board, row, col + 1); // right
  }

  char const visited_{'V'};
};

class Solution_2 {
public:
  void solve(vector<vector<char>>& board) {
    if (board.empty()) {
      return;
    }

    int rows = board.size();
    int cols = board[0].size();

    vector<pair<int, int>> const directions{
      {-1, 0}, // top
      {0, -1}, // left
      {1, 0},  // bottom
      {0, 1},  // right
    };

    // Check and mark 'O's on the borders and connected 'O's
    for (int i = 0; i < rows; ++i) {
      if (board[i][0] == 'O') {
        bfs(board, i, 0, directions);
      }
      if (board[i][cols - 1] == 'O') {
        bfs(board, i, cols - 1, directions);
      }
    }

    for (int j = 0; j < cols; ++j) {
      if (board[0][j] == 'O') {
        bfs(board, 0, j, directions);
      }
      if (board[rows - 1][j] == 'O') {
        bfs(board, rows - 1, j, directions);
      }
    }

    // Flip 'O's to 'X's and revert 'V's back to 'O's
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        if (board[i][j] == 'O') {
          board[i][j] = 'X';
        } else if (board[i][j] == visited_) {
          board[i][j] = 'O';
        }
      }
    }
  }

private:
  void bfs(vector<vector<char>>& board, int row, int col, vector<pair<int, int>> const& directions) {
    if (board.empty()) {
      return;
    }

    int rows = board.size();
    int cols = board[0].size();

    // Mark as visited
    board[row][col] = visited_;

    queue<pair<int, int>> q{};
    q.push({row, col});
    while (!q.empty()) {
      pair<int, int> loc = q.front();
      q.pop();

      // Check and enqueue neighboring 'O's
      for (auto const& dir : directions) {
        int r = loc.first + dir.first;
        int c = loc.second + dir.second;
        if (r >= 0 && r < rows && c >= 0 && c < cols && board[r][c] == 'O') {
          q.push({r, c});
          board[r][c] = visited_;
        }
      } // for
    } // while
  }

  char const visited_{'V'};
};
