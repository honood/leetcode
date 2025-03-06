// HoNooD <honood@gmail.com>
// 2024.08.05 09:50

// 88. Merge Sorted Array
// https://leetcode.com/problems/merge-sorted-array/?envType=study-plan-v2&envId=top-interview-150

// Follow up: Can you come up with an algorithm that runs in `O(m + n)` time?

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  // - Time complexity: O(m + n)
  // - Space complexity: O(1)
  void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    assert(nums2.size() == n && nums1.size() == m + n);
    if (n <= 0) {
      return;
    }

    nums1.resize(m + n);
    int i = m - 1;
    int j = n - 1;
    int k = m + n - 1;
    while (i >= 0 && j >= 0) {
      if (nums1[i] > nums2[j]) {
        nums1[k--] =  nums1[i--];
      } else {
        nums1[k--] =  nums2[j--];
      }
    }

    while (j >= 0) {
      nums1[k--] = nums2[j--];
    }
  }
};
