// HoNooD <honood@gmail.com>
// 2024.07.10 08:30

// 97. Interleaving String
// https://leetcode.com/problems/interleaving-string/description/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Dynamic_programming

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// Dynamic Programming (DP)
class Solution {
public:
  bool isInterleave(string s1, string s2, string s3) {
    if (s1.size() + s2.size() != s3.size()) {
      return false;
    }

    int m = s1.size();
    int n = s2.size();

    // create a 2D DP table
    //
    // Note: `dp[i][j]` represents whether the first `i` characters of `s1` and
    // the first `j` characters of `s2` can interleave to form the first `i + j`
    // characters of `s3`
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));

    // initialize the DP table
    //
    // Note: two empty strings can indeed interleave to form an empty string
    dp[0][0] = true;

    // fill the DP table
    for (int i = 0; i <= m; ++i) {
      for (int j = 0; j <= n; ++j) {
        if (i > 0) {
          dp[i][j] = dp[i][j] || (dp[i - 1][j] && s1[i - 1] == s3[i + j - 1]);
        }

        if (j > 0) {
          dp[i][j] = dp[i][j] || (dp[i][j - 1] && s2[j - 1] == s3[i + j - 1]);
        }
      }
    }

    return dp[m][n];
  }
};

// Recursive with Memoization
//
// Checks if the current characters of `s1` or `s2` match the current
// character of `s3`. If a match is found, recursively checks the remaining
// substrings.
class Solution_2 {
public:
  bool isInterleave(string s1, string s2, string s3) {
    if (s1.size() + s2.size() != s3.size()) {
      return false;
    }

    // store intermediate results
    std::unordered_map<string, bool> memo{};
    return impl(s1, s2, s3, 0, 0, 0, memo);
  }

  private:
  bool impl(string const& s1, string const& s2, string const& s3,
            int i, int j, int k, unordered_map<string, bool>& memo) {
    if (k == s3.size()) {
      return true;
    }

    string key = std::to_string(i) + ',' + to_string(j) + ',' + to_string(k);
    if (memo.contains(key)) {
      return memo[key];
    }

    // check if we can take a character from `s1`
    if (i < s1.size() && s1[i] == s3[k]) {
      if (impl(s1, s2, s3, i + 1, j, k + 1, memo)) {
        memo[key] = true;
        return true;
      }
    }

    // check if we can take a character from `s2`
    if (j < s2.size() && s2[j] == s3[k]) {
      if (impl(s1, s2, s3, i, j + 1, k + 1, memo)) {
        memo[key] = true;
        return true;
      }
    }

    // if neither character matches, store the result and return false
    memo[key] = false;
    return false;
  }
};
