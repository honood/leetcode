// HoNooD <honood@gmail.com>
// 2024.06.15 17:12

// 4. Median of Two Sorted Arrays
// https://leetcode.com/problems/median-of-two-sorted-arrays/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Median
// https://en.wikipedia.org/wiki/Quartile
// https://en.wikipedia.org/wiki/Decile
// https://en.wikipedia.org/wiki/Percentile

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// To achieve a time complexity of O(log(m+n)), we cannot directly merge and
// sort the arrays. Instead, we use a binary search approach for optimization.
//
// We need to partition the arrays such that:
// 1. Elements in the left partition are less than or equal to elements in the
// right partition.
// 2. The left and right partitions have nearly equal lengths.
//
// Let's partition `nums1` at index `i` and `nums2` at index `j`. `i + j` should
// be such that the left partition and the right partition lengths are balanced:
// 1. If `m + n` is even: `i + j = (m + n) / 2`
// 2. If `m + n` is odd: `i + j = (m + n + 1) / 2`
//
// Adjust the partition to:
// 1. ensure `nums1[i - 1] <= nums2[j]` and `nums2[j - 1] <= nums1[i]`.
// 2. if `nums1[i - 1] > nums2[j]`, decrease `i` (move partition left).
// 3. if `nums2[j - 1] > nums1[i]`, increase `i` (move partition right).
//
// Once correct `i` and `j` are found, compute the median:
// 1. If `m + n` is odd, the median is the maximum of the left partition. i.e.:
// `max(nums1[i - 1], nums2[j - 1])`
// 2. If `m + n` is even, the median is the average of the maximum of the left
// partition and the minimum of the right partition. i.e.:
// `(max(nums1[i - 1], nums2[j - 1]) + min(nums1[i], nums2[j])) / 2`
//
// time complexity: O(log(min(m, n)))
class Solution {
public:
  double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int m = nums1.size();
    int n = nums2.size();
    // ensure `nums1` is the smaller or equal sized array
    if (m > n) {
      return findMedianSortedArrays(nums2, nums1);
    }

    int left = 0;
    int right = m;
    int half_total_len = (m + n + 1) / 2;
    while (left <= right) {
      int i = left + (right - left) / 2;
      int j = half_total_len - i;

      // check boundary conditions
      int nums1_left_max  = i == 0 ? std::numeric_limits<int>::min() : nums1[i - 1];
      int nums1_right_min = i == m ? std::numeric_limits<int>::max() : nums1[i];
      int nums2_left_max  = j == 0 ? std::numeric_limits<int>::min() : nums2[j - 1];
      int nums2_right_min = j == n ? std::numeric_limits<int>::max() : nums2[j];

      // binary search to adjust `i`
      if (nums1_left_max > nums2_right_min) {
        // `i` is to large, decrease it
        right = i - 1;
      } else if (nums1_right_min < nums2_left_max) {
        // `i` is to small, increase it
        left = i + 1;
      } else {
        // `i` is perfectly positioned as both conditions are met:
        // 1. `nums1_left_max <= nums2_right_min`
        // 2. `nums2_left_max <= nums1_right_min`
        //
        // calculate the median
        if ((m + n) % 2 == 1) {
          // Note: if `half_total_len` is defined as `(m + n) / 2` (i.e., without
          // the `+1` adjustment), the correct return value for odd total length
          // would be: `std::min(nums1_right_min, nums2_right_min)`
          return std::max(nums1_left_max, nums2_left_max);
        } else {
          return (std::max(nums1_left_max, nums2_left_max) + std::min(nums1_right_min, nums2_right_min)) / 2.0;
        }
      }
    }

    // control should never reach here
    assert(false);
    return 0.0;
  }
};

// time complexity: O(log(min(m, n)))
class Solution_2 {
public:
  double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int m = nums1.size();
    int n = nums2.size();
    // ensure `nums1` is the smaller or equal sized array
    if (m > n) {
      return findMedianSortedArrays(nums2, nums1);
    }

    int left = 0;
    int right = m;
    int half_total_len = (m + n + 1) / 2;
    while (left < right) {
      int i = left + (right - left) / 2;
      int j = half_total_len - i;

      if (nums1[i] < nums2[j - 1]) {
        // `i` is to small, increase it
        left = i + 1;
      } else {
        // when `nums1[i] >= nums2[j - 1]`, it means that `nums1[i]` is large
        // enough to be a candidate for the median. therefore, we narrow the
        // search by moving the right boundary to `i`, potentially INCLUDING `i`.
        right = i;
      }
    }

    assert(left == right);
    int i = left;
    int j = half_total_len - i;

    int nums1_left_max  = i == 0 ? std::numeric_limits<int>::min() : nums1[i - 1];
    int nums1_right_min = i == m ? std::numeric_limits<int>::max() : nums1[i];
    int nums2_left_max  = j == 0 ? std::numeric_limits<int>::min() : nums2[j - 1];
    int nums2_right_min = j == n ? std::numeric_limits<int>::max() : nums2[j];

    if ((m + n) % 2 == 1) {
      // Note: if `half_total_len` is defined as `(m + n) / 2` (i.e., without
      // the `+1` adjustment), the correct return value for odd total length
      // would be: `std::min(nums1_right_min, nums2_right_min)`
      return std::max(nums1_left_max, nums2_left_max);
    } else {
      return (std::max(nums1_left_max, nums2_left_max) + std::min(nums1_right_min, nums2_right_min)) / 2.0;
    }
  }
};
