// HoNooD <honood@gmail.com>
// 2024.07.19 08:30

// 121. Best Time to Buy and Sell Stock
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  int maxProfit(vector<int>& prices) {
    return max_profit_v2(prices);
  }

private:
  // Brute Force
  // Note: result in Time Limit Exceeded (TLE)
  //
  // Complexity Analysis:
  // - Time complexity: O(n^2)
  // - Space complexity: O(1)
  int max_profit_v1(vector<int> const& prices) {
    int n = prices.size();
    if (n <= 1) {
      return 0;
    }

    int max_profit = 0;

    // for (int i = 0; i < n - 1; ++i) {
    //   for (int j = i + 1; j < n; ++j) {
    //     int buy = prices[i];
    //     int sell = prices[j];
    //     if (sell > buy) {
    //       max_profit = std::max(max_profit, sell - buy);
    //     }
    //   }
    // }

    for (int i = 0; i < n - 1; ++i) {
      int buy = prices[i];
      int sell = *std::max_element(std::next(prices.cbegin(), i + 1), prices.cend());
      if (sell > buy) {
        max_profit = std::max(max_profit, sell - buy);
      }
    }

    return max_profit;
  }

  // Dynamic Programming (DP)
  // https://leetcode.com/tag/dynamic-programming/
  //
  // Complexity Analysis:
  // - Time complexity: O(n)
  // - Space complexity: O(1)
  int max_profit_v2(vector<int> const& prices) {
    int min_price = std::numeric_limits<int>::max();
    int max_profix = 0;
    for (int price : prices) {
      min_price = std::min(min_price, price);
      max_profix = std::max(max_profix, price - min_price);
    }

    return max_profix;
  }
};
