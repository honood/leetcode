// HoNooD <honood@gmail.com>
// 2024.07.03 23:25

// 198. House Robber
// https://leetcode.com/problems/house-robber/description/?envType=study-plan-v2&envId=top-interview-150
// https://leetcode.com/problems/house-robber/description/?envType=study-plan-v2&envId=leetcode-75

// https://en.wikipedia.org/wiki/Dynamic_programming

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  int rob(vector<int>& nums) {
    return rob_v1(nums);
  }

private:
  // - Time complexity: O(n)
  // - Space complexity: O(n)
  int rob_v1(vector<int> const& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];

    // dp[i] represents the maximum amount that can be robbed up to house i
    vector<int> dp(n);

    // Base cases
    dp[0] = nums[0];
    dp[1] = std::max(nums[0], nums[1]);

    // Fill the dp table using the recurrence relation
    for (int i = 2; i < n; ++i) {
      // Option 1: Rob house i (cannot rob i-1)
      int rob_current = nums[i] + dp[i - 2];
      // Option 2: Don't rob house i (max is same as max up to i-1)
      int skip_current = dp[i - 1];
      dp[i] = std::max(rob_current, skip_current);
    }

    // The final answer is the maximum amount considering all houses
    return dp[n - 1];
  }

  // - Time complexity: O(n)
  // - Space complexity: O(1)
  int rob_v2(vector<int> const& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];

    int prev2 = nums[0]; // dp[i-2]
    int prev1 = std::max(nums[0], nums[1]); // dp[i-1]

    for (int i = 2; i < n; ++i) {
      int current = std::max(prev2 + nums[i], prev1);

      prev2 = prev1;
      prev1 = current;
    }

    return prev1;
  }

  // - Time complexity: O(n)
  // - Space complexity: O(n)
  int rob_v3(vector<int> const& nums) {
    int n = nums.size();
    vector<int> memo(n, -1);
    std::function<int(int)> solve = [&solve, &nums, &memo](int i) {
      // Base case: No houses left
      if (i < 0) {
        return 0;
      }

      if (memo[i] != -1) {
        return memo[i];
      }

      memo[i] = std::max(nums[i] + solve(i - 2), solve(i - 1));
      return memo[i];
    };

    return solve(n - 1);
  }
};
