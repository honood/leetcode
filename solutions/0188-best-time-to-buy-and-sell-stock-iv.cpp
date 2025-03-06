// HoNooD <honood@gmail.com>
// 2024.07.23 09:00

// 188. Best Time to Buy and Sell Stock IV
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  int maxProfit(int k, vector<int>& prices) {
    return max_profit_v1(k, prices);
  }

private:
  // Dynamic Programming (DP)
  // https://leetcode.com/tag/dynamic-programming/
  //
  // - Time complexity: O(k*n)
  // - Space complexity: O(k*n)
  int max_profit_v1(int k, vector<int> const& prices) {
    if (k <= 0) {
      return 0;
    }

    int n = prices.size();
    if (n <= 1) {
      return 0;
    }

    if (k >= n / 2) {
      // When `k >= n/2`, it means we can take advantage of every possible
      // opportunity to buy and sell whenever there is a price increase. This
      // means we are no longer constrained by the number of transactions,
      // effectively allowing for unlimited transactions since any additional
      // `k` beyond `n/2` will not yield additional profit opportunities. All
      // potential profits are already captured when `k = n/2`.
      //
      // This simplifies the problem to LeetCode 122: Best Time to Buy and Sell Stock II
      // - Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/description/?envType=study-plan-v2&envId=top-interview-150
      // - File: 0122-best-time-to-buy-and-sell-stock-ii.cpp
      int max_profit = 0;
      for (int j = 1; j < n; ++j) {
        if (prices[j] > prices[j - 1]) {
          max_profit += prices[j] - prices[j - 1];
        }
      }

      return max_profit;
    }

    // `dp[i][j]` represents the maximum profit achievable by making at most `i`
    // transactions up to day `j`
    //
    // Note:
    //   dp[i][0] = 0
    //   dp[0][j] = 0
    vector<vector<int>> dp(k + 1, vector<int>(n, 0));
    for (int i = 1; i <= k; ++i) {
      // `max_diff` represents the maximum profit achievable by buying a stock
      // on any of the days before day `j` and making a transaction
      int max_diff = -prices[0];
      for (int j = 1; j < n; ++j) {
        // Update `dp[i][j]` to the maximum of:
        // 1. `dp[i][j-1]` (no transaction on day `j`)
        // 2. `prices[j] + max_diff` (sell on day `j` after buying on the best
        //    day before `j`)
        dp[i][j] = std::max(dp[i][j - 1], prices[j] + max_diff);
        // Update `max_diff` to reflect the maximum profit we can have up until
        // day `j` if we buy on a previous day and sell on day `j`
        max_diff = std::max(max_diff, dp[i - 1][j] - prices[j]);
      }
    }

    // Return the maximum profit with at most `k` transactions on the last day
    return dp[k][n - 1];
  }

  // Dynamic Programming (DP)
  // https://leetcode.com/tag/dynamic-programming/
  //
  // Note: hard to understand
  //
  // - Time complexity: O(k*n)
  // - Space complexity: O(k)
  int max_profit_v2(int k, vector<int> const& prices) {
    if (k <= 0) {
      return 0;
    }

    int n = prices.size();
    if (n <= 1) {
      return 0;
    }

    if (k >= n / 2) {
      int max_profit = 0;
      for (int j = 1; j < n; ++j) {
        if (prices[j] > prices[j - 1]) {
          max_profit += prices[j] - prices[j - 1];
        }
      }

      return max_profit;
    }

    // `dp[i]` represents the maximum profit up to the `i`-th transaction
    vector<int> dp(k + 1, 0);
    // `min_price[i]` represents the minimum price to buy for the `i`-th
    // transaction
    vector<int> min_price(k + 1, prices[0]);

    for (int j = 0; j < n; ++j) {
      int price = prices[j];

      for (int i = 1; i <= k; ++i) {
        min_price[i] = std::min(min_price[i], price - dp[i - 1]);
        dp[i] = std::max(dp[i], price - min_price[i]);
      }
    }

    return dp[k];
  }

  // Brute Force
  //
  // - Time complexity: ?
  // - Space complexity: O(n)
  //
  // Note: result in Time Limit Exceeded (TLE)
  int max_profit_v3(int k, vector<int> const& prices) {
    if (k <= 0) {
      return 0;
    }

    int n = prices.size();
    if (n <= 1) {
      return 0;
    }

    return max_profit_v3_impl(prices, k, 0);
  }

  int max_profit_v3_impl(vector<int> const& prices, int k, int start) {
    // Output current state for debugging: the starting index (`start`) and the
    // remaining transactions (`k`).
    //
    // Note: Repeated calculations for the same `start` and `k` indicate a need
    // for memoization.
    std::cout << "max_profit_v3_impl: k = " << k << "; start = " << start
              << '\n';

    if (k == 0) {
      return 0;
    }

    int n = prices.size();
    if (start >= n) {
      return 0;
    }

    int max_profit = 0;
    for (int i = start; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        int buy = prices[i];
        int sell = prices[j];
        if (sell > buy) {
          int profit = sell - buy + max_profit_v3_impl(prices, k - 1, j + 1);
          max_profit = std::max(max_profit, profit);
        }
      }
    }

    return max_profit;
  }

  // Brute Force with Memoization
  // https://leetcode.com/tag/memoization/
  //
  // - Time complexity: ?
  // - Space complexity: O(k*n)
  //
  // Note: result in Time Limit Exceeded (TLE)
  int max_profit_v4(int k, vector<int> const& prices) {
    if (k <= 0) {
      return 0;
    }

    int n = prices.size();
    if (n <= 1) {
      return 0;
    }

    vector<vector<int>> memo(n, vector<int>(k + 1, -1));
    return max_profit_v4_impl(prices, k, 0, memo);
  }

  int max_profit_v4_impl(vector<int> const& prices, int k, int start,
                         vector<vector<int>>& memo) {
    if (k == 0) {
      return 0;
    }

    int n = prices.size();
    if (start >= n) {
      return 0;
    }

    if (memo[start][k] != -1) {
      return memo[start][k];
    }

    int max_profit = 0;
    for (int i = start; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        int buy = prices[i];
        int sell = prices[j];
        if (sell > buy) {
          int profit = sell - buy + max_profit_v4_impl(prices, k - 1, j + 1, memo);
          max_profit = std::max(max_profit, profit);
        }
      }
    }

    memo[start][k] = max_profit;
    return max_profit;
  }

  // Brute Force
  //
  // - Time complexity: ?
  // - Space complexity: O(n)
  //
  // Note: result in Time Limit Exceeded (TLE)
  int max_profit_v5(int k, vector<int> const& prices) {
    if (k <= 0) {
      return 0;
    }

    int n = prices.size();
    if (n <= 1) {
      return 0;
    }

    return max_profit_v5_impl(prices, k, 0, false);
  }

  int max_profit_v5_impl(vector<int> const& prices, int k, int start,
                         bool holding) {
    // Note: Repeated calculations for the same `k`, `start` and `holding`
    // indicate a need for memoization.
    std::cout << "max_profit_v5_impl: k = " << k << "; start = " << start
              << "; holding" << holding << '\n';

    if (k == 0) {
      return 0;
    }

    int n = prices.size();
    if (start >= n) {
      return 0;
    }

    // Case 1: Do nothing on the current day
    int do_nothing = max_profit_v5_impl(prices, k, start + 1, holding);

    // Case 2: Either buy or sell based on the current holding state
    int do_something = 0;
    if (holding) {
      // If holding a stock, sell it
      do_something = prices[start] + max_profit_v5_impl(prices, k - 1, start + 1, false);
    } else {
      // If not holding a stock, buy it
      do_something = max_profit_v5_impl(prices, k, start + 1, true) - prices[start];
    }

    return std::max(do_nothing, do_something);
  }

  // Top-Down Dynamic Programming (DP)
  // https://leetcode.com/tag/dynamic-programming/
  //
  // - Time complexity: O(k*n)
  // - Space complexity: O(k*n)
  int max_profit_v6(int k, vector<int> const& prices) {
    if (k <= 0) {
      return 0;
    }

    int n = prices.size();
    if (n <= 1) {
      return 0;
    }

    vector<vector<std::array<int, 2>>> memo(n, vector<std::array<int, 2>>(k + 1, {-1, -1}));
    return max_profit_v6_impl(prices, k, 0, false, memo);
  }

  int max_profit_v6_impl(vector<int> const& prices, int k, int start,
                         bool holding,
                         vector<vector<std::array<int, 2>>>& memo) {
    if (k == 0) {
      return 0;
    }

    int n = prices.size();
    if (start >= n) {
      return 0;
    }

    // If the current state has been computed, return its result
    if (memo[start][k][holding ? 1 : 0] != -1) {
      return memo[start][k][holding ? 1 : 0];
    }

    // Case 1: Do nothing on the current day
    int do_nothing = max_profit_v6_impl(prices, k, start + 1, holding, memo);

    // Case 2: Either buy or sell based on the current holding state
    int do_something = 0;
    if (holding) {
      // If holding a stock, sell it
      do_something = prices[start] + max_profit_v6_impl(prices, k - 1, start + 1, false, memo);
    } else {
      // If not holding a stock, buy it
      do_something = max_profit_v6_impl(prices, k, start + 1, true, memo) - prices[start];
    }

    memo[start][k][holding ? 1 : 0] = std::max(do_nothing, do_something);
    return memo[start][k][holding ? 1 : 0];
  }
};
