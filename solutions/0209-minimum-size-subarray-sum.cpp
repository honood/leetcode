// HoNooD <honood@gmail.com>
// 2024.06.23 15:57

// 209. Minimum Size Subarray Sum
// https://leetcode.com/problems/minimum-size-subarray-sum/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// sliding window technique
class Solution {
public:
  int minSubArrayLen(int target, vector<int>& nums) {
    int n = nums.size();
    int left = 0;
    int curr_sum = 0;
    int min_len = std::numeric_limits<int>::max();
    for (int right = 0; right < n; ++right) {
      // expand the window by adding `nums[right]` to the current sum
      curr_sum += nums[right];

      // shrink the window as long as the current sum is greater than or equal
      // to the target
      while (curr_sum >= target) {
        min_len = std::min(min_len, right - left + 1);
        // shrink the window by subtracting `nums[left]` from the current sum
        curr_sum -= nums[left];
        ++left;
      }
    }

    return min_len == std::numeric_limits<int>::max() ? 0 : min_len;
  }
};
