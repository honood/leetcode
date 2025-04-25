// HoNooD <honood@gmail.com>
// 2025.04.24 14:44
//
// 16. 3Sum Closest
// https://leetcode.com/problems/3sum-closest/description/

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  // clang-format off
  //
  // Constraints:
  // 1. -1000 <= nums[i] <= 1000
  // 2. -10^4 <= target <= 10^4
  //
  // Note:
  // 1. std::numeric_limits<int>::max() = INT_MAX =  2'147'483'647
  // 2. std::numeric_limits<int>::min() = INT_MIN = -2'147'483'648
  // 3. INT_MIN < (-1000*3 - 10^4) <= nums[i] + nums[j] + nums[k] - target <= (1000*3 + 10^4 ) < INT_MAX
  //
  // clang-format on
  int threeSumClosest(vector<int>& nums, int target) {
    return three_sum_closest_v2(nums, target);
  }

private:
  // - Time complexity: O(n^3)
  // - Space complexity: O(1)
  int three_sum_closest_v1(vector<int>& nums, int target) {
    int n = nums.size();
    if (n < 3) {
      throw std::invalid_argument("nums must contain at least 3 elements");
    }

    int closest_sum = nums[0] + nums[1] + nums[2];
    if (closest_sum == target) {
      return target;
    }

    int min_diff = std::numeric_limits<int>::max();

    for (int i = 0; i < n - 2; ++i) {
      for (int j = i + 1; j < n - 1; ++j) {
        for (int k = j + 1; k < n; ++k) {
          int sum = nums[i] + nums[j] + nums[k];
          int diff = std::abs(sum - target);
          if (diff == 0) {
            return target;
          }

          if (diff < min_diff) {
            min_diff = diff;
            closest_sum = sum;
          }
        }
      }
    }

    return closest_sum;
  }

  // - Time complexity: O(n^2)
  // - Space complexity: O(log(n)) or O(n), depending on the specific sorting
  //   algorithm implementation used.
  int three_sum_closest_v2(vector<int>& nums, int target) {
    int n = nums.size();
    if (n < 3) {
      throw std::invalid_argument("nums must contain at least 3 elements");
    }

    std::sort(nums.begin(), nums.end());

    int min_diff = std::numeric_limits<int>::max();
    // Initializing closest_sum to 0 is acceptable because min_diff is max,
    // ensuring the first calculated sum will update closest_sum.
    // Initializing with nums[0]+nums[1]+nums[2] is also a valid alternative.
    int closest_sum = 0;

    for (int i = 0; i < n - 2; ++i) {
      if (int min_sum = nums[i] + nums[i + 1] + nums[i + 2]; min_sum > target) {
        return std::abs(min_sum - target) < min_diff ? min_sum : closest_sum;
      }

      if (i > 0 && nums[i] == nums[i - 1]) {
        continue;
      }

      if (int max_sum = nums[i] + nums[n - 2] + nums[n - 1]; max_sum < target) {
        if (int diff = std::abs(max_sum - target); diff < min_diff) {
          min_diff = diff;
          closest_sum = max_sum;
        }
        continue;
      }

      int left = i + 1;
      int right = n - 1;
      while (left < right) {
        int sum = nums[i] + nums[left] + nums[right];

        if (int diff = std::abs(sum - target); diff < min_diff) {
          min_diff = diff;
          closest_sum = sum;
        }

        if (sum == target) {
          return target;
        } else if (sum < target) {
          ++left;
          while (left < right && nums[left] == nums[left - 1]) {
            ++left;
          }
        } else {
          --right;
          while (left < right && nums[right] == nums[right + 1]) {
            --right;
          }
        }
      } // while
    } // for

    return closest_sum;
  }

  // - Time complexity: O(n^3)
  // - Space complexity: O(n)
  int three_sum_closest_v3(vector<int>& nums, int target) {
    int n = nums.size();
    if (n < 3) {
      throw std::invalid_argument("nums must contain at least 3 elements");
    }

    std::sort(nums.begin(), nums.end());

    int closest_sum = nums[0] + nums[1] + nums[2];

    for (int i = 0; i < n - 2; ++i) {
      if (i > 0 && nums[i] == nums[i - 1]) {
        continue;
      }

      unordered_set<int> seen{};
      for (int j = i + 1; j < n; ++j) {
        int complement = target - nums[i] - nums[j];

        if (!seen.empty()) {
          int closest = *seen.begin();
          for (int num : seen) {
            if (std::abs(num - complement) < std::abs(closest - complement)) {
              closest = num;
            }
          }

          int sum = nums[i] + nums[j] + closest;
          if (std::abs(sum - target) < std::abs(closest_sum - target)) {
            closest_sum = sum;
          }
        }

        seen.insert(nums[j]);
      }
    }

    return closest_sum;
  }
};
