// HoNooD
// 2024.06.03 21:05

// 918. Maximum Sum Circular Subarray
// https://leetcode.com/problems/maximum-sum-circular-subarray/description/?envType=study-plan-v2&envId=top-interview-150

// Note: A circular array means the end of the array connects to the beginning
// of the array. Formally, the next element of `nums[i]` is `nums[(i + 1) % n]`
// and the previous element of `nums[i]` is `nums[(i - 1 + n) % n]`.
//
// `n`: length of array `nums`.

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// Kadane's Algorithm
// https://en.wikipedia.org/wiki/Maximum_subarray_problem#Kadane's_algorithm
class Solution {
public:
  int maxSubarraySumCircular(vector<int>& nums) {
    assert(!nums.empty());

    int maxSum = nums[0];
    int currSum = 0;

    int n = nums.size();
    int total = n + (n - 1);
    int subarrayLeft = 0;
    for (int i = 0; i < total; ++i) {
      if (nums[i] > currSum + nums[i]) {
        currSum = nums[i];
      } else {
        currSum = currSum + nums[i];
      }

      if (currSum > maxSum) {
        maxSum = currSum;
      }
    }
  }

private:
  int kadane() {}
};
