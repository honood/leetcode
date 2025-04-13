// HoNooD <honood@gmail.com>
// 2024.07.04 23:18

// 300. Longest Increasing Subsequence
// https://leetcode.com/problems/longest-increasing-subsequence/description/?envType=study-plan-v2&envId=top-interview-150

// Longest increasing subsequence
// https://en.wikipedia.org/wiki/Longest_increasing_subsequence

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

// Dynamic Programming Approach
//
// 1.	Define the State:
//   - Let `dp[i]` represent the length of the longest increasing subsequence
//     that ends with the element at index `i`.
//
// 2. Initial State:
//   - Initialize each `dp[i]` to `1`, because the minimum length of LIS ending
//     at any element is `1` (the element itself).
//
// 3. State Transition:
//   - For each element `nums[i]`, check all previous elements `nums[j]` where
//     `j < i`. If `nums[i]` is greater than `nums[j]`, then `nums[i]` can
//     extend the increasing subsequence ending at `nums[j]`.
//   - Update `dp[i]` as `dp[i] = max(dp[i], dp[j] + 1)`. This formula updates
//     `dp[i]` to the maximum length by either:
//     - Keeping the current value of `dp[i]` (no extension), or
//     - Extending the subsequence ending at `nums[j]` by including `nums[i]`.
//
// 4.	Result:
//   - The length of the longest increasing subsequence in the array will be the
//     maximum value in the `dp` array, i.e., max(dp).
//
// Note: time complexity: O(n^2)
class Solution {
public:
  int lengthOfLIS(vector<int>& nums) {
    if (nums.empty()) {
      return 0;
    }

    // DP array to store the length of LIS ending at each index
    vector<int> dp(nums.size(), 1);

    int max_len = 1;
    for (int i = 1; i < nums.size(); ++i) {
      // check all previous elements
      for (int j = 0; j < i; ++j) {
        if (nums[i] > nums[j]) {
          dp[i] = std::max(dp[i], dp[j] + 1);
        }
      }

      max_len = std::max(max_len, dp[i]);
    }

    return max_len;
  }
};

// The approach uses a combination of dynamic programming and binary search. It
// maintains a list `lis` where `lis[i]` represents the smallest ending value of
// an increasing subsequence of length `i+1`. For each element in the input
// array, binary search is used to determine its position in the `lis` list.
//
// Note: time complexity: O(n*log(n))
class Solution_2 {
public:
  int lengthOfLIS(vector<int>& nums) {
    // store the increasing subsequence
    vector<int> lis{};

    for (int const& num : nums) {
      // perform binary search to find the position to insert the current number
      auto it = std::lower_bound(lis.begin(), lis.end(), num);

      // if `num` is larger than all elements in `lis`, it should be appended
      if (it == lis.end()) {
        lis.emplace_back(num);
      } else {
        // otherwise, replace the element at the position found
        *it = num;
      }
    }

    return lis.size();
  }

  // Example 1: nums = [10, 9, 2, 5, 3, 7, 101, 18]
  // i   nums[i]   lis
  // ------------------------------
  // 0   10        [10]
  // 1   9         [9]
  // 2   2         [2]
  // 3   5         [2, 5]
  // 4   3         [2, 3]
  // 5   7         [2, 3, 7]
  // 6   101       [2, 3, 7, 101]
  // 7   18        [2, 3, 7, 18]
  //
  // Example 2: nums = [0, 1, 0, 3, 2, 3]
  // i   nums[i]   lis
  // ------------------------------
  // 0   0         [0]
  // 1   1         [0, 1]
  // 2   0         [0, 1]
  // 3   3         [0, 1, 3]
  // 4   2         [0, 1, 2]
  // 5   3         [0, 1, 2, 3]
  int length_of_lis_debug(const vector<int>& nums) {
    vector<int> lis{};

    cout << left << setw(10) << "i" << setw(10) << "nums[i]" << "lis" << endl;
    cout << string(40, '-') << endl;

    for (int i = 0; i < nums.size(); ++i) {
      int num = nums[i];
      auto it = lower_bound(lis.begin(), lis.end(), num);
      if (it == lis.end()) {
        lis.push_back(num);
      } else {
        *it = num;
      }

      cout << left << setw(10) << i << setw(10) << num;
      cout << "[";
      for (size_t j = 0; j < lis.size(); ++j) {
        if (j > 0) { cout << ", "; }
        cout << lis[j];
      }
      cout << "]" << endl;
    }
    cout << endl;

    return lis.size();
  }
};
