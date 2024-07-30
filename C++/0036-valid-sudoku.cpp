// HoNooD <honood@gmail.com>
// 2024.06.25 05:30

// 36. Valid Sudoku
// https://leetcode.com/problems/valid-sudoku/description/?envType=study-plan-v2&envId=top-interview-150
//
// Note:
//   1. A Sudoku board (partially filled) could be valid but is not necessarily
//      solvable.
//   2. Only the filled cells need to be validated according to the mentioned
//      rules.

// https://en.wikipedia.org/wiki/Sudoku
// https://en.wikipedia.org/wiki/Sudoku_solving_algorithms

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  bool isValidSudoku(vector<vector<char>>& board) {
    return is_valid_sudoku_v2(board);
  }

private:
  bool is_valid_sudoku_v1(vector<vector<char>> const& board) {
    assert(board.size() == 9 && board[0].size() == 9);

    auto check = [](int (&data)[9]) {
      for (int i = 0; i < 9; ++i) {
        if (data[i] > 1) {
          return false;
        }
      }
      return true;
    };

    for (int i = 0; i < 9; ++i) {
      int row[9] = {0};

      for (int j = 0; j < 9; ++j) {
        if (board[i][j] != '.') {
          ++row[board[i][j] - '1'];
        }
      }

      if (!check(row)) {
        return false;
      }
    }

    for (int j = 0; j < 9; ++j) {
      int col[9] = {0};

      for (int i = 0; i < 9; ++i) {
        if (board[i][j] != '.') {
          ++col[board[i][j] - '1'];
        }
      }

      if (!check(col)) {
        return false;
      }
    }

    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        int grid33[9] = {0};

        for (int i2 = 0; i2 < 3; ++i2) {
          for (int j2 = 0; j2 < 3; ++j2) {
            if (board[3 * i + i2][3 * j + j2] != '.') {
              ++grid33[board[3 * i + i2][3 * j + j2] - '1'];
            }
          }
        }

        if (!check(grid33)) {
          return false;
        }
      }
    }

    return true;
  }

  bool is_valid_sudoku_v2(vector<vector<char>> const& board) {
    assert(board.size() == 9 && board[0].size() == 9);

    // Using `std::array` with explicit initialization might be clearer:
    //
    // auto fill_false = [](array<array<bool, 9>, 9>& matrix) {
    //   for (auto& row : matrix) {
    //     row.fill(false);
    //   }
    // };
    // array<array<bool, 9>, 9> rows{};
    // fill_false(rows);
    // array<array<bool, 9>, 9> cols{};
    // fill_false(cols);
    // array<array<bool, 9>, 9> boxes{};
    // fill_false(boxes);
    bool rows[9][9] = {};
    // std::memset(rows, false, sizeof(rows)); // not needed for `bool rows[9][9]`
    bool cols[9][9] = {};
    // std::memset(cols, false, sizeof(cols)); // not needed for `bool cols[9][9]`
    bool boxes[9][9] = {};
    // std::memset(boxes, false, sizeof(boxes)); // not needed for `bool boxes[9][9]`

    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        if (board[i][j] == '.') {
          continue;
        }

        // convert the character to an integer index, '1' -> 0, '2' -> 1, ..., '9' -> 9
        int num = board[i][j] - '1';
        // determine the index for the 3x3 sub-box
        int box_index = (i / 3) * 3 + j / 3;
        // check if this number has already been seen in the current row, column, or 3x3 sub-box
        if (rows[i][num] || cols[j][num] || boxes[box_index][num]) {
          return false;
        }

        // mark this number as seen in the row, column, and 3x3 sub-box
        rows[i][num] = true;
        cols[j][num] = true;
        boxes[box_index][num] = true;
      }
    }

    return true;
  }
};
