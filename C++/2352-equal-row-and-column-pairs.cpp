// HoNooD <honood@gmail.com>
// 2025.02.28 21:00

// 2352. Equal Row and Column Pairs
// https://leetcode.com/problems/equal-row-and-column-pairs/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  int equalPairs(vector<vector<int>>& grid) {
    return equal_pairs_v1(grid);
  }

private:
  // - Time complexity: O(n^3)
  // - Space complexity: O(1)
  int equal_pairs_v1(vector<vector<int>> const& grid) {
    int count = 0;

    int n = grid.size();
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        bool equal = true;
        for (int k = 0; k < n; ++k) {
          if (grid[i][k] != grid[k][j]) {
            equal = false;
            break;
          }
        }
        if (equal) {
          ++count;
        }
      }
    }

    return count;
  }

  // - Time complexity: O(n^2)
  // - Space complexity: O(n^2)
  int equal_pairs_v2(vector<vector<int>> const& grid) {
    unordered_map<string, int> row_count{};
    for (auto const& row : grid) {
      ++row_count[transform(row)];
    }

    int count = 0;
    int n = grid.size();
    for (int j = 0; j < n; ++j) {
      vector<int> col(n);
      for (int i = 0; i < n; ++i) {
        col[i] = grid[i][j];
      }

      string col_repr = transform(col);
      if (row_count.contains(col_repr)) {
        count += row_count[col_repr];
      }
    }

    return count;
  }

  string transform(vector<int> const& vec) {
    ostringstream oss{};
    for (int i = 0; i < vec.size(); ++i) {
      if (i > 0) {
        oss << ',';
      }
      oss << vec[i];
    }
    return oss.str();
  }
};
