// HoNooD <honood@gmail.com>
// 2024.07.25 15:53

// 55. Jump Game
// https://leetcode.com/problems/jump-game/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  bool canJump(vector<int>& nums) {
    return can_jump_v1(nums);
  }

private:
  // Greedy algorithm
  // https://leetcode.com/tag/greedy/
  //
  // - Time complexity: O(n)
  // - Space complexity: O(1)
  bool can_jump_v1(vector<int> const& nums) {
    if (nums.empty()) {
      return false;
    }

    int n = nums.size();
    if (n == 1) {
      return nums[0] >= 0;
    }

    /*
    // debug code
    bool can_reach = false;
    int end = n - 1;
    for (int i = n - 2; i >= 0; --i) {
      if (i + nums[i] >= end) {
        can_reach = true;
        end = i;
      } else {
        can_reach = false;
      }
    }

    return can_reach;
    */

    int end = n - 1;
    for (int i = n - 2; i >= 0; --i) {
      if (i + nums[i] >= end) {
        end = i;
      }
    }

    return end == 0;
  }

  // Greedy algorithm
  // https://leetcode.com/tag/greedy/
  //
  // - Time complexity: O(n)
  // - Space complexity: O(1)
  bool can_jump_v2(vector<int> const& nums) {
    if (nums.empty()) {
      return false;
    }

    int n = nums.size();
    if (n == 1) {
      return nums[0] >= 0;
    }

    int max_reachable = 0;
    for (int i = 0; i < n; ++i) {
      // If the current index `i` is greater than the furthest position we can
      // reach so far (i.e., `max_reachable`), it means we cannot jump to this
      // position from any of the previous positions, hence it is impossible to
      // reach the end.
      if (i > max_reachable) {
        return false;
      }

      // Update the maximum reachable position from the current index `i`
      max_reachable = std::max(max_reachable, i + nums[i]);
    }

    // If the loop completes, check if the last position is within the maximum
    // reachable range
    return max_reachable >= n - 1;
  }

  // Dynamic Programming (DP)
  // https://leetcode.com/tag/dynamic-programming/
  //
  // - Time complexity: O(n^2)
  // - Space complexity: O(n)
  bool can_jump_v3(vector<int> const& nums) {
    if (nums.empty()) {
      return false;
    }

    int n = nums.size();
    if (n == 1) {
      return nums[0] >= 0;
    }

    vector<bool> dp(n, false);
    dp[0] = true;

    for (int i = 0; i < n; ++i) {
      if (dp[i]) { // if the current position is reachable
        // update all positions reachable from the current position
        for (int j = 1; j <= nums[i] && i + j < n; ++j) {
          dp[i + j] = true;
        }
      }
    }

    // return whether the last position is reachable
    return dp[n - 1];
  }

  // Brute Force
  //
  // - Time complexity: exponential time (recursion tree)
  // - Space complexity: O(n)
  //
  // Note: result in Time Limit Exceeded (TLE)
  bool can_jump_v4(vector<int> const& nums) {
    if (nums.empty()) {
      return false;
    }

    int n = nums.size();
    if (n == 1) {
      return nums[0] >= 0;
    }

    return can_jump_from_position(0, nums);
  }

  bool can_jump_from_position(int position, vector<int> const& nums) {
    int n = nums.size();
    if (position >= n - 1) {
      return true;
    }

    int furthest_jump = std::min(position + nums[position], n - 1);
    for (int i = position + 1; i <= furthest_jump; ++i) {
      if (can_jump_from_position(i, nums)) {
        return true;
      }
    }

    return false;
  }
};
