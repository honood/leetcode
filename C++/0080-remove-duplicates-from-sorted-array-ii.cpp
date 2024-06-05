// HoNooD
// 2024.06.05 10:38

// 80. Remove Duplicates from Sorted Array II
// https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  int removeDuplicates(vector<int>& nums) {
    int n = nums.size();
    if (n <= 2) {
      return n;
    }

    int overwrite = 2;
    for (int i = 2; i < n; ++i) {
      if (nums[i] != nums[overwrite - 2]) {
        if (overwrite != i) {
          nums[overwrite] = nums[i];
        }
        ++overwrite;
      }
    }

    return overwrite;
  }
};
