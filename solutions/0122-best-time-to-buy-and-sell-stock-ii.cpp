// HoNooD <honood@gmail.com>
// 2024.07.19 10:00

// 122. Best Time to Buy and Sell Stock II
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  int maxProfit(vector<int>& prices) {
    return max_profit_v3(prices);
  }

private:
  // Brute Force
  //
  // The brute force approach to solving the problem involves trying all
  // possible combinations of buy and sell days to find the maximum profit.
  //
  // Complexity Analysis:
  // - Time complexity: O(2^n)  // TODO: how to understand? recursion tree?
  // - Space complexity: O(n)
  int max_profit_v1(vector<int> const& prices) {
    if (prices.size() <= 1) {
      return 0;
    }

    return max_profit_v1_impl(prices, 0);
  }

  int max_profit_v1_impl(vector<int> const& prices, int start) {
    // Check if the same `start` value is being recalculated multiple times.
    // If so, consider optimizing with Memoization.
    std::cout << "max_profit_v1_impl: start = " << start << '\n';

    int n = prices.size();
    if (start >= n) {
      return 0;
    }

    int max_profit = 0;
    for (int i = start; i < n - 1; ++i) {
      for (int j = i + 1; j < n; ++j) {
        int buy = prices[i];
        int sell = prices[j];
        if (sell > buy) {
          int profit = (sell - buy) + max_profit_v1_impl(prices, j + 1);
          max_profit = std::max(max_profit, profit);
        }
      }
    }

    return max_profit;
  }

  // Brute Force with Memoization
  // https://leetcode.com/tag/memoization/
  //
  // Complexity Analysis:
  // - Time complexity: O(n^3) // ?
  //   - Number of States: There are `n` different starting positions, where `n`
  //     is the number of days.
  //   - Time to Compute Each State: Calculating each state involves two nested
  //     loops, leading to a time complexity of `O(n^2)` for each state.
  //   - With memoization, each state is computed at most once.
  // - Space complexity: O(n)
  int max_profit_v2(vector<int> const& prices) {
    int n = prices.size();
    if (n <= 1) {
      return 0;
    }

    vector<int> memo(n, -1);
    return max_profit_v2_impl(prices, 0, memo);
  }

  int max_profit_v2_impl(vector<int> const& prices, int start,
                         vector<int>& memo) {
    int n = prices.size();
    if (start >= n) {
      return 0;
    }

    // If already computed, return the stored result
    if (memo[start] != -1) {
      return memo[start];
    }

    int max_profit = 0;
    for (int i = start; i < n - 1; ++i) {
      for (int j = i + 1; j < n; ++j) {
        int buy = prices[i];
        int sell = prices[j];
        if (sell > buy) {
          int profit = (sell - buy) + max_profit_v2_impl(prices, j + 1, memo);
          max_profit = std::max(max_profit, profit);
        }
      }
    }

    memo[start] = max_profit;
    return max_profit;
  }

  // Greedy algorithm
  // https://leetcode.com/tag/greedy/
  //
  // Complexity Analysis:
  // - Time complexity: O(n)
  // - Space complexity: O(1)
  int max_profit_v3(vector<int> const& prices) {
    int max_profit = 0;
    for (int i = 1; i < prices.size(); ++i) {
      if (prices[i] > prices[i - 1]) {
        max_profit += prices[i] - prices[i - 1];
      }
    }

    return max_profit;
  }

  // Dynamic Programming (DP)
  // https://leetcode.com/tag/dynamic-programming/
  //
  // Complexity Analysis:
  // - Time complexity: O(n)
  // - Space complexity: O(n)
  int max_profit_v4(vector<int> const& prices) {
    int n = prices.size();
    if (n <= 1) {
      return 0;
    }

    // Create a DP table
    //
    // `dp[i].first`: the maximum profit on day `i` if no stock is held
    // `dp[i].second`: the maximum profit on day `i` if a stock is held
    std::vector<pair<int, int>> dp(n, {0, 0});

    // Initial state
    //
    // On day `0`, if no stock is held, the profit is `0`
    dp[0].first = 0;
    // On day `0`, if a stock is held, the profit is `-prices[0]` due to the
    // purchase cost
    dp[0].second = -prices[0];

    // Fill the DP table
    for (int i = 1; i < n; ++i) {
      // Maximum profit on day `i` without holding stock:
      // 1. Continuation of not holding stock from day `i-1`: `dp[i-1].first`
      // 2. Selling stock held from day `i-1`: `dp[i-1].second + prices[i]`
      dp[i].first = std::max(dp[i - 1].first, dp[i - 1].second + prices[i]);
      // Maximum profit on day `i` with holding stock:
      // 1. Continuation of holding stock from day `i-1`: `dp[i-1].second`
      // 2. Buying stock on day `i`: `dp[i-1].first - prices[i]`
      dp[i].second = std::max(dp[i - 1].second, dp[i - 1].first - prices[i]);
    }

    // Maximum profit on the last day without holding stock
    return dp[n - 1].first;
  }

  // Top-Down Dynamic Programming (DP)
  // https://leetcode.com/tag/dynamic-programming/
  //
  // Complexity Analysis:
  // - Time complexity: O(n)
  // - Space complexity: O(n)
  int max_profit_v5(vector<int> const& prices) {
    int n = prices.size();
    if (n <= 1) {
      return 0;
    }

    vector<ProfitCache> memo(n);
    return max_profit_v5_impl(prices, 0, false, memo);
  }

  class ProfitCache;
  int max_profit_v5_impl(vector<int> const& prices, int start, bool holding,
                         vector<ProfitCache>& memo) {
    if (start >= prices.size()) {
      return 0;
    }

    // If the current state has been computed, return its result
    if (memo[start].has_set(holding)) {
      return memo[start].profit(holding);
    }

    // Case 1: Do nothing on the current day
    int do_nothing = max_profit_v5_impl(prices, start + 1, holding, memo);

    // Case 2: Either buy or sell based on the current holding state
    int do_something = 0;
    if (holding) {
      // If holding a stock, sell it
      do_something = prices[start] + max_profit_v5_impl(prices, start + 1, false, memo);
    } else {
      // If not holding a stock, buy it
      do_something = max_profit_v5_impl(prices, start + 1, true, memo) - prices[start];
    }

    memo[start].set_profit(holding, std::max(do_nothing, do_something));
    return memo[start].profit(holding);
  }

  class ProfitCache {
  public:
    // Check if the profit for the given state has been set
    bool has_set(bool holding) const {
      return holding ? holding_ != -1 : not_holding_ != -1;
    }

    // Set the profit for the given state
    void set_profit(bool holding, int profit) {
      if (holding) {
        holding_ = profit;
      } else {
        not_holding_ = profit;
      }
    }

    // Get the profit for the given state
    int profit(bool holding) const {
      return holding ? holding_ : not_holding_;
    }

  private:
    int not_holding_{-1}; // Profit when not holding stock
    int holding_{-1};     // Profit when holding stock
  };
};
