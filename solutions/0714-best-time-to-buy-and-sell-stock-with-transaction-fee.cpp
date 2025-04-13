// HoNooD <honood@gmail.com>
// 2025.04.13 17:30
//
// 714. Best Time to Buy and Sell Stock with Transaction Fee
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  int maxProfit(vector<int>& prices, int fee) {
    return max_profit_v1(prices, fee);
  }

private:
  // - Time complexity: O(n)
  // - Space complexity: O(n)
  int max_profit_v1(vector<int>& prices, int fee) {
    int n = prices.size();
    if (n < 2) { // Cannot complete a transaction
      return 0;
    }

    vector<int> hold(n); // Max profit ending with holding stock on day i
    vector<int> sold(n); // Max profit ending with not holding stock on day i

    // Base case for day 0
    hold[0] = -prices[0]; // Buy on day 0
    sold[0] = 0; // Do nothing on day 0

    for (int i = 1; i < n; ++i) {
      // Max profit if holding stock today:
      // 1. Held stock yesterday
      // 2. Did not hold stock yesterday (sold state), buy today
      hold[i] = std::max(hold[i - 1], sold[i - 1] - prices[i]);

      // Max profit if not holding stock today (sold state):
      // 1. Did not hold stock yesterday (sold state)
      // 2. Held stock yesterday, sell today (pay fee)
      sold[i] = std::max(sold[i - 1], hold[i - 1] + prices[i] - fee);
    }

    return sold[n - 1];
  }

  // - Time complexity: O(n)
  // - Space complexity: O(1)
  int max_profit_v2(vector<int>& prices, int fee) {
    int n = prices.size();
    if (n < 2) {
      return 0;
    }

    // Initialize states based on day 0
    int hold = -prices[0]; // Max profit if holding stock after day i's action
    int sold = 0; // Max profit if not holding stock after day i's action

    for (int i = 1; i < n; ++i) {
      int prev_hold = hold;

      // Continue holding or buy
      hold = std::max(hold, sold - prices[i]);
      // Continue not holding or sell
      sold = std::max(sold, prev_hold + prices[i] - fee);
    }

    return sold;
  }

  // - Time complexity: O(n)
  // - Space complexity: O(1)
  int max_profit_v3(vector<int>& prices, int fee) {
    if (prices.empty()) return 0;

    // Initialize 'buy_price' with the price of the first day.
    // This represents the effective cost of the stock we are currently
    // 'holding' (or the lowest price encountered since the last sell).
    int buy_price = prices[0];

    // Initialize the total accumulated profit.
    int max_profit = 0;

    // Iterate through the prices starting from the second day.
    for (int i = 1; i < prices.size(); ++i) {
      int current_price = prices[i];

      // --- Greedy Decision Point ---

      // Condition 1: Check if selling at the current price is profitable.
      // Profit exists if current_price > buy_price + fee.
      if (current_price > buy_price + fee) {
        // Calculate the profit from this transaction.
        int current_profit = current_price - buy_price - fee;
        // Add this profit to the total accumulated profit.
        max_profit += current_profit;

        // ** Crucial Greedy Step **: Update buy_price after selling.
        // We set the new buy_price benchmark relative to the selling price.
        // This allows chaining profits if the price continues to rise,
        // effectively "carrying over" the stock without paying the fee again immediately.
        // The next profitable sell must exceed (current_price - fee) + fee = current_price.
        buy_price = current_price - fee;
      } else {
        // Condition 2: Cannot sell profitably OR price is not high enough.
        // Check if the current price offers a lower potential buying point.
        // If current_price is less than our current effective buy_price, it
        // means we found a better entry point if we were to buy now.
        buy_price = std::min(buy_price, current_price);
      }
    }

    // Return the total maximum profit accumulated.
    return max_profit;
  }
};
