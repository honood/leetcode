// HoNooD
// 2024.05.30 22:45

// 287. Find the Duplicate Number
// https://leetcode.com/problems/find-the-duplicate-number/description/
//
// Note: You must solve the problem without modifying the array `nums` and uses 
// only constant extra space.

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  int findDuplicate(vector<int>& nums) {
    int low = 1;
    int high = nums.size() - 1; // n

    while (low < high) {
      int mid = (low + high) / 2;
      int count = 0;

      // Count how many numbers are less than or equal to mid
      for (int num : nums) {
        if (num <= mid) {
          ++count;
        }
      }

      // Adjust the binary search range
      if (count > mid) {
        high = mid;
      } else {
        low = mid + 1;
      }
    }

    return low;
  }
};
