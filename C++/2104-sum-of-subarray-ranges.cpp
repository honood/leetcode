// HoNooD <honood@gmail.com>
// 2024.07.17 11:11

// 2104. Sum of Subarray Ranges
// https://leetcode.com/problems/sum-of-subarray-ranges/description/

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  long long subArrayRanges(vector<int>& nums) {
    return subarray_ranges_v5(nums);
  }

private:
  // Brute Force
  //
  // Time complexity: O(n^3)
  //
  // Note: result in Time Limit Exceeded (TLE)
  long long subarray_ranges_v1(vector<int> const& nums) {
    int n = nums.size();
    if (n <= 1) {
      return 0;
    }

    long long res = 0;
    for (int subarr_sz = 2; subarr_sz <= n; ++subarr_sz) {
      for (int start = 0; start <= n - subarr_sz; ++start) {
        auto first = std::next(nums.cbegin(), start);
        auto last = std::next(nums.cbegin(), start + subarr_sz);
        auto minmax = std::minmax_element(first, last);
        res += *minmax.second - *minmax.first;
      }
    }

    return res;
  }

  // Brute Force
  //
  // Time complexity: O(n^2)
  //     sum_{start=0}^{n-1} (n - start - 1)
  //   = sum_{start=0}^{n-1} (n - 1 - start)
  //   = sum_{start=0}^{n-1} (n - 1) - sum_{start=0}^{n-1} start
  //   = n(n-1) - (0 + 1 + 2 + ... + (n-1))
  //   = n(n-1) - (n(n-1))/2
  //   = (1/2)(n^2 - n)
  long long subarray_ranges_v2(vector<int> const& nums) {
    int n = nums.size();
    if (n <= 1) {
      return 0;
    }

    long long res = 0;

    // for (int start = 0; start < n; ++start) {
    //   int min = nums[start];
    //   int max = nums[start];
    //   // Note:
    //   // 1. `offset` indicates the relative position of the last element in the
    //   //    subarray starting from `start`.
    //   // 2. This loop calculates the range `(max - min)` for all possible
    //   //    subarrays of length greater than 1 starting from `start` and adds it
    //   //    to the result.
    //   for (int offset = 1; start + offset < n; ++offset) {
    //     min = std::min(min, nums[start + offset]);
    //     max = std::max(max, nums[start + offset]);
    //     res += max - min;
    //   }
    // }

    for (int i = 0; i < n; ++i) {
      int min = nums[i];
      int max = nums[i];
      // explore all subarrays where the element at `i` is the first element and
      // the element at `j` is the last element
      for (int j = i + 1; j < n; ++j) {
        min = std::min(min, nums[j]);
        max = std::max(max, nums[j]);
        res += max - min;
      }
    }

    return res;
  }

  // using monotonic stack
  // https://leetcode.com/tag/monotonic-stack/
  //
  // The main idea is to use a monotonic stack to efficiently calculate the sum
  // of contributions of each element as the maximum and minimum of all
  // subarrays in which they appear.
  //
  // Time complexity: O(n)
  long long subarray_ranges_v3(vector<int> const& nums) {
    int n = nums.size();
    if (n <= 1) {
      return 0;
    }

    return sum_of_subarray_maxs(nums) - sum_of_subarray_mins(nums);
  }

  long long sum_of_subarray_maxs(vector<int> const& nums) {
    int n = nums.size();
    vector<int> left_first_greater(n);
    vector<int> right_first_greater_or_equal(n);

    stack<int> stack{};

    // stack is used as a STRICT monotonic decreasing stack
    for (int i = 0; i < n; ++i) {
      while (!stack.empty() && nums[i] >= nums[stack.top()]) {
        stack.pop();
      }
      left_first_greater[i] = stack.empty() ? -1 : stack.top();

      stack.emplace(i);
    }

    while (!stack.empty()) {
      stack.pop();
    }

    // stack is used as a monotonic decreasing stack
    for (int i = n - 1; i >= 0; --i) {
      while (!stack.empty() && nums[i] > nums[stack.top()]) {
        stack.pop();
      }
      right_first_greater_or_equal[i] = stack.empty() ? n : stack.top();

      stack.emplace(i);
    }

    long long res = 0;
    for (int i = 0; i < n; ++i) {
      // Assume:
      // i = 5, left_first_greater[i] = 2, right_first_greater_or_equal[i] = 8
      //
      // Then:
      //   (i - left_first_greater[i]) * (right_first_greater_or_equal[i] - i)
      // = (5 - 2) * (8 - 5)
      // = 3 * 3
      // = 9
      //
      // - Possible left boundaries (inclusive) for subarrays with `nums[i]` as
      //   the maximum: indices 3, 4, 5
      // - Possible right boundaries (inclusive) for subarrays with `nums[i]` as
      //   the maximum: indices 5, 6, 7
      // - Total number of subarrays where `nums[i]` is the maximum: 9, these
      //   subarrays are:
      //     [3, 5], [3, 6], [3, 7],
      //     [4, 5], [4, 6], [4, 7],
      //     [5, 5], [5, 6], [5, 7]
      res += static_cast<long long>(nums[i])
             * (i - left_first_greater[i]) // number of possible left boundaries
                                           // (inclusive) for subarrays with
                                           // `nums[i]` as the maximum
             * (right_first_greater_or_equal[i] - i); // number of possible right
                                                      // boundaries (inclusive)
                                                      // for subarrays with
                                                      // `nums[i]` as the maximum
    }
    return res;
  }

  long long sum_of_subarray_mins(vector<int> const& nums) {
    int n = nums.size();
    vector<int> left_first_smaller(n);
    vector<int> right_first_smaller_or_equal(n);

    stack<int> stack{};

    // stack is used as a STRICT monotonic increasing stack
    for (int i = 0; i < n; ++i) {
      while (!stack.empty() && nums[i] <= nums[stack.top()]) {
        stack.pop();
      }
      left_first_smaller[i] = stack.empty() ? -1 : stack.top();

      stack.emplace(i);
    }

    while (!stack.empty()) {
      stack.pop();
    }

    // stack is used as a monotonic increasing stack
    for (int i = n - 1; i >= 0; --i) {
      while (!stack.empty() && nums[i] < nums[stack.top()]) {
        stack.pop();
      }
      right_first_smaller_or_equal[i] = stack.empty() ? n : stack.top();

      stack.emplace(i);
    }

    long long res = 0;
    for (int i = 0; i < n; ++i) {
      res += static_cast<long long>(nums[i])
             * (i - left_first_smaller[i]) // number of possible left boundaries
                                           // (inclusive) for subarrays with
                                           // `nums[i]` as the minimum
             * (right_first_smaller_or_equal[i] - i); // number of possible right
                                                      // boundaries (inclusive)
                                                      // for subarrays with
                                                      // `nums[i]` as the minimum
    }
    return res;
  }

  // using monotonic stack
  // https://leetcode.com/tag/monotonic-stack/
  //
  // The main idea is to use a monotonic stack to efficiently calculate the sum
  // of contributions of each element as the maximum and minimum of all
  // subarrays in which they appear.
  //
  // Time complexity: O(n)
  long long subarray_ranges_v4(vector<int> const& nums) {
    int n = nums.size();
    if (n <= 1) {
      return 0;
    }

    long long res = 0;
    stack<int> stack{};

    for (int i = 0; i <= n; ++i) {
      // [NOTE]
      // 1. Constraints: `-10^9 <= nums[i]`
      // 2. `std::numeric_limits<int>::min() < -10^9`
      int curr_num = i == n ? std::numeric_limits<int>::min() : nums[i];
      while (!stack.empty() && curr_num < nums[stack.top()] ) {
        int idx = stack.top();
        int right_first_smaller_of_idx = i;
        stack.pop();

        int left_first_smaller_or_equal_of_idx = stack.empty() ? -1 : stack.top();
        res -= static_cast<long long>(nums[idx])
               * (idx - left_first_smaller_or_equal_of_idx)
               * (right_first_smaller_of_idx - idx);
      }

      stack.emplace(i);
    }

    while (!stack.empty()) {
      stack.pop();
    }

    for (int i = 0; i <= n; ++i) {
      // [NOTE]
      // 1. Constraints: `nums[i] <= 10^9`
      // 2. `std::numeric_limits<int>::max() > 10^9`
      int curr_num = i == n ? std::numeric_limits<int>::max() : nums[i];
      while (!stack.empty() && curr_num > nums[stack.top()]) {
        int idx = stack.top();
        int right_first_greater_of_idx = i;
        stack.pop();

        int left_first_greater_or_equal_of_idx = stack.empty() ? -1 : stack.top();
        res += static_cast<long long>(nums[idx])
               * (idx - left_first_greater_or_equal_of_idx)
               * (right_first_greater_of_idx - idx);
      }

      stack.emplace(i);
    }

    return res;
  }

  // using monotonic stack
  // https://leetcode.com/tag/monotonic-stack/
  //
  // The main idea is to use a monotonic stack to efficiently calculate the sum
  // of contributions of each element as the maximum and minimum of all
  // subarrays in which they appear.
  //
  // Time complexity: O(n)
  long long subarray_ranges_v5(vector<int> const& nums) {
    int n = nums.size();
    if (n <= 1) {
      return 0;
    }

    vector<int> right_first_smaller(n, n);
    vector<int> left_first_smaller_or_equal(n);
    stack<int> inc_stack{};
    for (int i = 0; i < n; ++i) {
      while (!inc_stack.empty() && nums[i] < nums[inc_stack.top()]) {
        right_first_smaller[inc_stack.top()] = i;
        inc_stack.pop();
      }
      left_first_smaller_or_equal[i] = inc_stack.empty() ? -1 : inc_stack.top();

      inc_stack.emplace(i);
    }

    vector<int> right_first_greater(n, n);
    vector<int> left_first_greater_or_equal(n);
    stack<int> dec_stack{};
    for (int i = 0; i < n; ++i) {
      while (!dec_stack.empty() && nums[i] > nums[dec_stack.top()]) {
        right_first_greater[dec_stack.top()] = i;
        dec_stack.pop();
      }
      left_first_greater_or_equal[i] = dec_stack.empty() ? -1 : dec_stack.top();

      dec_stack.emplace(i);
    }

    long long res = 0;
    for (int i = 0; i < n; ++i) {
      res += static_cast<long long>(nums[i])
             * ((i - left_first_greater_or_equal[i]) * (right_first_greater[i] - i)
                - (i - left_first_smaller_or_equal[i]) * (right_first_smaller[i] - i));
    }
    return res;
  }
};
