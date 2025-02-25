// HoNooD <honood@gmail.com>
// 2025.02.25 21:00

// 1004. Max Consecutive Ones III
// https://leetcode.com/problems/max-consecutive-ones-iii/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  int longestOnes(vector<int>& nums, int k) {
    int max_len = 0;
    for (int zeros = 0, left = 0, right = 0; right < nums.size(); ++right) {
      if (nums[right] == 0) {
        ++zeros;
        while (zeros > k) {
          if (nums[left] == 0) {
            --zeros;
          }
          ++left;
        }
      }

      max_len = std::max(max_len, right - left + 1);
    }
    return max_len;
  }
};
