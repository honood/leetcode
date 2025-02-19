// HoNooD <honood@gmail.com>
// 2025.02.19 22:49

// 1431. Kids With the Greatest Number of Candies
// https://leetcode.com/problems/kids-with-the-greatest-number-of-candies/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  vector<bool> kidsWithCandies(vector<int>& candies, int extra_candies) {
    vector<bool> result(candies.size(), false);
    int max_candies = *std::max_element(candies.cbegin(), candies.cend());
    for (int i = 0; i < candies.size(); ++i) {
      result[i] = candies[i] + extra_candies >= max_candies;
    }
    return result;
  }
};
