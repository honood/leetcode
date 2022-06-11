// HoNooD
// 2022.06.12 00:50

// https://leetcode.cn/problems/permutations/

// 参考：
// 1. https://github.com/labuladong/fucking-algorithm/blob/master/%E7%AE%97%E6%B3%95%E6%80%9D%E7%BB%B4%E7%B3%BB%E5%88%97/%E5%9B%9E%E6%BA%AF%E7%AE%97%E6%B3%95%E8%AF%A6%E8%A7%A3%E4%BF%AE%E8%AE%A2%E7%89%88.md
// 2. https://flamsteed.github.io/2020/03/27/LeetCode-%E6%8E%92%E5%88%97%E7%BB%84%E5%90%88%E7%B3%BB%E5%88%97%E6%95%B4%E7%90%86-2020/#46-%E5%85%A8%E6%8E%92%E5%88%97
// 3. https://www.geeksforgeeks.org/write-a-c-program-to-print-all-permutations-of-a-given-string/
//    https://www.techiedelight.com/find-permutations-given-string/
//    https://www.interviewbit.com/blog/permutations-of-the-given-string/
// 4. https://www.geeksforgeeks.org/print-all-permutations-with-repetition-of-characters/
// 5. https://segmentfault.com/a/1190000040401426

#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
  vector<vector<int>> permute(vector<int> const& nums) {
    result.clear();
    if (nums.empty()) {
      return result;
    }

    vector<int> track{};
    vector<bool> tracked(nums.size(), false);
    backtrack(nums, tracked, track);

    return result;
  }

  void backtrack(vector<int> const& nums, vector<bool>& tracked, vector<int>& track) {
    if (track.size() == nums.size()) {
      result.push_back(track);
      return;
    }

    for (int i = 0; i < nums.size(); ++i) {
      if (tracked[i]) {
        continue;
      }

      track.push_back(nums[i]);
      tracked[i] = true;

      backtrack(nums, tracked, track);

      track.pop_back();
      tracked[i] = false;
    }
  }

private:
  vector<vector<int>> result{};
};

int main(int argc, char* argv[]) {
  Solution s{};
  auto r = s.permute(std::vector{1, 2, 3});
  for (int i = 0; i < r.size(); ++i) {
    std::cout << "[" << i + 1 << "] ";
    for (auto const& e: r[i]) {
      std::cout << e << " ";
    }
    std::cout << '\n';
  }

  return 0;
}
