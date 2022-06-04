// HoNooD
// 2022.06.04 17:10

// https://leetcode.com/problems/two-sum/

class Solution {
public:
  vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> m{};

    for (int i = 0; i < nums.size(); ++i) {
      int left = nums[i];
      int right = target - left;
      if (m.find(right) != m.end()) {
        return {m[right], i};
      } 

      m[left] = i;
    }

    return {-1, -1};
  }
};
