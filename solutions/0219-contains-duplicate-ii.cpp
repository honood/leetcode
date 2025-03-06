// HoNooD <honood@gmail.com>
// 2024.06.10 13:47

// 219. Contains Duplicate II
// https://leetcode.com/problems/contains-duplicate-ii/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  bool containsNearbyDuplicate(vector<int>& nums, int k) {
    if (k <= 0) {
      return false;
    }

    unordered_map<int, int> numToIndex{};
    for (int i = 0; i < nums.size(); ++i) {
      if (numToIndex.contains(nums[i]) && i - numToIndex[nums[i]] <= k) {
        return true;
      }

      numToIndex[nums[i]] = i;
    }

    return false;
  }
};
