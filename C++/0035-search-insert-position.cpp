// HoNooD <honood@gmail.com>
// 2024.06.14 11:39

// 35. Search Insert Position
// https://leetcode.com/problems/search-insert-position/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  int searchInsert(vector<int>& nums, int target) {
    assert(!nums.empty());

    int low = 0;
    int high = nums.size() - 1;
    while (low <= high) {
      int mid = low + (high - low) / 2;
      if (nums[mid] == target) {
        return mid;
      }

      if (nums[mid] > target) {
        high = mid - 1;
      } else {
        low = mid + 1;
      }
    }

    return low;
  }
};
