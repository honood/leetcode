// HoNooD <honood@gmail.com>
// 2025.02.19 22:49

// 1431. Kids With the Greatest Number of Candies
// https://leetcode.com/problems/kids-with-the-greatest-number-of-candies/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  vector<bool> kidsWithCandies(vector<int>& candies, int extra_candies) {
    vector<int> left_max_candies(candies.size(), 0);
    for (int i = 1; i < candies.size(); ++i) {
      left_max_candies[i] = std::max(left_max_candies[i - 1], candies[i - 1]);
    }

    vector<int> right_max_candies(candies.size(), 0);
    for (int i = candies.size() - 2; i >= 0; --i) {
      right_max_candies[i] = std::max(right_max_candies[i + 1], candies[i + 1]);
    }

    vector<bool> result(candies.size(), false);
    for (int i = 0; i < candies.size(); ++i) {
      result[i] = candies[i] + extra_candies >= std::max(left_max_candies[i], right_max_candies[i]);
    }
    return result;
  }
};
