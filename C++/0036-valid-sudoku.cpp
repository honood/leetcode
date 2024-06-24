// HoNooD <honood@gmail.com>
// 2024.06.25 05:30

// 36. Valid Sudoku
// https://leetcode.com/problems/valid-sudoku/description/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Sudoku
// https://en.wikipedia.org/wiki/Sudoku_solving_algorithms

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// Great!
class Solution {
public:
  bool isValidSudoku(vector<vector<char>>& board) {
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
    bool rows[9][9] = {false};
    bool cols[9][9] = {false};
    bool boxes[9][9] = {false};

    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        if (board[i][j] == '.') {
          continue;
        }

        // convert the character to an integer index, '1' -> 0, '2' -> 1, ...,
        // '9' -> 9
        int num = board[i][j] - '1';
        // determine the index for the 3x3 sub-box
        int boxIndex = (i / 3) * 3 + j / 3;
        // check if this number has already been seen in the current row,
        // column, or 3x3 sub-box
        if (rows[i][num] || cols[j][num] || boxes[boxIndex][num]) {
          return false;
        }

        // mark this number as seen in the row, column, and 3x3 sub-box
        rows[i][num] = true;
        cols[j][num] = true;
        boxes[boxIndex][num] = true;
      }
    }

    return true;
  }
};

// brute force
//
// simple but less efficient, do NOT use!
class Solution_2 {
public:
  bool isValidSudoku(vector<vector<char>>& board) {
    assert(board.size() == 9 && board[0].size() == 9);

    auto check = [](int(&data)[9]) {
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
};
