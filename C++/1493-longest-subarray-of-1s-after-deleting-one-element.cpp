// HoNooD <honood@gmail.com>
// 2025.02.26 10:51

// 1493. Longest Subarray of 1's After Deleting One Element
// https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  int longestSubarray(vector<int>& nums) {
    int max_len = 0;
    for (int zeros = 0, left = 0, right = 0; right < nums.size(); ++right) {
      if (nums[right] == 0) {
        ++zeros;
        while (zeros > 1) {
          if (nums[left] == 0) {
            --zeros;
          }
          ++left;
        }
      }

      max_len = std::max(max_len, right - left);
    }
    return max_len;
  }
};
