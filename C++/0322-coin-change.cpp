// HoNooD <honood@gmail.com>
// 2024.07.04 20:56

// 322. Coin Change
// https://leetcode.com/problems/coin-change/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Dynamic_programming

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// Dynamic Programming Approach
//
// 1.	State Definition:
// Let `dp[i]` represent the minimum number of coins required to make up amount
// `i`.
//
// 2.	State Transition:
// For each amount `i`, try every `coin` in `coins`. If `i - coin` is
// non-negative, update `dp[i]` as the minimum of `dp[i]` and `dp[i - coin] +
// 1`.
//
// 3.	Initialization:
// Set `dp[0] = 0`, because 0 coins are required to make the amount 0.
// Initialize the rest of dp with `amount + 1`, which serves as a placeholder
// for infinity (i.e., the amount can’t be made up).
//
// 4.	Final Answer:
// If `dp[amount]` is still `amount + 1`, it means the amount can’t be formed,
// so return `-1`; otherwise, return `dp[amount]`.
class Solution {
public:
  int coinChange(vector<int>& coins, int amount) {
    // Represents a sentinel value indicating an unattainable amount.
    //
    // Any value in the range `[amount + 1, std::numeric_limits<int>::max() -
    // 1]` can serve this purpose.
    int const IMPOSSIBLE = amount + 1;
    vector<int> dp(amount + 1, IMPOSSIBLE);
    // Base case: amount 0 requires 0 coins
    dp[0] = 0;

    for (int i = 1; i <= amount; ++i) {
      for (int coin : coins) {
        if (i - coin >= 0) {
          dp[i] = std::min(dp[i], dp[i - coin] + 1);
        }
      }
    }

    return dp[amount] == IMPOSSIBLE ? -1 : dp[amount];
  }
};
