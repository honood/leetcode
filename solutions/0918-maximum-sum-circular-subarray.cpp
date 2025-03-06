// HoNooD <honood@gmail.com>
// 2024.07.15 00:01

// 918. Maximum Sum Circular Subarray
// https://leetcode.com/problems/maximum-sum-circular-subarray/description/
//
// A circular array means the end of the array connects to the beginning of the
// array. Formally, the next element of `nums[i]` is `nums[(i + 1) % n]` and the
// previous element of `nums[i]` is `nums[(i - 1 + n) % n]`.

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  int maxSubarraySumCircular(vector<int>& nums) {
    return max_subarray_sum_circular_v3(nums);
  }

private:
  // Brute Force
  //
  // Time complexity: O(n^3)
  //
  // Note: result in Time Limit Exceeded (TLE)
  int max_subarray_sum_circular_v1(vector<int> const& nums) {
    if (nums.empty()) {
      return 0;
    }

    int n = nums.size();
    int res = std::numeric_limits<int>::min();

    for (int subarr_sz = 1; subarr_sz <= n; ++subarr_sz) {
      for (int start = 0; start <= n - 1; ++start) {
        int sum = 0;
        for (int i = start; i < start + subarr_sz; ++i) {
          sum += nums[i % n];
        }
        res = std::max(res, sum);
      }
    }

    return res;
  }

  // Brute Force
  //
  // Time complexity: O(n^2)
  //
  // Note: result in Time Limit Exceeded (TLE)
  int max_subarray_sum_circular_v2(vector<int> const& nums) {
    if (nums.empty()) {
      return 0;
    }

    int n = nums.size();
    int res = nums[0];

    for (int start = 0; start < n; ++start) {
      int sum = 0;
      // Note:
      // 1. `offset` indicates the relative position of the last element in the
      //    subarray starting from `start`.
      // 2. This loop calculates the sum of all possible subarrays starting from
      //    `start` and updates the maximum sum found so far.
      for (int offset = 0; offset < n; ++offset) {
        int idx = (start + offset) % n;
        sum += nums[idx];
        res = std::max(res, sum);
      }
    }

    return res;
  }

  // Kadane's Algorithm
  //
  // Finding the maximum sum of a circular subarray involves extending the
  // classic Kadane's algorithm, which is used to find the maximum sum of a
  // non-circular subarray.
  //
  // For a circular array, two scenarios must be considered:
  // 1. The maximum subarray is entirely within the array and does not span the
  //    ends.
  // 2. The maximum subarray spans the ends of the array, including both the
  //    tail and head.
  //
  // Time complexity: O(n)
  int max_subarray_sum_circular_v3(vector<int> const& nums) {
    if (nums.empty()) {
      return 0;
    }

    // https://en.wikipedia.org/wiki/Maximum_subarray_problem#Kadane's_algorithm
    auto kadane = [](vector<int> const& nums) {
      int max_ending_here = nums[0];
      int max_so_far = nums[0];
      for (int i = 1; i < nums.size(); ++i) {
        max_ending_here = std::max(max_ending_here + nums[i], nums[i]);
        max_so_far = std::max(max_so_far, max_ending_here);
      }

      return max_so_far;
    };

    // find the maximum subarray sum using Kadane's algorithm
    int max_kadane = kadane(nums);

    // In a circular array, a subarray that spans the ends is divided into two
    // segments: one at the beginning and the other at the end of the array. By
    // rethinking the problem, excluding the minimum subarray (a contiguous
    // subarray with the smallest sum) leaves the remaining elements to form the
    // maximum sum subarray that spans the ends.
    //
    // [NOTE] A key point to understand is that among all subarrays that span
    // the ends, one includes all elements of the original array. The maximum
    // sum for this subarray is simply the total sum of the array, which is
    // already covered by the standard Kadane's algorithm for non-circular
    // arrays. Thus, there is no need to separately consider subarrays including
    // all elements when using the formula:
    //
    // max_circular_subarray_sum = total_sum - min_subarray_sum

    // find the total sum of the array
    int total_sum = std::accumulate(nums.cbegin(), nums.cend(), 0);
    // invert the sign of all elements in the array to use Kadane's algorithm
    // for finding the minimum subarray sum
    vector<int> inverted_num(nums.size());
    std::transform(nums.cbegin(), nums.cend(), inverted_num.begin(), std::negate<>{});
    // find the minimum subarray sum using Kadane's algorithm on the inverted
    // array
    // [NOTE] min_subarray_sum = -max_inverted_kadane
    int max_inverted_kadane = kadane(inverted_num);
    // compute the maximum subarray sum for the circular case
    // [NOTE] max_circular = total_sum - min_subarray_sum
    //                     = total_sum + max_inverted_kadane
    int max_circular = total_sum + max_inverted_kadane;
    // It is important to note that if all elements in the array are negative,
    // subtracting the minimum subarray sum from the total array sum would
    // result in an empty subarray (i.e., a sum of 0). In this scenario, the
    // result should directly return the maximum subarray sum found using the
    // standard Kadane's algorithm.
    if (max_circular == 0) {
      return max_kadane;
    }

    // return the maximum of the non-circular and circular subarray sums
    return std::max(max_kadane, max_circular);
  }

  // Time complexity: O(n)
  int max_subarray_sum_circular_v4(vector<int> const& nums) {
    if (nums.empty()) {
      return 0;
    }

    int total = 0;
    int max_sum = nums[0]; // maximum subarray sum for non-circular case
    int curr_max = 0;      // current maximum subarray sum
    int min_sum = nums[0]; // minimum subarray sum for circular case
    int curr_min = 0;      // current minimum subarray sum

    for (int num : nums) {
      // update the current and maximum subarray sums using Kadane's algorithm
      curr_max = std::max(curr_max + num, num);
      max_sum = std::max(max_sum, curr_max);

      curr_min = std::min(curr_min + num, num);
      min_sum = std::min(min_sum, curr_min);

      total += num;
    }

    // if all numbers are negative, `max_sum` is the result
    if (max_sum < 0) {
      return max_sum;
    }

    // return the maximum of non-circular and circular subarray sums
    return std::max(max_sum, total - min_sum);
  }

  int max_subarray_sum_circular_v5(vector<int> const& nums) {
    if (nums.empty()) {
      return 0;
    }
  }
};

