// HoNooD <honood@gmail.com>
// 2024.06.25 21:40

// 73. Set Matrix Zeroes
// https://leetcode.com/problems/set-matrix-zeroes/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  void setZeroes(vector<vector<int>>& matrix) {
    if (matrix.empty() || matrix[0].empty()) {
      return;
    }

    int m = matrix.size();
    int n = matrix[0].size();

    // determine if the first row has any zeros
    bool first_row_has_zero = false;
    for (int j = 0; j < n; ++j) {
      if (matrix[0][j] == 0) {
        first_row_has_zero = true;
        break;
      }
    }

    // determine if the first column has any zeros
    bool first_col_has_zero = false;
    for (int i = 0; i < m; ++i) {
      if (matrix[i][0] == 0) {
        first_col_has_zero = true;
        break;
      }
    }

    // use the first row and column to mark zeros
    for (int i = 1; i < m; ++i) {
      for (int j = 1; j < n; ++j) {
        if (matrix[i][j] == 0) {
          matrix[i][0] = 0;
          matrix[0][j] = 0;
        }
      }
    }

    // zero out rows based on the markers
    for (int i = 1; i < m; ++i) {
      if (matrix[i][0] == 0) {
        for (int j = 1; j < n; ++j) {
          matrix[i][j] = 0;
        }
      }
    }

    // zero out columns based on the markers
    for (int j = 1; j < n; ++j) {
      if (matrix[0][j] == 0) {
        for (int i = 1; i < m; ++i) {
          matrix[i][j] = 0;
        }
      }
    }

    // finally handle the first row and column
    if (first_row_has_zero) {
      for (int j = 0; j < n; ++j) {
        matrix[0][j] = 0;
      }
    }

    if (first_col_has_zero) {
      for (int i = 0; i < m; ++i) {
        matrix[i][0] = 0;
      }
    }
  }
};
