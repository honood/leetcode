// HoNooD <honood@gmail.com>
// 2024.07.13 23:56

// 456. 132 Pattern
// https://leetcode.com/problems/132-pattern/description/
//
// Given an array of `n` integers `nums`, a "132 pattern" is a subsequence of
// three integers `nums[i]`, `nums[j]` and `nums[k]` such that `i < j < k` and
// `nums[i] < nums[k] < nums[j]`. Return `true` if there is a "132 pattern" in
// `nums`, otherwise, return `false`.
//
// https://leetcode.com/tag/monotonic-stack/

// Monotonic Stack
//
// A monotonic stack is a stack data structure that maintains its elements in
// either an increasing or decreasing order. Here are its key properties:
//
// 1. Order Maintenance:
//   - In a Monotonic Increasing Stack, each new element pushed onto the stack
//     is greater than or equal to the element at the top of the stack.
//   - In a Monotonic Decreasing Stack, each new element pushed onto the stack
//     is less than or equal to the element at the top of the stack.
// 2. Efficiency:
//   - It allows for efficient retrieval of the next greater or next smaller
//     element in a sequence, typically in linear time `O(n)`.
// 3. Dynamic Updates:
//   - As elements are added or removed, the stack dynamically maintains its
//     monotonic property, ensuring that the operations of pushing and popping
//     elements are efficient.
// 4. Application:
//   - Monotonic stacks are commonly used in problems involving the next greater
//     element, next smaller element, stock span problems, and histogram
//     problems.

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  bool find132pattern(vector<int>& nums) {
    return find_132_pattern_v3(nums);
  }

private:
  // Brute Force
  //
  // Time complexity: O(n^3)
  //
  // Note: result in Time Limit Exceeded (TLE)
  bool find_132_pattern_v1(vector<int> const& nums) {
    int n = nums.size();
    if (n < 3) {
      return false;
    }

    for (int i = 0; i < n - 2; ++i) {
      for (int j = i + 1; j < n - 1; ++j) {
        for (int k = j + 1; k < n; ++k) {
          if (nums[i] < nums[k] && nums[k] < nums[j]) {
            return true;
          }
        }
      }
    }

    return false;
  }

  // Time complexity: O(n*log(n))
  bool find_132_pattern_v2(vector<int> const& nums) {
    int n = nums.size();
    if (n < 3) {
      return false;
    }

    // store the minimum values up to each index
    vector<int> min_vals(n);
    min_vals[0] = nums[0];
    for (int i = 1; i < n; ++i) {
      min_vals[i] = std::min(min_vals[i - 1], nums[i]);
    }

    // maintain potential third elements of the 132 pattern
    set<int> candidates{};

    // traverse from the end to the beginning
    for (int j = n - 1; j >= 0; --j) {
      // check if `nums[j]` can be the "2" in the 132 pattern
      //
      // Note: if `nums[j] > min_vals[j]`, `min_vals[j]` must be a value from
      // `nums[0]` to `nums[j - 1]`
      if (nums[j] > min_vals[j]) {
        // find the smallest element in `candidates` greater than `min_vals[j]`
        auto it = candidates.lower_bound(min_vals[j] + 1);
        // verify if there is a valid "3" that is less than `nums[j]`
        if (it != candidates.end() && *it < nums[j]) {
          return true;
        }

        // insert `nums[j]` into the set for future potential "3" elements
        candidates.emplace(nums[j]);
      }
    }

    return false;
  }

  bool find_132_pattern_v2_debug(vector<int> const& nums) {
    int n = nums.size();
    if (n < 3) {
      return false;
    }

    vector<pair<int, int>> min_vals{};
    min_vals.emplace_back(nums[0], 0);
    for (int i = 1; i < n; ++i) {
      if (nums[i] < min_vals[i - 1].first) {
        min_vals.emplace_back(nums[i], i);
      } else {
        min_vals.emplace_back(min_vals[i - 1]);
      }
    }

    auto less = [](pair<int, int> const& left, pair<int, int> const& right) {
      return left.first < right.first;
    };
    set<pair<int, int>, decltype(less)> candidates{less};
    for (int j = n - 1; j >= 0; --j) {
      if (nums[j] > min_vals[j].first) {
        auto it = candidates.lower_bound({min_vals[j].first + 1, -1});
        if (it != candidates.end() && it->first < nums[j]) {
          cout << "For nums: [";
          for (int i = 0; i < n; ++i) {
            if (i < n - 1) { cout << nums[i] << ", "; }
            else { cout << nums[i]; }
          }
          cout << std::format("]\nFind 132 pattern: {}(i) < {}(j) < {}(k) && {}(nums[i]) < {}(nums[k]) < {}(nums[j])",
                              min_vals[j].second, j, it->second, min_vals[j].first, it->first, nums[j])
               << '\n';
          return true;
        }

        candidates.emplace(nums[j], j);
      }
    }

    return false;
  }

  // using monotonic decreasing stack
  //
  // Time complexity: O(n)
  bool find_132_pattern_v3(vector<int> const& nums) {
    int n = nums.size();
    if (n < 3) {
      return false;
    }

    // initialize the third element in the 132 pattern
    int third = std::numeric_limits<int>::min();
    // keep track of the possible values of the third element
    stack<int> stack{};

    // traverse from the end to the beginning
    for (int i = n - 1; i >= 0; --i) {
      if (nums[i] < third) {
        return true;
      }

      // maintain the possible values for the third element
      while (!stack.empty() && nums[i] > stack.top()) {
        third = stack.top();
        stack.pop();
      }

      stack.emplace(nums[i]);
    }

    return false;
  }

  // test case:
  // - nums = {2, 3, 6, 3, 5, 1, 2, 7}
  //   2 █▉█▉
  //   3 █▉█▉█▉
  //   6 █▉█▉█▉█▉█▉█▉
  //   3 █▉█▉█▉
  //   5 █▉█▉█▉█▉█▉
  //   1 █▉
  //   2 █▉█▉
  //   7 █▉█▉█▉█▉█▉█▉█▉
  // - found: i = 1, j = 2, k = 4
  bool find_132_pattern_v3_debug(vector<int> const& nums) {
    int n = nums.size();
    if (n < 3) {
      return false;
    }

    pair<int, int> second{};
    pair<int, int> third{std::numeric_limits<int>::min(), -1};
    stack<pair<int, int>> stack{};

    for (int i = n - 1; i >= 0; --i) {
      if (nums[i] < third.first) {
        cout << "For nums: [";
        for (int j = 0; j < n; ++j) {
          if (j < n - 1) { cout << nums[j] << ", "; }
          else { cout << nums[j]; }
        }
        cout << std::format("]\nFind 132 pattern: {}(i) < {}(j) < {}(k) && {}(nums[i]) < {}(nums[k]) < {}(nums[j])",
                            i, second.second, third.second, nums[i], third.first, second.first)
             << '\n';
        return true;
      }

      while (!stack.empty() && nums[i] > stack.top().first) {
        second = {nums[i], i};
        third = stack.top();
        stack.pop();
      }

      stack.emplace(nums[i], i);
    }

    return false;
  }
};
