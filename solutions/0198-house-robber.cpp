// HoNooD <honood@gmail.com>
// 2024.07.03 23:25

// 198. House Robber
// https://leetcode.com/problems/house-robber/description/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Dynamic_programming

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// Dynamic Programming Approach
//
// 1. Define State:
//    - Use `dp[i]` to represent the maximum amount of money you can rob up to the `i`-th house.
//
// 2. State Transition:
//    - If you rob the current house `i`, the total amount will be `nums[i] + dp[i-2]`.
//    - If you do not rob the current house `i`, the total amount will be `dp[i-1]`.
//    - Hence, `dp[i] = max(nums[i] + dp[i-2], dp[i-1])`.
//
// 3. Initial State:
//    - If there are no houses, the result is `0`.
//    - If there is only one house, the result is the value of that house `nums[0]`.
//    - If there are two houses, the result is the maximum value between the two houses.
//
// 4. Final State:
//    - The last element in `dp` will hold the maximum amount of money that can be robbed.
class Solution {
public:
  int rob(vector<int>& nums) {
    // if there are no house, the maximum amount is 0
    if (nums.empty()) {
      return 0;
    }

    int n = nums.size();

    // if there is only one house, return the amount in that house
    if (n == 1) {
      return nums[0];
    }

    // if there are two houses, return the maximum amount between them
    if (n == 2) {
      return std::max(nums[0], nums[1]);
    }

    // initialize the dp array
    vector<int> dp(n, 0);
    dp[0] = nums[0]; // max amount for the first house
    dp[1] = std::max(nums[0], nums[1]); // max amount for the first two houses

    // fill the dp array according to the recurrence relation
    // Note: recurrence relation: [计]递归关系，递推关系
    for (int i = 2; i < n; ++i) {
      dp[i] = std::max(nums[i] + dp[i - 2], dp[i - 1]);
    }

    return dp[n - 1];
  }
};

// space optimized
class Solution_2 {
public:
  int rob(vector<int>& nums) {
    if (nums.empty()) {
      return 0;
    }

    int n = nums.size();

    int prev1 = nums[0];
    if (n == 1) {
      return prev1;
    }

    int prev2 = std::max(nums[0], nums[1]);
    if (n == 2) {
      return prev2;
    }

    for (int i = 2; i < n; ++i) {
      int curr = std::max(nums[i] + prev1, prev2);
      prev1 = prev2;
      prev2 = curr;
    }

    return prev2;
  }

  // more concise code
  /*
  int rob(vector<int>& nums) {
    if (nums.empty()) {
      return 0;
    }

    int prev1 = 0; // maximum amount up to the house before the last
    int prev2 = 0; // maximum amount up to the last house
    for (int num : nums) {
      int curr = max(num + prev1, prev2);
      prev1 = prev2;
      prev2 = curr;
    }

    return prev2;
  }
  */
};
