// HoNooD <honood@gmail.com>
// 2024.07.08 08:30

// 63. Unique Paths II
// https://leetcode.com/problems/unique-paths-ii/description/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Dynamic_programming

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// Do not use, result in Time Limit Exceeded (TLE).
//
// time complexity: O(2^(m+n)) (each cell has two possible moves: right or down)
class Solution {
public:
  int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    if (obstacleGrid.empty() || obstacleGrid[0].empty()) {
      return 0;
    }

    return dfs(obstacleGrid, 0, 0);
  }

private:
  int dfs(vector<vector<int>> const& grid, int row, int col) {
    int m = grid.size();
    int n = grid[0].size();

    if (row >= m || col >= n || grid[row][col] == 1) {
      return 0;
    }

    if (row == m - 1 && col == n - 1) {
      return 1;
    }

    return dfs(grid, row + 1, col) + dfs(grid, row, col + 1);
  }
};

// Memoized DFS
//
// time complexity: O(m*n) (each cell is visit only once)
class Solution_2 {
public:
  int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    if (obstacleGrid.empty() || obstacleGrid[0].empty()) {
      return 0;
    }

    // initialize memoization table with -1 (unvisited)
    vector<vector<int>> memo(obstacleGrid.size(), vector<int>(obstacleGrid[0].size(), -1));
    return dfs(obstacleGrid, 0, 0, memo);
    // -OR-
    // return dfs2(obstacleGrid, obstacleGrid.size() - 1, obstacleGrid[0].size() - 1, memo);
  }

private:
  int dfs(vector<vector<int>> const& grid, int row, int col, vector<vector<int>>& memo) {
    int m = grid.size();
    int n = grid[0].size();

    if (row >= m || col >= n || grid[row][col] == 1) {
      return 0;
    }

    if (row == m - 1 && col == n - 1) {
      return 1;
    }

    // check if already calculated
    if (memo[row][col] != -1) {
      return memo[row][col];
    }

    memo[row][col] = dfs(grid, row + 1, col, memo) + dfs(grid, row, col + 1, memo);
    return memo[row][col];
  }

  int dfs2(vector<vector<int>> const& grid, int row, int col, vector<vector<int>>& memo) {
    // reach the top-left corner
    if (row == 0 && col == 0) {
      // ensure start is not an obstacle
      return grid[0][0] == 1 ? 0 : 1;
    }

    if (memo[row][col] != -1) {
      return memo[row][col];
    }

    // if the current cell is an obstacle, there are no paths
    if (grid[row][col] == 1) {
      memo[row][col] = 0;
      return 0;
    }

    // calculate paths from top
    int from_top = 0;
    if (row > 0) {
      from_top = dfs2(grid, row - 1, col, memo);
    }

    // calculate paths from left
    int from_left = 0;
    if (col > 0) {
      from_left = dfs2(grid, row, col - 1, memo);
    }

    memo[row][col] = from_top + from_left;
    return memo[row][col];
  }
};

// Dynamic Programming (DP)
//
// Use a 2D DP array `dp` where `dp[i][j]` represents the number of unique paths
// to reach cell `(i, j)` from the top-left corner. The DP formula will consider
// the number of paths coming from the top and left, provided those cells are
// not obstacles.
class Solution_3 {
public:
  // time Complexity: O(m*n)
  // space complexity: O(m*n)
  int uniquePathsWithObstacles(vector<vector<int>> const& obstacleGrid) {
    if (obstacleGrid.empty() || obstacleGrid[0].empty()) {
      return 0;
    }

    int m = obstacleGrid.size();
    int n = obstacleGrid[0].size();

    vector<vector<int>> dp(m, vector<int>(n, 0));
    dp[0][0] = obstacleGrid[0][0] == 0 ? 1 : 0;

    // fill the first row
    for (int j = 1; j < n; ++j) {
      if (obstacleGrid[0][j] == 0) {
        dp[0][j] = dp[0][j - 1];
      }
    }

    // fill the first column
    for (int i = 1; i < m; ++i) {
      if (obstacleGrid[i][0] == 0) {
        dp[i][0] = dp[i - 1][0];
      }
    }

    // fill the rest of the DP table
    for (int i = 1; i < m; ++i) {
      for (int j = 1; j < n; ++j) {
        if (obstacleGrid[i][j] == 0) {
          dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
      }
    }

    return dp[m - 1][n - 1];
  }

  // time Complexity: O(m*n)
  // space complexity: O(n)
  int unique_paths_with_obstacles_space_opt(vector<vector<int>> const& obstacleGrid) {
    if (obstacleGrid.empty() || obstacleGrid[0].empty()) {
      return 0;
    }

    int m = obstacleGrid.size();
    int n = obstacleGrid[0].size();

    // initialize a DP array for one row
    vector<int> dp(n, 0);
    dp[0] = obstacleGrid[0][0] == 0 ? 1 : 0;

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (obstacleGrid[i][j] == 1) {
          dp[j] = 0;
        } else if (j > 0) {
          // If the current cell `obstacleGrid[i][j]` is not an obstacle (which
          // is already checked before this line), add the number of paths to
          // the current cell from the left cell `dp[j - 1]`. This means that
          // `dp[j]` now contains the total number of paths to reach the cell
          // `(i, j)` either from above (which was already stored in `dp[j]`) or
          // from the left (`dp[j - 1]`), effectively combining the paths from
          // both directions.
          dp[j] += dp[j - 1];
        }
      }
    }

    return dp[n - 1];
  }

  // time Complexity: O(m*n)
  // space complexity: O(1)
  int unique_paths_with_obstacles_in_place(vector<vector<int>>& obstacleGrid) {
    if (obstacleGrid.empty() || obstacleGrid[0].empty()) {
      return 0;
    }

    if (obstacleGrid[0][0] == 1) {
      return 0;
    }

    obstacleGrid[0][0] = 1;

    int m = obstacleGrid.size();
    int n = obstacleGrid[0].size();

    // fill the first row
    for (int j = 1; j < n; ++j) {
      if (obstacleGrid[0][j] == 0) {
        obstacleGrid[0][j] = obstacleGrid[0][j - 1];
      } else {
        obstacleGrid[0][j] = 0;
      }
    }

    // fill the first column
    for (int i = 1; i < m; ++i) {
      if (obstacleGrid[i][0] == 0) {
        obstacleGrid[i][0] = obstacleGrid[i - 1][0];
      } else {
        obstacleGrid[i][0] = 0;
      }
    }

    // fill the rest of the grid
    for (int i = 1; i < m; ++i) {
      for (int j = 1; j < n; ++j) {
        if (obstacleGrid[i][j] == 0) {
          obstacleGrid[i][j] = obstacleGrid[i - 1][j] + obstacleGrid[i][j - 1];
        } else {
          obstacleGrid[i][j] = 0;
        }
      }
    }

    return obstacleGrid[m - 1][n - 1];
  }
};
