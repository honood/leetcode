// HoNooD <honood@gmail.com>
// 2025.02.28 10:29

// 1207. Unique Number of Occurrences
// https://leetcode.com/problems/unique-number-of-occurrences/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  bool uniqueOccurrences(vector<int>& arr) {
    unordered_map<int, int> freq{};
    for (int val : arr) {
      ++freq[val];
    }

    unordered_set<int> occurrences{};
    for (auto const& [k, v] : freq) {
      if (occurrences.contains(v)) {
        return false;
      }
      occurrences.emplace(v);
    }

    return true;
  }
};
