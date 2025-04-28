// HoNooD <honood@gmail.com>
// 2025.04.29 01:00
//
// 454. 4Sum II
// https://leetcode.com/problems/4sum-ii/description/

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  // clang-format off
  //
  // Constraints: -2^28 <= nums1[i], nums2[i], nums3[i], nums4[i] <= 2^28
  //
  // Note:
  // 1. std::numeric_limits<int>::max() = INT_MAX =  2^31 - 1
  // 2. std::numeric_limits<int>::min() = INT_MIN = -2^31
  // 3. INT_MIN < -2^30 = (-2^28) * 4 <= nums1[i] + nums2[i] + nums3[i] + nums4[i] <= 2^28 * 4 = 2^30 < INT_MAX
  //
  // clang-format on
  int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3,
                   vector<int>& nums4) {
    return four_sum_count_v2(nums1, nums2, nums3, nums4);
  }

private:
  // Time Limit Exceeded!
  //
  // - Time complexity: O(n^4)
  // - Space complexity: O(1)
  int four_sum_count_v1(vector<int>& nums1, vector<int>& nums2,
                        vector<int>& nums3, vector<int>& nums4) {
    int n = nums1.size();
    if (nums2.size() != n || nums3.size() != n || nums4.size() != n) {
      throw std::invalid_argument(
        "nums1, nums2, nums3 and nums4 must have the same number of elements");
    }

    int result = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        for (int k = 0; k < n; ++k) {
          for (int l = 0; l < n; ++l) {
            if (nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0) {
              ++result;
            }
          }
        }
      }
    }
    return result;
  }

  // - Time complexity: O(n^2)
  // - Space complexity: O(n^2)
  int four_sum_count_v2(vector<int>& nums1, vector<int>& nums2,
                        vector<int>& nums3, vector<int>& nums4) {
    int n = nums1.size();
    if (nums2.size() != n || nums3.size() != n || nums4.size() != n) {
      throw std::invalid_argument(
        "nums1, nums2, nums3 and nums4 must have the same number of elements");
    }

    unordered_map<int, int> sum_freq{};
    for (int num1 : nums1) {
      for (int num2 : nums2) {
        ++sum_freq[num1 + num2];
      }
    }

    int result = 0;
    for (int num3 : nums3) {
      for (int num4 : nums4) {
        int target = -(num3 + num4);
        if (sum_freq.contains(target)) {
          result += sum_freq[target];
        }
      }
    }
    return result;
  }
};
