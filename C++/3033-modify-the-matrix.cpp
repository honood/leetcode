// HoNooD <honood@gmail.com>
// 2024.07.22 10:00

// 3033. Modify the Matrix
// https://leetcode.com/problems/modify-the-matrix/description/

// https://leetcode.com/tag/matrix/

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  vector<vector<int>> modifiedMatrix(vector<vector<int>>& matrix) {
    return modified_matrix_v2(matrix);
  }

private:
  // - Time complexity: O(m*n)
  // - Space complexity: O(n)
  vector<vector<int>> modified_matrix_v1(vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();

    vector<int> col_max{matrix[0]};
    for (int i = 1; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        col_max[j] = std::max(col_max[j], matrix[i][j]);
      }
    }

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (matrix[i][j] == -1) {
          matrix[i][j] = col_max[j];
        }
      }
    }

    return matrix;
  }

  // - Time complexity: O(m*n)
  // - Space complexity: O(1)
  vector<vector<int>> modified_matrix_v2(vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();

    for (int j = 0; j < n; ++j) {
      int col_max = std::numeric_limits<int>::min();
      for (int i = 0; i < m; ++i) {
        col_max = std::max(col_max, matrix[i][j]);
      }

      for (int i = 0; i < m; ++i) {
        if (matrix[i][j] == -1) {
          matrix[i][j] = col_max;
        }
      }
    }

    return matrix;
  }
};
