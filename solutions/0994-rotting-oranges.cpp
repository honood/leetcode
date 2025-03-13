// HoNooD <honood@gmail.com>
// 2025.03.13 09:20

// 994. Rotting Oranges
// https://leetcode.com/problems/rotting-oranges/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  // each cell can have one of three values:
  //   - 0: empty cell
  //   - 1: fresh orange
  //   - 2: rotten orange
  int orangesRotting(vector<vector<int>>& grid) {
    return oranges_rotting_v1(grid);
  }

private:
  // Multi-source BFS
  //
  // - Time complexity: O(m * n)
  // - Space complexity: O(m * n)
  int oranges_rotting_v1(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();

    std::queue<tuple<int, int, int>> queue{};
    int fresh_count = 0;

    for (int row = 0; row < m; ++row) {
      for (int col = 0; col < n; ++col) {
        if (grid[row][col] == 2) {
          queue.emplace(row, col, 0);
        } else if (grid[row][col] == 1) {
          ++fresh_count;
        }
      }
    }

    if (fresh_count == 0) {
      return 0;
    }

    // clang-format off
    constexpr std::array<pair<int, int>, 4> directions{{
      {-1, 0}, {0, -1}, {1, 0}, {0, 1}
    }};
    // clang-format on
    auto in_bounds = [m, n](int row, int col) {
      return row >= 0 && row < m && col >= 0 && col < n;
    };

    assert(fresh_count > 0);
    while (!queue.empty()) {
      auto [row, col, minutes] = queue.front();
      queue.pop();

      for (auto [drow, dcol] : directions) {
        int new_row = row + drow;
        int new_col = col + dcol;
        if (in_bounds(new_row, new_col) && grid[new_row][new_col] == 1) {
          grid[new_row][new_col] = 2; // Mark as rotten
          --fresh_count;
          if (fresh_count == 0) {
            return minutes + 1;
          }

          queue.emplace(new_row, new_col, minutes + 1);
        }
      }
    }

    return -1;
  }

  // Level-order BFS
  //
  // - Time complexity: O(m * n)
  // - Space complexity: O(m * n)
  int oranges_rotting_v2(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();

    std::queue<pair<int, int>> queue{};
    int fresh_count = 0;

    for (int row = 0; row < m; ++row) {
      for (int col = 0; col < n; ++col) {
        if (grid[row][col] == 2) {
          queue.emplace(row, col);
        } else if (grid[row][col] == 1) {
          ++fresh_count;
        }
      }
    }

    if (fresh_count == 0) {
      return 0;
    }

    // clang-format off
    constexpr std::array<pair<int, int>, 4> directions{{
      {-1, 0}, {0, -1}, {1, 0}, {0, 1}
    }};
    // clang-format on
    auto in_bounds = [m, n](int row, int col) {
      return row >= 0 && row < m && col >= 0 && col < n;
    };

    int minutes = 0;

    assert(fresh_count > 0);
    while (!queue.empty() && fresh_count > 0) {
      int size = queue.size();
      for (int i = 0; i < size; ++i) {
        auto [row, col] = queue.front();
        queue.pop();

        for (auto [drow, dcol] : directions) {
          int new_row = row + drow;
          int new_col = col + dcol;
          if (in_bounds(new_row, new_col) && grid[new_row][new_col] == 1) {
            grid[new_row][new_col] = 2; // Mark as rotten
            --fresh_count;

            queue.emplace(new_row, new_col);
          }
        }
      } // for (i)

      ++minutes;
    }

    return fresh_count > 0 ? -1 : minutes;
  }
};
