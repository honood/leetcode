// HoNooD
// 2024.05.30 15:26

// 268. Missing Number
// https://leetcode.com/problems/missing-number/description/

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// Best
class Solution {
public:
  int missingNumber(vector<int>& nums) {
    assert(!nums.empty());

    int xorSum = 0;
    for (int i = 0; i <= nums.size(); ++i) {
      xorSum ^= i;
    }

    for (auto const& num : nums) {
      xorSum ^= num;
    }

    return xorSum;
  }
};

class Solution_2 {
public:
  int missingNumber(vector<int>& nums) {
    assert(!nums.empty());

    int sum = (1 + nums.size()) * nums.size() / 2;
    for (auto const& num : nums) {
      sum -= num;
    }

    return sum;
  }
};
