// HoNooD
// 2022.06.05 00:36

// https://leetcode.com/problems/median-of-two-sorted-arrays/

// [NOTE] 下面的算法时间复杂度是 O(m+n), 不符合题目要求。
// 
// 参考视频：
// 1. https://www.youtube.com/watch?v=q6IEA26hvXc 
// 2. https://www.youtube.com/watch?v=LPFhl65R7ww
// 
class Solution {
public:
  double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
    std::vector<int> merged_nums{};

    std::vector<int>::const_iterator nums1_it = nums1.cbegin();
    std::vector<int>::const_iterator nums2_it = nums2.cbegin();
    while (nums1_it != nums1.cend() && nums2_it != nums2.cend()) {
      if (*nums1_it <= *nums2_it) {
        merged_nums.push_back(*nums1_it);
        ++nums1_it;
      } else {
        merged_nums.push_back(*nums2_it);
        ++nums2_it;
      }
    }

    while (nums1_it != nums1.cend()) {
      merged_nums.push_back(*nums1_it++);
    }

    while (nums2_it != nums2.cend()) {
      merged_nums.push_back(*nums2_it++);
    }

    int size = merged_nums.size();
    if (0 == (size & 0x1)) {
      return (merged_nums[size / 2] + merged_nums[size / 2 - 1]) / 2.0;
    } else {
      return merged_nums[size / 2];
    }
  }
};
