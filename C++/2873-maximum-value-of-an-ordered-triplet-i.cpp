// HoNooD <honood@gmail.com>
// 2024.06.19 23:20

// 2873. Maximum Value of an Ordered Triplet I
// https://leetcode.com/problems/maximum-value-of-an-ordered-triplet-i/description/
//
// You are given a 0-indexed integer array `nums`.
//
// Return the maximum value over all triplets of indices `(i, j, k)` such that
// `i < j < k`. If all such triplets have a negative value, return `0`.
//
// The value of a triplet of indices `(i, j, k)` is equal to
// `(nums[i] - nums[j]) * nums[k]`.

// Exact Duplicate of:
// LeetCode 2874. Maximum Value of an Ordered Triplet II
// https://leetcode.com/problems/maximum-value-of-an-ordered-triplet-ii/description/

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  long long maximumTripletValue(vector<int>& nums) {
    int n = nums.size();
    if (n < 3) {
      return 0;
    }

    vector<int> leftMax(n, std::numeric_limits<int>::min());
    leftMax[0] = nums[0];
    for (int i = 1; i < n; ++i) {
      leftMax[i] = std::max(leftMax[i - 1], nums[i]);
    }

    vector<int> rightMax(n, std::numeric_limits<int>::min());
    rightMax[n - 1] = nums[n - 1];
    for (int i = n - 2; i >= 0; --i) {
      rightMax[i] = std::max(rightMax[i + 1], nums[i]);
    }

    long long maxValue = std::numeric_limits<long long>::min();
    for (int j = 1; j < n - 1; ++j) {
      if (leftMax[j - 1] > nums[j]) {
        long long value = (leftMax[j - 1] - nums[j]) * static_cast<long long>(rightMax[j + 1]);
        maxValue = std::max(maxValue, value);
      }
    }

    return maxValue == std::numeric_limits<long long>::min() ? 0 : maxValue;
  }
};
