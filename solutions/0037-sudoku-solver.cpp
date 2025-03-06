// HoNooD <honood@gmail.com>
// 2024.07.30 09:33

// 37. Sudoku Solver
// https://leetcode.com/problems/sudoku-solver/description/

// https://en.wikipedia.org/wiki/Sudoku
// https://en.wikipedia.org/wiki/Sudoku_solving_algorithms

// https://leetcode.com/tag/matrix/
// https://leetcode.com/tag/backtracking/
// https://leetcode.com/tag/hash-table/
// https://leetcode.com/tag/array/

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  void solveSudoku(vector<vector<char>>& board) {
    solve_sudoku_v2(board);
  }

private:
  void solve_sudoku_v1(vector<vector<char>>& board) {
    solve(board);
  }

  bool solve(vector<vector<char>>& board) {
    for (int row = 0; row < 9; ++row) {
      for (int col = 0; col < 9; ++col) {
        if (board[row][col] != '.') {
          continue;
        }

        // try filling cell with digits '1' to '9'
        for (char num = '1'; num <= '9'; ++num) {
          if (!is_valid(board, row, col, num)) {
            continue;
          }

          board[row][col] = num;
          // recursively try to fill the rest of the board
          if (solve(board)) {
            return true;
          }
          // if filling current cell with `num` didn't lead to a solution, undo it
          board[row][col] = '.';
        }

        // if no valid number can be placed in this cell, return `false`
        return false;
      }
    }

    // if no empty cells are left, return `true` as the board is solved
    return true;
  }

  bool is_valid(vector<vector<char>> const& board, int row, int col, char num) {
    for (int i = 0; i < 9; ++i) {
      if (board[row][i] == num) {
        return false;
      }
      if (board[i][col] == num) {
        return false;
      }
      if (board[row / 3 * 3 + i / 3][col / 3 * 3 + i % 3] == num) {
        return false;
      }
    }

    return true;
  }

  void solve_sudoku_v2(vector<vector<char>>& board) {
    bool rows[9][9] = {};
    // std::memset(rows, false, sizeof(rows)); // not needed for `bool rows[9][9]`
    bool cols[9][9] = {};
    // std::memset(cols, false, sizeof(cols)); // not needed for `bool cols[9][9]`
    bool boxes[9][9] = {};
    // std::memset(boxes, false, sizeof(boxes)); // not needed for `bool boxes[9][9]`

    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        if (board[i][j] != '.') {
          int num = board[i][j] - '1';
          int box_index = (i / 3) * 3 + j / 3;

          rows[i][num] = true;
          cols[j][num] = true;
          boxes[box_index][num] = true;
        }
      }
    }

    solve(board, 0, 0, rows, cols, boxes);
  }

  bool solve(vector<vector<char>>& board, int row, int col,
             bool (&rows)[9][9], bool (&cols)[9][9], bool (&boxes)[9][9]) {
    if (row == 9) {
      return true;
    }

    if (col == 9) {
      return solve(board, row + 1, 0, rows, cols, boxes);
    }

    if (board[row][col] != '.') {
      return solve(board, row, col + 1, rows, cols, boxes);
    }

    for (char fill = '1'; fill <= '9'; ++fill) {
      int num = fill - '1';
      int box_index = (row / 3) * 3 + col / 3;
      if (rows[row][num] || cols[col][num] || boxes[box_index][num]) {
        continue;
      }

      board[row][col] = fill;
      rows[row][num] = true;
      cols[col][num] = true;
      boxes[box_index][num] = true;

      if (solve(board, row, col + 1, rows, cols, boxes)) {
        return true;
      }

      board[row][col] = '.';
      rows[row][num] = false;
      cols[col][num] = false;
      boxes[box_index][num] = false;
    }

    return false;
  }

  void solve_sudoku_v3(vector<vector<char>>& board) {
    int rows[9] = {};
    int cols[9] = {};
    int boxes[9] = {};

    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        if (board[i][j] != '.') {
          int num = board[i][j] - '1';
          int mask = 1 << num;
          int box_index = (i / 3) * 3 + j / 3;

          rows[i] |= mask;
          cols[j] |= mask;
          boxes[box_index] |= mask;
        }
      }
    }

    solve(board, 0, 0, rows, cols, boxes);
  }

  bool solve(vector<vector<char>>& board, int row, int col,
             int (&rows)[9], int (&cols)[9], int (&boxes)[9]) {
    if (row == 9) {
      return true;
    }

    if (col == 9) {
      return solve(board, row + 1, 0, rows, cols, boxes);
    }

    if (board[row][col] != '.') {
      return solve(board, row, col + 1, rows, cols, boxes);
    }

    for (char num = '1'; num <= '9'; ++num) {
      int mask = 1 << (num - '1');
      int box_index = (row / 3) * 3 + col / 3;

      if ((rows[row] & mask) != 0 || (cols[col] & mask) != 0 || (boxes[box_index] & mask) != 0) {
        continue;
      }

      board[row][col] = num;
      rows[row] |= mask;
      cols[col] |= mask;
      boxes[box_index] |= mask;

      if (solve(board, row, col + 1, rows, cols, boxes)) {
        return true;
      }

      board[row][col] = '.';
      rows[row] &= ~mask;
      cols[col] &= ~mask;
      boxes[box_index] &= ~mask;
    }

    return false;
  }
};
