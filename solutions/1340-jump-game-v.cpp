// HoNooD <honood@gmail.com>
// 2024.07.28 12:42

// 1340. Jump Game V
// https://leetcode.com/problems/jump-game-v/description/

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  int maxJumps(vector<int>& arr, int d) {
    return max_jumps_v1(arr, d);
  }

private:
  // Dynamic Programming (DP)
  // https://leetcode.com/tag/dynamic-programming/
  //
  // - Time complexity: O(n*d)
  // - Space complexity: O(n)
  int max_jumps_v1(vector<int> const& arr, int d) {
    int n = arr.size();
    if (d <= 0) {
      return n > 0 ? 1 : 0;
    }

    if (n <= 1) {
      return n;
    }

    // `dp[i]` as the maximum number of indices that can be visited starting
    // from index `i`
    vector<int> dp(n, 1);

    vector<pair<int, int>> sorted_positions{};
    sorted_positions.reserve(n);
    for (int i = 0; i < n; ++i) {
      sorted_positions.emplace_back(arr[i], i);
    }
    std::sort(sorted_positions.begin(), sorted_positions.end(), [](pair<int, int> const& left, pair<int, int> const& right) {
      return left.first < right.first;
    });

    for (auto const& [value, i] : sorted_positions) {
      // check left jumps
      for (int j = 1; j <= d && i - j >= 0 && arr[i - j] < arr[i]; ++j) {
        dp[i] = std::max(dp[i], dp[i - j] + 1);
      }

      // check right jumps
      for (int j = 1; j <= d && i + j < n && arr[i + j] < arr[i]; ++j) {
        dp[i] = std::max(dp[i], dp[i + j] + 1);
      }
    }

    return *std::max_element(dp.cbegin(), dp.cend());
  }

  // DFS with Memoization
  // https://leetcode.com/tag/depth-first-search/
  // https://leetcode.com/tag/memoization/
  //
  // - Time complexity: O(n*d)
  // - Space complexity: O(n)
  int max_jumps_v2(vector<int> const& arr, int d) {
    int n = arr.size();
    if (d <= 0) {
      return n > 0 ? 1 : 0;
    }

    if (n <= 1) {
      return n;
    }

    vector<int> memo(n, -1);
    int res = 0;
    for (int i = 0; i < n; ++i) {
      res = std::max(res, dfs(arr, i, d, memo));
    }

    return res;
  }

  int dfs(vector<int> const& arr, int i, int const& d, vector<int>& memo) {
    if (memo[i] != -1) {
      return memo[i];
    }

    int n = arr.size();
    // can at least stay at this index
    int max_visits = 1;

    // check left jumps
    for (int j = 1; j <= d && i - j >= 0 && arr[i - j] < arr[i]; ++j) {
      max_visits = std::max(max_visits, dfs(arr, i - j, d, memo) + 1);
    }
    // check right jumps
    for (int j = 1; j <= d && i + j < n && arr[i + j] < arr[i]; ++j) {
      max_visits = std::max(max_visits, dfs(arr, i + j, d, memo) + 1);
    }

    memo[i] = max_visits;
    return max_visits;
  }
};
