// HoNooD <honood@gmail.com>
// 2024.06.15 15:21

// 153. Find Minimum in Rotated Sorted Array
// https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  int findMin(vector<int>& nums) {
    assert(!nums.empty());

    int left = 0;
    int right = nums.size() - 1;
    // narrow down the range to always include the smallest until one element remains
    while (left < right) {
      int mid = left + (right - left) / 2;
      if (nums[mid] < nums[right]) {
        // smallest is left of or at `mid` (e.g., [3, 5, 0, 1, 2])
        right = mid;
      } else {
        // smallest is in right half
        left = mid + 1;
      }
    }

    assert(left == right);
    return nums[left];
  }
};
