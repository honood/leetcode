// HoNooD <honood@gmail.com>
// 2024.08.05 10:10

// 27. Remove Element
// https://leetcode.com/problems/remove-element/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  // - Time complexity: O(n)
  // - Space complexity: O(1)
  int removeElement(vector<int>& nums, int val) {
    int overwrite = 0;
    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] != val) {
        if (i != overwrite) {
          nums[overwrite] = nums[i];
        }
        ++overwrite;
      }
    }

    return overwrite;
  }
};
