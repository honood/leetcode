// HoNooD <honood@gmail.com>
// 2025.04.09 14:52
//
// 62. Unique Paths
// https://leetcode.com/problems/unique-paths/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  int uniquePaths(int m, int n) {
    return unique_paths_v1(m, n);
  }

public:
  // - Time complexity: O(m * n)
  // - Space complexity: O(m * n)
  int unique_paths_v1(int m, int n) {
    // Create a 2D DP table
    vector<vector<int>> dp(m, vector<int>(n, 0));
    // There's only one way to reach any cell in the first row (move right)
    for (int i = 0; i < m; ++i) dp[i][0] = 1;
    // There's only one way to reach any cell in the first column (move down)
    for (int j = 0; j < n; ++j) dp[0][j] = 1;

    // Fill the rest of the DP table using the recurrence relation
    for (int i = 1; i < m; ++i) {
      for (int j = 1; j < n; ++j) {
        dp[i][j] = dp[i][j - 1] // left
                   + dp[i - 1][j]; // top
      }
    }

    return dp[m - 1][n - 1];
  }

  // - Time complexity: O(m * n)
  // - Space complexity: O(min(m, n))
  int unique_paths_v2(int m, int n) {
    if (n > m) std::swap(m, n);

    // Create a 1D DP array
    // dp[j] will store the number of paths to reach cell (current_row, j)
    vector<int> dp(n, 1); // Initialize with 1s (representing the first row)

    for (int i = 1; i < m; ++i) {
      for (int j = 1; j < n; ++j) {
        dp[j] = dp[j] // paths from top, i.e., dp[i-1][j]
                + dp[j - 1]; // paths from left, i.e., dp[i][j-1]
      }
    }

    return dp[n - 1];
  }

  // - Time complexity: O(min(m, n))
  // - Space complexity: O(1)
  int unique_paths_v3(int m, int n) {
    // Total number of steps needed
    int total_steps = m + n - 2;
    // Number of 'down' steps needed
    int down_steps = m - 1;
    // Number of `right` steps needed (k for C(N, k))
    // We choose the smaller one to optimize calculation loops
    // k = min(m-1, n-1)
    int k = std::min(down_steps, total_steps - down_steps);

    // C(N, K) = (N * (N-1) * (N-2) * ... * (N-K+1)) / K!
    //         = (N * (N-1) * (N-2) * ... * (N-K+1)) / (1 * 2 * 3 * ... K)
    //         = (N/1)   * ((N-1)/2) * ((N-2)/3) * ... * ((N-K+1)/K)
    //         = C(N, 1) * ((N-1)/2) * ((N-2)/3) * ... * ((N-K+1)/K)
    //         =             C(N, 2) * ((N-2)/3) * ... * ((N-K+1)/K)
    //         =                         C(N, 3) * ... * ((N-K+1)/K)
    //         =                                             C(N, K)

    // Calculate C(total_steps, k) iteratively
    long long result = 1; // Use long long to prevent overflow
    for (int i = 1; i <= k; ++i) {
      // Multiply by (N - i + 1) which is (total_steps - i + 1)
      result = result * (total_steps - i + 1);
      // Divide by i
      result = result / i;
    }
    return static_cast<int>(result);
  }
};
