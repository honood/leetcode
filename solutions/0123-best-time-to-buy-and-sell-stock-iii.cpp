// HoNooD <honood@gmail.com>
// 2024.07.21 16:27

// 123. Best Time to Buy and Sell Stock III
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  int maxProfit(vector<int>& prices) {
    return max_profit_v5(prices);
  }

private:
  // Brute Force
  //
  // Note: result in Time Limit Exceeded (TLE)
  //
  // Time complexity: O(n^4)
  int max_profit_v1(vector<int> const& prices) {
    int n = prices.size();
    int max_profit = 0;
    for (int i = 0; i < n - 1; ++i) {
      for (int j = i + 1; j < n; ++j) {
        int trans1_profit = 0;
        if (prices[j] > prices[i]) {
          trans1_profit = prices[j] - prices[i];
        }

        int max_trans2_profit = 0;
        for (int k = j + 1; k < n; ++k) {
          for (int l = k + 1; l < n; ++l) {
            if (prices[l] > prices[k]) {
              max_trans2_profit = std::max(max_trans2_profit, prices[l] - prices[k]);
            }
          }
        }

        max_profit = std::max(max_profit, trans1_profit + max_trans2_profit);
      }
    }

    return max_profit;
  }

  // Brute Force
  //
  // Note: result in Time Limit Exceeded (TLE)
  //
  // Time complexity: O(n^3)
  int max_profit_v2(vector<int> const& prices) {
    int n = prices.size();
    if (n <= 1) {
      return 0;
    }

    if (n == 2) {
      int profit = prices[1] - prices[0];
      return profit > 0 ? profit : 0;
    }

    int max_profit = 0;
    for (int i = 1; i < n - 1; ++i) {
      for (int j = i; j < n - 1; ++j) {
        // first transaction from day `0` to day `i`
        int min_price = prices[0];
        int max_trans1_profit = 0;
        for (int k = 1; k <= i; ++k) {
          if (prices[k] < min_price) {
            min_price = prices[k];
          }

          if (int p = prices[k] - min_price; p > max_trans1_profit ) {
            max_trans1_profit = p;
          }
        }

        // second transaction from day `j` to day `n-1`
        min_price = prices[j];
        int max_trans2_profit = 0;
        for (int k = j + 1; k < n; ++k) {
          if (prices[k] < min_price) {
            min_price = prices[k];
          }

          if (int p = prices[k] - min_price; p > max_trans2_profit) {
            max_trans2_profit = p;
          }
        }

        if (int p = max_trans1_profit + max_trans2_profit; p > max_profit) {
          max_profit = p;
        }
      }
    }

    return max_profit;
  }


  // Brute Force
  //
  // Note: result in Time Limit Exceeded (TLE)
  //
  // Time complexity: O(n^3)
  int max_profit_v3(vector<int> const& prices) {
    int n = prices.size();
    int max_profit = 0;
    // Note: `i` should start from `0`, not `1`, to handle cases like `[1, 2]` correctly.
    for (int i = 0; i < n - 1; ++i) {
      for (int j = i; j < n - 1; ++j) {
        int max_trans1_profit = 0;
        for (int k = 0; k < i; ++k) {
          if (int p = prices[i] - prices[k]; p > max_trans1_profit) {
            max_trans1_profit = p;
          }
        }

        int max_trans2_profit = 0;
        for (int k = j + 1; k < n; ++k) {
          if (int p = prices[k] - prices[j]; p > max_trans2_profit) {
            max_trans2_profit = p;
          }
        }

        if (int p = max_trans1_profit + max_trans2_profit; p > max_profit) {
          max_profit = p;
        }
      }
    }

    return max_profit;
  }

  // Dynamic Programming (DP)
  // https://leetcode.com/tag/dynamic-programming/
  //
  // - Time complexity: O(n)
  // - Space complexity: O(n)
  int max_profit_v4(vector<int> const& prices) {
    int n = prices.size();
    if (n <= 1) {
      return 0;
    }

    if (n == 2) {
      int profit = prices[1] - prices[0];
      return profit > 0 ? profit : 0;
    }

    // `left_profit[i]` represents the maximum profit that can be achieved from
    // day `0` to day `i`
    vector<int> left_profit(n, 0);
    // `rightProfit[i]` represents the maximum profit that can be achieved from
    // day `i` to the last day
    vector<int> right_profit(n, 0);

    int min_price = prices[0];
    for (int i = 1; i < n; ++i) {
      min_price = std::min(min_price, prices[i]);
      left_profit[i] = std::max(left_profit[i - 1], prices[i] - min_price);
    }

    int max_price = prices[n - 1];
    for (int i = n - 2; i >= 0; --i) {
      max_price = std::max(max_price, prices[i]);
      right_profit[i] = std::max(right_profit[i + 1], max_price - prices[i]);
    }

    int max_profit = 0;
    for (int i = 0; i < n; ++i) {
      max_profit = std::max(max_profit, left_profit[i] + right_profit[i]);
    }

    return max_profit;
  }

  // Dynamic Programming (DP)
  // https://leetcode.com/tag/dynamic-programming/
  //
  // Since we are allowed to complete at most two transactions, after each day,
  // we can be in one of the following five states:
	// 1.	No transactions have been made.
	// 2.	One buy transaction has been completed.
	// 3.	One buy and one sell transaction have been completed, i.e., one
	//    transaction has been finished.
	// 4.	After completing one transaction, a second buy transaction has been made.
	// 5.	Both transactions (one buy and one sell each) have been completed.
	//
	// Since the profit for the first state is obviously 0, we do not need to
	// record it. For the remaining four states, we will keep track of their
	// maximum profits as `buy1`, `sell1`, `buy2`, and `sell2`.
	//
	// Given the states at the end of day `i-1`, we need to compute the states at
	// the end of day `i` using state transition equations.
	//
	// It is important to understand that regardless of whether the problem allows
	// "buying and selling on the same day", the final answer will not be affected
	// because such operations yield zero profit.
  //
  // - Time complexity: O(n)
  // - Space complexity: O(1)
  int max_profit_v5(vector<int> const& prices) {
    // Note: It might be clearer to rename `buy1`, `sell1`, `buy2` and `sell2`
    // to `hold1`, `sold1`, `hold2` and `sold2`, respectively.

    // Represents the maximum profit after the first buy
    // Initialized to negative infinity because buying a stock means an outflow of money
    int buy1 = std::numeric_limits<int>::min();
    // Represents the maximum profit after the first sell
    // Initialized to `0` because no transaction has been made yet
    int sell1 = 0;
    // Represents the maximum profit after the second buy
    // Initialized to negative infinity for the same reason as `buy1`
    int buy2 = std::numeric_limits<int>::min();
    // Represents the maximum profit after the second sell
    // Initialized to `0` because no second transaction has been made yet
    int sell2 = 0;

    /*
    for (int price : prices) {
      int prev_buy1 = buy1;
      int prev_sell1 = sell1;
      int prev_buy2 = buy2;
      int prev_sell2 = sell2;

      buy1 = std::max(prev_buy1, -price);
      sell1 = std::max(prev_sell1, prev_buy1 + price);
      buy2 = std::max(prev_buy2, prev_sell1 - price);
      sell2 = std::max(prev_sell2, prev_buy2 + price);
    }

    return std::max(sell1, sell2);
    */

    for (int price : prices) {
      // Note: The variables must be updated in the correct order

      // keep the current `buy1` value or buy at the current price (which means
      // spending money, so it’s negative)
      buy1 = std::max(buy1, -price);
      // keep the current `sell1` value or sell at the current price (which
      // means gaining money, so it's `buy1` plus the current price)
      sell1 = std::max(sell1, buy1 + price);
      // keep the current `buy2` value or buy again at the current price after
      // having sold previously (so it's `sell1` minus the current price, as
      // it's another spending)
      buy2 = std::max(buy2, sell1 - price);
      // keep the current `sell2` value or sell at the current price (which
      // means gaining money, so it's `buy2` plus the current price)
      sell2 = std::max(sell2, buy2 + price);
    }

    return sell2;
  }
};
