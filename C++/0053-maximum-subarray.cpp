// HoNooD
// 2024.06.02 16:05

// 53. Maximum Subarray
// https://leetcode.com/problems/maximum-subarray/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// Brute Force
// Time Limit Exceeded, NOT recommended!
class Solution {
public:
  int maxSubArray(vector<int>& nums) {
    assert(!nums.empty());

    // Do not initialize to 0 as all elements may be negative.
    int maxSum = nums[0];

    int n = nums.size();
    for (int i = 0; i < n; ++i) {
      int sum = 0;
      for (int j = i; j < n; ++j) {
        sum += nums[j];
        if (sum > maxSum) {
          maxSum = sum;
        }
      }
    }

    return maxSum;
  }
};

// Dynamic Programming (Kadane's Algorithm)
// https://en.wikipedia.org/wiki/Maximum_subarray_problem#Kadane's_algorithm
//
// Best!
class Solution_2 {
public:
  int maxSubArray(vector<int>& nums) {
    assert(!nums.empty());

    int maxSum = nums[0];
    int currSum = nums[0];
    for (int i = 1; i < nums.size(); ++i) {
      if (int s = currSum + nums[i]; nums[i] > s) {
        currSum = nums[i];
      } else {
        currSum = s;
      }

      if (currSum > maxSum) {
        maxSum = currSum;
      }
    }

    return maxSum;
  }
};

// Prefix Sum
// https://en.wikipedia.org/wiki/Prefix_sum
//
// Best!
class Solution_3 {
public:
  int maxSubArray(vector<int>& nums) {
    assert(!nums.empty());

    int maxSum = nums[0];
    int currSum = 0;
    for (int i = 0; i < nums.size(); ++i) {
      currSum += nums[i];
      if (currSum > maxSum) {
        maxSum = currSum;
      }

      if (currSum < 0) {
        currSum = 0;
      }
    }

    return maxSum;
  }
};

// Divide and Conquer Algorithm
// https://en.wikipedia.org/wiki/Divide-and-conquer_algorithm
class Solution_4 {
public:
  int maxSubArray(vector<int>& nums) {
    assert(!nums.empty());

    return impl(nums, 0, nums.size() - 1);
  }

private:
  int impl(vector<int> const& nums, int left, int right) {
    if (left == right) {
      return nums[left];
    }

    // Note: The `left > right` scenario does not occur due to the nature of the
    // recursive division and the termination condition of the function. The
    // function structure ensures that only valid indices are used, making an
    // explicit check for `left > right` unnecessary.

    // Note: this way of calculating `mid` is safe from integer overflow.
    int mid = left + (right - left) / 2;

    int leftMax = impl(nums, left, mid);
    int rightMax = impl(nums, mid + 1, right);
    int crossMax = maxCrossingSubArray(nums, left, mid, right);

    return std::max({leftMax, rightMax, crossMax});
  }

  int maxCrossingSubArray(vector<int> const& nums, int left, int mid, int right) {
    assert(left <= mid);
    assert(mid <= right);

    int sum = 0;
    int leftMaxSum = std::numeric_limits<int>::min();
    for (int i = mid; i >= left; --i) {
      sum += nums[i];
      if (sum > leftMaxSum) {
        leftMaxSum = sum;
      }
    }

    sum = 0;
    int rightMaxSum = std::numeric_limits<int>::min();
    for (int i = mid + 1; i <= right; ++i) {
      sum += nums[i];
      if (sum > rightMaxSum) {
        rightMaxSum = sum;
      }
    }

    return leftMaxSum + rightMaxSum;
  }
};
