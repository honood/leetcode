// HoNooD <honood@gmail.com>
// 2024.06.14 15:45

// 162. Find Peak Element
// https://leetcode.com/problems/find-peak-element/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  int findPeakElement(vector<int>& nums) {
    assert(!nums.empty());

    int left = 0;
    int right = nums.size() - 1;
    while (left < right) {
      // Note: `mid` is always less than `right` due to `left < right`
      int mid = left + (right - left) / 2;
      if (nums[mid] > nums[mid + 1]) {
        // indicates that the peak is either on the left side of `mid` or is at
        // `mid` itself.
        right = mid;
      } else {
        // otherwise, the peak is on the right side of mid.
        // Note: `mid + 1` is always less than or equal to `right` as `mid < right`
        left = mid + 1;
      }
    }

    return left; // or return right;
  }
};
