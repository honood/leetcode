// HoNooD <honood@gmail.com>
// 2024.06.10 14:05

// 128. Longest Consecutive Sequence
// https://leetcode.com/problems/longest-consecutive-sequence/description/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Sorting_algorithm

// Note: You must write an algorithm that runs in `O(n)` time.

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// O(n)
class Solution {
public:
  int longestConsecutive(vector<int>& nums) {
    int n = nums.size();
    if (n < 2) {
      return n;
    }

    int longestStreak = 1;
    unordered_set<int> uniqueNums(nums.cbegin(), nums.cend());
    for (auto const& num : uniqueNums) {
      // Skip numbers that are not the start of a sequence
      if (num != std::numeric_limits<int>::min() && uniqueNums.contains(num - 1)) {
        continue;
      }

      // `num` is the start of a sequence
      int currNum = num;
      int currStreak = 1;
      while (uniqueNums.contains(currNum + 1)) {
        currStreak += 1;
        currNum = currNum + 1;
      }

      longestStreak = std::max(longestStreak, currStreak);
    }

    return longestStreak;
  }
};

// O(nlogn)
class Solution_2 {
public:
  int longestConsecutive(vector<int>& nums) {
    int n = nums.size();
    if (n < 2) {
      return n;
    }

    std::sort(nums.begin(), nums.end());

    int longestStreak = 1;
    int currStreak = 1;
    for (int i = 0; i < n - 1; ++i) {
      if (nums[i] == nums[i + 1]) {
        continue;
      }

      if (nums[i] + 1 == nums[i + 1]) {
        ++currStreak;
      } else {
        longestStreak = std::max(longestStreak, currStreak);
        currStreak = 1;
      }
    }

    return std::max(longestStreak, currStreak);;
  }
};
