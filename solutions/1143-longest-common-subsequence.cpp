// HoNooD <honood@gmail.com>
// 2025.04.09 20:00
//
// 1143. Longest Common Subsequence
// https://leetcode.com/problems/longest-common-subsequence/?envType=study-plan-v2&envId=leetcode-75

// Longest common subsequence
// https://en.wikipedia.org/wiki/Longest_common_subsequence

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  int longestCommonSubsequence(string text1, string text2) {
    return longest_common_subsequence_v2(text1, text2);
  }

private:
  // - Time complexity: O(m * n)
  // - Space complexity: O(m * n)
  int longest_common_subsequence_v1(string const& text1, string const& text2) {
    int m = text1.length();
    int n = text2.length();
    vector<vector<int>> memo(m + 1, vector<int>(n + 1, -1));

    // Helper function to compute LCS length for prefixes of length i and j
    std::function<int(int, int)> solve
      = [&solve, &text1, &text2, &memo](int i, int j) {
          // Base case: one of the strings is empty
          if (i == 0 || j == 0) return 0;
          if (memo[i][j] != -1) return memo[i][j];

          if (text1[i - 1] == text2[j - 1]) {
            memo[i][j] = solve(i - 1, j - 1) + 1;
          } else {
            // If the last characters don't match
            memo[i][j] = std::max(solve(i - 1, j), solve(i, j - 1));
          }

          return memo[i][j];
        };

    return solve(m, n);
  }

  // - Time complexity: O(m * n)
  // - Space complexity: O(m * n)
  int longest_common_subsequence_v2(string const& text1, string const& text2) {
    int m = text1.length();
    int n = text2.length();

    // dp[i][j] = LCS length for text1[0...i-1] and text2[0...j-1]
    // Size (m+1) x (n+1) to handle base cases i=0 and j=0 easily
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Fill the dp table using the recurrence relation
    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        // Check if characters at the curent end match
        if (text1[i - 1] == text2[j - 1]) {
          // If match, add 1 the LCS of prefixes ending before these characters
          dp[i][j] = dp[i - 1][j - 1] + 1;
        } else {
          // If no match, take the maximum LCS by excluding one character from
          // either text1 or text2
          dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
        }
      }
    }

    return dp[m][n];
  }

  // - Time complexity: O(m * n)
  // - Space complexity: O(min(m, n))
  int longest_common_subsequence_v3(string& text1, string& text2) {
    int m = text1.length();
    int n = text2.length();

    // clang-format off
    // Ensure n is the smaller dimension for O(min(m, n)) space
    if (m < n) {
      text1.swap(text2);
      std::swap(m, n);
    }

    assert(n <= m);

    // dp array stores results conceptually for 'previous' row
    vector<int> dp(n + 1, 0);

    // ┼────────────┼──────────┼
    // │ (i-1, j-1) │ (i-1, j) │
    // ┼────────────┼──────────┼
    // │ (i, j-1)   │ (i, j)   │
    // ┼────────────┼──────────┼

    // Iterate through the longer string (text1)
    for (int i = 1; i <= m; ++i) {
      int prev_val_diag = 0; // dp[i-1][j-1]

      // Iterate through the shorter string (text2)
      for (int j = 1; j <= n; ++j) {
        int temp = dp[j]; // dp[i-1][j] (value before update)

        if (text1[i - 1] == text2[j - 1]) {
          // Match: current dp[j] = 1 + value from top-left diagonal of prev row
          dp[j] = prev_val_diag + 1;
        } else {
          // No match: current dp[j] = max(value above, value to the left)
          // value above = dp[j] (before update, stored in temp, but we use the current dp[j])
          // value to the left = dp[j-1] (already updated for the current row i)
          dp[j] = std::max(dp[j], dp[j - 1]);
        }
        // Update prev_val_diag for the next iteration (j+1)
        // It needs the value that dp[j] had *before* this iteration's update
        prev_val_diag = temp;
      }
    }

    // The result is the last element of the dp array after processing all rows
    return dp[n];
    // clang-format on
  }
};
