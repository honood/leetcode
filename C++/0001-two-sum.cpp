// HoNooD <honood@gmail.com>
// 2022.06.04 17:10

// 1. Two Sum
// https://leetcode.com/problems/two-sum/?envType=study-plan-v2&envId=top-interview-150

class Solution {
public:
  vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> numToIndex{};
    for (int i = 0; i < nums.size(); ++i) {
      int complement = target - nums[i];
      if (numToIndex.contains(complement)) {
        return {numToIndex[complement], i};
      }

      numToIndex[nums[i]] = i;
    }

    return {};
  }
};
