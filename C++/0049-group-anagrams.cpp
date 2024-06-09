// HoNooD <honood@gmail.com>
// 2024.06.09 12:17

// 49. Group Anagrams
// https://leetcode.com/problems/group-anagrams/?envType=study-plan-v2&envId=top-interview-150

// An Anagram is a word or phrase formed by rearranging the letters of a
// different word or phrase, typically using all the original letters exactly
// once.

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  // Constraints: `strs[i]` consists of lowercase English letters.
  vector<vector<string>> groupAnagrams(vector<string>& strs) {
    vector<vector<string>> res{};

    int n = strs.size();
    vector<bool> used(n, false);
    for (int i = 0; i < n; ++i) {
      if (used[i]) {
        continue;
      }

      vector<string> anagrams{strs[i]};
      for (int j = i + 1; j < n; ++j) {
        if (!used[j] && isAnagram(strs[i], strs[j])) {
          anagrams.emplace_back(strs[j]);
          used[j] = true;
        }
      }

      used[i] = true;
      res.emplace_back(std::move(anagrams));
    }

    return res;
  }

private:
  bool isAnagram(string const& s, string const& t) {
    if (s.size() != t.size()) {
      return false;
    }

    int charFreq[26] = {0};
    for (int i = 0; i < s.size(); ++i) {
      ++charFreq[s[i] - 'a'];
      --charFreq[t[i] - 'a'];
    }

    for (int i = 0; i < 26; ++i) {
      if (charFreq[i] != 0) {
        return false;
      }
    }

    return true;
  }
};

class Solution_2 {
public:
  // Constraints: `strs[i]` consists of lowercase English letters.
  vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> groups{};
    for (auto const& str : strs) {
      string key{str};
      std::sort(key.begin(), key.end());
      groups[key].emplace_back(str);
    }

    // vector<vector<string>> res(groups.size());
    // for (auto it = res.begin(); auto& [key, anagrams] : groups) {
    //   (it++)->swap(anagrams);
    // }
    vector<vector<string>> res{};
    res.reserve(groups.size());
    for (auto& p : groups) {
      res.emplace_back(std::move(p.second));
    }

    return res;
  }
};
