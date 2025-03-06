// HoNooD
// 2024.06.05 09:31

// 26. Remove Duplicates from Sorted Array
// https://leetcode.com/problems/remove-duplicates-from-sorted-array/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  // - Time complexity: O(n)
  // - Space complexity: O(1)
  int removeDuplicates(vector<int>& nums) {
    int n = nums.size();
    if (n <= 1) {
      return n;
    }

    int overwrite = 1;
    for (int i = 1; i < n; ++i) {
      if (nums[i] != nums[overwrite - 1]) {
        if (overwrite != i) {
          nums[overwrite] = nums[i];
        }
        ++overwrite;
      }
    }

    return overwrite;
  }
};
