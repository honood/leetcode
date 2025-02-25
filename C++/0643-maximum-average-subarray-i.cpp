// HoNooD <honood@gmail.com>
// 2025.02.25 08:30

// 643. Maximum Average Subarray I
// https://leetcode.com/problems/maximum-average-subarray-i/description/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  double findMaxAverage(vector<int>& nums, int k) {
    assert(k > 0);
    int n = nums.size();
    assert(n >= k);

    int k_sum = std::reduce(nums.cbegin(), std::next(nums.cbegin(), k));
    int max_k_sum = k_sum;
    for (int left = 1, right = k; right < n; ++left, ++right) {
      k_sum += nums[right] - nums[left - 1];
      max_k_sum = std::max(max_k_sum, k_sum);
    }

    return static_cast<double>(max_k_sum) / k;
  }
};