// using monotonic increasing deque
//
// https://leetcode.com/tag/monotonic-queue/
// https://leetcode.com/tag/prefix-sum/
//
// Time complexity: O(n)
class Solution_2 {
public:
  int maxSubarraySumCircular(vector<int>& nums) {
    if (nums.empty()) {
      return 0;
    }

    int n = nums.size();

    // Compute the prefix sum array
    //
    // `prefix[i]` represents the sum of the first `i` elements of the circular
    // array
    vector<int> prefix(n * 2 + 1, 0);
    for (int i = 1; i <= n * 2; ++i) {
      prefix[i] = prefix[i - 1] + nums[(i - 1) % n];
    }

    int max_sum = std::numeric_limits<int>::min();
    deque<int> dq{};

    // Use the sliding window technique on the prefix sum array
    for (int i = 0; i <= n * 2; ++i) {
      // Ensure the window size is at most n
      //
      //   prefix[i] - prefix[i - n]
      // = (nums[0] + ... + nums[i - n] + nums[i - n + 1] + ... nums[i])
      //   - (nums[0] + ... + nums[i - n])
      // = nums[i - n + 1] + ... nums[i]
      //
      // subarray length: i - (i - n + 1) + 1 = n
      //
      // Note: `if (!dq.empty() && dq.front() == i - n - 1)` is OK
      if (!dq.empty() && dq.front() < i - n) {
        dq.pop_front();
      }

      // Update the maximum subarray sum
      if (!dq.empty()) {
        max_sum = std::max(max_sum, prefix[i] - prefix[dq.front()]);
      }

      // Maintain a monotonic increasing deque
      while (!dq.empty() && prefix[i] < prefix[dq.back()]) {
        dq.pop_back();
      }

      dq.emplace_back(i);
    }

    return max_sum;
  }
};
