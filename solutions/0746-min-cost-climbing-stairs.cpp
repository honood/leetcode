// HoNooD <honood@gmail.com>
// 2025.03.28 09:15
//
// 746. Min Cost Climbing Stairs
// https://leetcode.com/problems/min-cost-climbing-stairs/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  int minCostClimbingStairs(vector<int>& cost) {
    return min_cost_climbing_stairs_v1(cost);
  }

private:
  // - Time complexity: O(n)
  // - Space complexity: O(n)
  int min_cost_climbing_stairs_v1(vector<int> const& cost) {
    int n = cost.size();
    vector<int> dp(n + 1, 0);
    // Base cases:
    // dp[0] = 0;
    // dp[1] = 0;

    // Fill the dp array
    for (int i = 2; i <= n; ++i) {
      dp[i] = std::min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
    }

    return dp[n];
  }

  // - Time complexity: O(n)
  // - Space complexity: O(1)
  int min_cost_climbing_stairs_v2(vector<int> const& cost) {
    int n = cost.size();
    int prev1 = 0;
    int prev2 = 0;

    for (int i = 2; i <= n; ++i) {
      int current = std::min(prev1 + cost[i - 1], prev2 + cost[i - 2]);

      prev2 = prev1;
      prev1 = current;
    }

    return prev1;
  }

  // - Time complexity: O(n)
  // - Space complexity: O(n)
  int min_cost_climbing_stairs_v3(vector<int> const& cost) {
    int n = cost.size();
    vector<int> memo(n + 1, -1);
    std::function<int(int)> min_cost = [&min_cost, &memo, &cost](int step) {
      // Base cases
      if (step <= 1) {
        return 0;
      }

      if (memo[step] != -1) {
        return memo[step];
      }

      memo[step] = std::min(min_cost(step - 1) + cost[step - 1],
                            min_cost(step - 2) + cost[step - 2]);
      return memo[step];
    };

    return min_cost(n);
  }
};
