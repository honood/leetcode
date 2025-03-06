// HoNooD <honood@gmail.com>
// 2025.02.28 10:48

// 1657. Determine if Two Strings Are Close
// https://leetcode.com/problems/determine-if-two-strings-are-close/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  bool closeStrings(string word1, string word2) {
    return close_strings_v2(word1, word2);
  }

private:
  bool close_strings_v1(string const& word1, string const& word2) {
    if (word1.size() != word2.size()) {
      return false;
    }

    unordered_map<char, int> freq1{};
    unordered_set<char> keys1{};
    for (char c : word1) {
      ++freq1[c];
      keys1.emplace(c);
    }

    unordered_map<char, int> freq2{};
    unordered_set<char> keys2{};
    for (char c : word2) {
      ++freq2[c];
      keys2.emplace(c);
    }

    if (keys1 != keys2) {
      return false;
    }

    vector<int> value1{};
    for (auto const& [k, v] : freq1) {
      value1.push_back(v);
    }
    std::sort(value1.begin(), value1.end());

    vector<int> value2{};
    for (auto const& [k, v] : freq2) {
      value2.push_back(v);
    }
    std::sort(value2.begin(), value2.end());

    return value1 == value2;
  }

  // Constraints:
  // - `word1` and `word2` contain only lowercase English letters.
  bool close_strings_v2(string const& word1, string const& word2) {
    if (word1.size() != word2.size()) {
      return false;
    }

    vector<int> freq1(26, 0), freq2(26, 0);
    vector<bool> present1(26, false), present2(26, false);
    for (char c : word1) {
      ++freq1[c - 'a'];
      present1[c - 'a'] = true;
    }
    for (char c : word2) {
      ++freq2[c - 'a'];
      present2[c - 'a'] = true;
    }

    if (present1 != present2) {
      return false;
    }

    std::sort(freq1.begin(), freq1.end());
    std::sort(freq2.begin(), freq2.end());
    return freq1 == freq2;
  }
};
