// HoNooD <honood@gmail.com>
// 2024.06.09 18:22

// 438. Find All Anagrams in a String
// https://leetcode.com/problems/find-all-anagrams-in-a-string/description/

// An Anagram is a word or phrase formed by rearranging the letters of a
// different word or phrase, typically using all the original letters exactly
// once.

// See also:
// 242. Valid Anagram
// https://leetcode.com/problems/valid-anagram/description/?envType=study-plan-v2&envId=top-interview-150
// 49. Group Anagrams
// https://leetcode.com/problems/group-anagrams/?envType=study-plan-v2&envId=top-interview-150

class Solution {
public:
 // Constraints: `s` and `p` consist of lowercase English letters.
  vector<int> findAnagrams(string s, string p) {
    if (p.size() > s.size()) {
      return {};
    }

    array<int, 26> pFreq{};
    for (int i = 0; i < p.size(); ++i) {
      ++pFreq[p[i] - 'a'];
    }

    vector<int> res{};
    for (int i = 0; i <= s.size() - p.size(); ++i) {
      array<int, 26> freq{pFreq};
      for (int j = i; j < i + p.size(); ++j) {
        --freq[s[j] - 'a'];
      }

      int k = 0;
      for (; k < 26; ++k) {
        if (freq[k] != 0) {
          break;
        }
      }

      if (k == 26) {
        res.emplace_back(i);
      }
    }

    return res;
  }
};

// Better performance
class Solution_2 {
public:
 // Constraints: `s` and `p` consist of lowercase English letters.
  vector<int> findAnagrams(string s, string p) {
    if (p.size() > s.size()) {
      return {};
    }

    vector<int> res{};

    unordered_map<char, int> pFreq{};
    for (auto const& c : p) {
      ++pFreq[c];
    }

    unordered_map<char, int> sFreq{};
    for (int left = 0, right = 0, match = 0; right < s.size(); ++right) {
      char c = s[right];
      if (pFreq.contains(c)) {
        ++sFreq[c];
        if (sFreq[c] == pFreq[c]) {
          ++match;
        }
      }

      if (right - left + 1 > p.size()) {
        char c = s[left];
        if (pFreq.contains(c)) {
          if (sFreq[c] == pFreq[c]) {
            --match;
          }
          --sFreq[c];
        }

        ++left;
      }

      if (match == pFreq.size()) {
        res.emplace_back(left);
      }
    }

    return res;
  }
};

// Same performance as `Solution_2` while more readable and intuitive
class Solution_3 {
public:
 // Constraints: `s` and `p` consist of lowercase English letters.
  vector<int> findAnagrams(string s, string p) {
    int windowSize = p.size();
    if (s.size() < windowSize) {
      return {};
    }

    vector<int> res{};

    vector<int> pFreq(26, 0);
    for (auto const& c : p) {
      ++pFreq[c - 'a'];
    }

    vector<int> sFreq(26, 0);
    for (int i = 0; i < s.size(); ++i) {
      ++sFreq[s[i] - 'a'];

      if (i >= windowSize) {
        --sFreq[s[i - windowSize] - 'a'];
      }

      if (i >= windowSize - 1 && sFreq == pFreq) {
        res.emplace_back(i - windowSize + 1);
      }
    }

    return res;
  }
};
