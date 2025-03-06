// HoNooD <honood@gmail.com>
// 2025.02.29 10:09

// 2215. Find the Difference of Two Arrays
// https://leetcode.com/problems/find-the-difference-of-two-arrays/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  vector<vector<int>> findDifference(vector<int>& nums1, vector<int>& nums2) {
    unordered_set<int> set1{nums1.cbegin(), nums1.cend()};
    unordered_set<int> set2{nums2.cbegin(), nums2.cend()};

    vector<int> diff1{};
    for (int num : set1) {
      if (!set2.contains(num)) {
        diff1.push_back(num);
      }
    }

    vector<int> diff2{};
    for (int num : set2) {
      if (!set1.contains(num)) {
        diff2.push_back(num);
      }
    }

    return {diff1, diff2};
  }
};
