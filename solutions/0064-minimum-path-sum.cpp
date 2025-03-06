// HoNooD <honood@gmail.com>
// 2024.07.07 20:00

// 64. Minimum Path Sum
// https://leetcode.com/problems/minimum-path-sum/description/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Dynamic_programming

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// Do not use, result in Time Limit Exceeded (TLE).
//
// time complexity: O(2^(m+n)) (each cell has two possible moves: right or down)
class Solution {
public:
  int minPathSum(vector<vector<int>>& grid) {
    if (grid.empty() || grid[0].empty()) {
      return 0;
    }

    return dfs(grid, 0, 0, 0);
  }

private:
  int dfs(vector<vector<int>> const& grid, int row, int col, int sum) {
    if (row >= grid.size() || col >= grid[0].size()) {
      return std::numeric_limits<int>::max();
    }

    sum += grid[row][col];
    if (row == grid.size() - 1 && col == grid[0].size() - 1) {
      return sum;
    }

    int right = dfs(grid, row, col + 1, sum);
    int down = dfs(grid, row + 1, col, sum);

    return std::min(right, down);
  }
};

// Memoized DFS involves storing the results of subproblems so that each cell's
// path sum is computed only once. This avoids redundant calculations by using a
// cache to record already solved subproblems.
//
// time complexity: O(m*n) (each cell is visit only once)
class Solution_2 {
public:
  int minPathSum(vector<vector<int>>& grid) {
    if (grid.empty() || grid[0].empty()) {
      return 0;
    }

    // as grid is filled with non-negative numbers, `-1` is invalid sum value
    vector<vector<int>> memo(grid.size(), vector<int>(grid[0].size(), -1));

    return dfs(grid, 0, 0, memo);
    // -OR-
    // return impl(grid, grid.size() - 1, grid[0].size() - 1, memo);
  }

private:
  int dfs(vector<vector<int>> const& grid, int row, int col, vector<vector<int>>& memo) {
    if (row >= grid.size() || col >= grid[0].size()) {
      return std::numeric_limits<int>::max();
    }

    // if reached the bottom-right corner, return its value
    if (row == grid.size() - 1 && col == grid[0].size() - 1) {
      return grid[row][col];
    }

    // if already computed, return the stored value
    if (memo[row][col] != -1) {
      return memo[row][col];
    }

    int right = dfs(grid, row, col + 1, memo);
    int down = dfs(grid, row + 1, col, memo);

    memo[row][col] = grid[row][col] + std::min(right, down);
    return memo[row][col];
  }

  int impl(vector<vector<int>> const& grid, int row, int col, vector<vector<int>>& memo) {
    // base case: when we reach the top-left corner
    if (row == 0 && col == 0) {
      return grid[row][col];
    }

    // if already computed, return the stored value
    if (memo[row][col] != -1) {
      return memo[row][col];
    }

    int from_top = std::numeric_limits<int>::max();
    if (row > 0) {
      from_top = impl(grid, row - 1, col, memo);
    }

    int from_left = std::numeric_limits<int>::max();
    if (col > 0) {
      from_left = impl(grid, row, col - 1, memo);
    }

    memo[row][col] = grid[row][col] + std::min(from_top, from_left);
    return memo[row][col];
  }
};

// Dynamic Programming (DP)
//
// The main idea is to use a 2D `dp` table to store the minimum path sum up to
// each cell.
class Solution_3 {
public:
  // Instead of creating a separate `dp` table, we can use the input `grid`
  // itself to store the minimum path sums.
  //
  // Note: optimal, recommended!
  //
  // time complexity: O(m*n)
  // space complexity: O(1)
  int minPathSum(vector<vector<int>>& grid) {
    if (grid.empty() || grid[0].empty()) {
      return 0;
    }

    int m = grid.size();
    int n = grid[0].size();

    // for the first row, each cell's minimum path sum is the sum of all the
    // cells to its left
    for (int j = 1; j < n; ++j) {
      grid[0][j] += grid[0][j - 1];
    }

    // for the first column, each cell's minimum path sum is the sum of all the
    // cells above it
    for (int i = 1; i < m; ++i) {
      grid[i][0] += grid[i - 1][0];
    }

    // fill the grid with the minimum path sums
    for (int i = 1; i < m; ++i) {
      for (int j = 1; j < n; ++j) {
        // for each cell (i, j) starting from (1, 1), its minimum path sum can
        // be derived from the minimum of the path sums of the cell directly
        // above it (`grid[i-1][j]`) and the cell directly to the left of it
        // (`grid[i][j-1]`). The value of the current cell is then added to this
        // minimum.
        grid[i][j] += std::min(grid[i - 1][j], grid[i][j - 1]);
      }
    }

    // the bottom-right cell (`grid[m-1][n-1]`) will contain the minimum path
    // sum from the top-left to the bottom-right of the grid
    return grid[m - 1][n - 1];
  }

  // time complexity: O(m*n)
  // space complexity: O(m*n)
  int min_path_sum_dp_not_modify_input(vector<vector<int>> const& grid) {
    if (grid.empty() || grid[0].empty()) {
      return 0;
    }

    int m = grid.size();
    int n = grid[0].size();

    vector<vector<int>> dp(m, vector<int>(n, 0));

    // initialize the first cell
    dp[0][0] = grid[0][0];

    // initialize the first row
    for (int j = 1; j < n; ++j) {
      dp[0][j] = dp[0][j - 1] + grid[0][j];
    }

    // initialize the first column
    for (int i = 1; i < m; ++i) {
      dp[i][0] = dp[i - 1][0] + grid[i][0];
    }

    // fill the `dp` array
    for (int i = 1; i < m; ++i) {
      for (int j = 1; j < n; ++j) {
        // The current cell value is the minimum path sum from the cell above or
        // the cell to the left plus the current cell's value
        dp[i][j] = std::min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
      }
    }

    // return the minimum path sum to the bottom-right corner
    return dp[m - 1][n - 1];
  }

  // optimize space usage by noting that each cell's value depends only on the
  // current and previous row. use a 1D array to store minimum path sums for the
  // current row.
  //
  // Note: great, recommended!
  //
  // time complexity: O(m*n)
  // space complexity: O(n)
  int min_path_sum_dp_not_modify_input_with_space_opt(vector<vector<int>> const& grid) {
    if (grid.empty() || grid[0].empty()) {
      return 0;
    }

    int m = grid.size();
    int n = grid[0].size();

    // store the minimum path sum for the current row
    vector<int> dp(n, 0);
    dp[0] = grid[0][0];

    // initialize for the first row
    for (int j = 1; j < n; ++j) {
      dp[j] = dp[j - 1] + grid[0][j];
    }

    // iterate over each row starting from the second row
    for (int i = 1; i < m; ++i) {
      // update the first element of `dp` for the current row
      dp[0] += grid[i][0];

      // update the rest of `dp` for the current row
      for (int j = 1; j < n; ++j) {
        dp[j] = std::min(dp[j], dp[j - 1]) + grid[i][j];
      }
    }

    // the last element of `dp` contains the minimum path sum to the
    // bottom-right corner
    return dp[n - 1];
  }
};
