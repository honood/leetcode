// HoNooD <honood@gmail.com>
// 2024.07.25 20:08

// 45. Jump Game II
// https://leetcode.com/problems/jump-game-ii/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  int jump(vector<int>& nums) {
    return jump_v4(nums);
  }

private:
  // Brute Force
  //
  // - Time complexity: exponential time (recursion tree)
  // - Space complexity: O(n)
  //
  // Note: result in Time Limit Exceeded (TLE)
  int jump_v1(vector<int> const& nums) {
    int n = nums.size();
    // no jump needed if there's only one element
    if (n <= 1) {
      return 0;
    }

    return min_jumps_from_position(0, nums);
  }

  int min_jumps_from_position(int position, vector<int> const& nums) {
    // Note: repeated calculations for the same `position` indicate a need
    // for memoization.
    std::cout << "min_jumps_from_position: position = " << position << '\n';

    int n = nums.size();
    if (position >= n - 1) {
      return 0;
    }

    int max_jump = nums[position];
    // if unable to jump further from this position
    if (max_jump == 0) {
      return std::numeric_limits<int>::max();
    }

    int min_jumps = std::numeric_limits<int>::max();
    for (int i = 1; i <= max_jump; ++i) {
      int jumps = min_jumps_from_position(position + i, nums);
      if (jumps != std::numeric_limits<int>::max()) {
        min_jumps = std::min(min_jumps, jumps + 1);
      }
    }

    return min_jumps;
  }

  // Brute Force with Memoization
  // https://leetcode.com/tag/memoization/
  //
  // - Time complexity: O(n^2)
  // - Space complexity: O(n)
  int jump_v2(vector<int> const& nums) {
    int n = nums.size();
    // no jump needed if there's only one element
    if (n <= 1) {
      return 0;
    }

    vector<int> memo(n, -1);
    return min_jumps_from_position_with_memo(0, nums, memo);
  }

  int min_jumps_from_position_with_memo(int position, vector<int> const& nums,
                                        vector<int>& memo) {
    int n = nums.size();
    if (position >= n - 1) {
      return 0;
    }

    if (memo[position] != -1) {
      return memo[position];
    }

    int max_jump = nums[position];
    // if unable to jump further from this position
    if (max_jump == 0) {
      return std::numeric_limits<int>::max();
    }

    int min_jumps = std::numeric_limits<int>::max();
    for (int i = 1; i <= max_jump; ++i) {
      int jumps = min_jumps_from_position_with_memo(position + i, nums, memo);
      if (jumps != std::numeric_limits<int>::max()) {
        min_jumps = std::min(min_jumps, jumps + 1);
      }
    }

    memo[position] = min_jumps;
    return min_jumps;
  }

  // Dynamic Programming (DP)
  // https://leetcode.com/tag/dynamic-programming/
  //
  // - Time complexity: O(n^2)
  // - Space complexity: O(n)
  int jump_v3(vector<int> const& nums) {
    int n = nums.size();
    // no jump needed if there's only one element
    if (n <= 1) {
      return 0;
    }

    // `dp[i]` represents the minimum number of jumps needed to reach position
    // `i` from the start
    vector<int> dp(n, std::numeric_limits<int>::max());
    // starting point requires 0 jumps
    dp[0] = 0;

    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j <= i + nums[i] && j < n; ++j) {
        dp[j] = std::min(dp[j], dp[i] + 1);
      }
    }

    return dp[n - 1];
  }

  // Greedy algorithm
  // https://leetcode.com/tag/greedy/
  //
  // - Time complexity: O(n)
  // - Space complexity: O(1)
  int jump_v4(vector<int> const& nums) {
    int n = nums.size();
    // no jump needed if there's only one element
    if (n <= 1) {
      return 0;
    }

    int jumps = 0;
    // the end of the current jump range
    int curr_end = 0;
    // the farthest reachable position from the current position
    int farthest = 0;

    for (int i = 0; i < n - 1; ++i) {
      farthest = std::max(farthest, i + nums[i]);

      // if the end of the current jump range is reached
      if (i == curr_end) {
        // if unable to move any further, return `-1`
        if (curr_end == farthest) {
          return -1;
        }

        ++jumps;
        curr_end = farthest;
      }
    }

    // check if the last element is reachable
    return curr_end >= n - 1 ? jumps : -1;
  }
};
