// HoNooD <honood@gmail.com>
// 2024.06.10 13:41

// 217. Contains Duplicate
// https://leetcode.com/problems/contains-duplicate/description/

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  bool containsDuplicate(vector<int>& nums) {
    if (nums.size() < 2) {
      return false;
    }

    unordered_set<int> seen{};
    for (auto const& num : nums) {
      if (seen.contains(num)) {
        return true;
      }

      seen.emplace(num);
    }

    return false;
  }
};

class Solution_2 {
public:
  bool containsDuplicate(vector<int>& nums) {
    if (nums.size() < 2) {
      return false;
    }

    std::sort(nums.begin(), nums.end());

    for (int i = 1; i < nums.size(); ++i) {
      if (nums[i] == nums[i - 1]) {
        return true;
      }
    }

    return false;
  }
};
