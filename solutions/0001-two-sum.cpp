// HoNooD <honood@gmail.com>
// 2022.06.04 17:10
// 2025.04.23 20:50

// 1. Two Sum
// https://leetcode.com/problems/two-sum/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  vector<int> twoSum(vector<int>& nums, int target) {
    return two_sum_v3(nums, target);
  }

private:
  // - Time complexity: O(n^2)
  // - Space complexity: O(1)
  vector<int> two_sum_v1(vector<int> const& nums, int target) {
    int n = nums.size();
    if (n < 2) {
      return {};
    }

    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        if (nums[i] + nums[j] == target) {
          return {i, j};
        }
      }
    }

    return {};
  }

  // - Time complexity: O(n)
  // - Space complexity: O(n)
  vector<int> two_sum_v2(vector<int> const& nums, int target) {
    int n = nums.size();
    if (n < 2) {
      return {};
    }

    unordered_map<int, int> num_to_index{};
    for (int i = 0; i < n; ++i) {
      num_to_index.emplace(nums[i], i);
    }

    for (int i = 0; i < n; ++i) {
      int complement = target - nums[i];
      if (num_to_index.contains(complement) && num_to_index[complement] != i) {
        return {i, num_to_index[complement]};
      }
    }

    return {};
  }

  // - Time complexity: O(n)
  // - Space complexity: O(n)
  vector<int> two_sum_v3(vector<int> const& nums, int target) {
    int n = nums.size();
    if (n < 2) {
      return {};
    }

    unordered_map<int, int> num_to_index{};
    for (int i = 0; i < n; ++i) {
      int complement = target - nums[i];
      if (num_to_index.contains(complement)) {
        return {num_to_index[complement], i};
      }

      num_to_index.emplace(nums[i], i);
    }

    return {};
  }

  // - Time complexity: O(n * log(n))
  // - Space complexity: O(n)
  vector<int> two_sum_v4(vector<int> const& nums, int target) {
    int n = nums.size();
    if (n < 2) {
      return {};
    }

    vector<std::pair<int, int>> num_with_index{};
    num_with_index.reserve(n);
    for (int i = 0; i < n; ++i) {
      num_with_index.emplace_back(nums[i], i);
    }

    std::sort(
      num_with_index.begin(), num_with_index.end(),
      [](auto const& lhs, auto const& rhs) { return lhs.first < rhs.first; });

    int left = 0;
    int right = n - 1;
    while (left < right) {
      int sum = num_with_index[left].first + num_with_index[right].first;
      if (sum == target) {
        return {num_with_index[left].second, num_with_index[right].second};
      } else if (sum < target) {
        ++left;
      } else {
        --right;
      }
    }

    return {};
  }
};
