// HoNooD <honood@gmail.com>
// 2024.06.09 10:55

// 242. Valid Anagram
// https://leetcode.com/problems/valid-anagram/description/?envType=study-plan-v2&envId=top-interview-150

// An Anagram is a word or phrase formed by rearranging the letters of a
// different word or phrase, typically using all the original letters exactly
// once.

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// Note:
// 1. Not applicable for input containing Unicode characters.
// 2. Switch input parameters to `wstring` and replace `char` with `wchar_t` in
// the code to handle Unicode characters.
class Solution {
public:
  bool isAnagram(string s, string t) {
    if (s.size() != t.size()) {
      return false;
    }

    unordered_map<char, int> charFreq{};
    for (auto const& c : s) {
      ++charFreq[c];
    }

    for (auto const& c : t) {
      if (!charFreq.contains(c)) {
        return false;
      }

      if (--charFreq[c] == 0) {
        charFreq.erase(c);
      }
    }

    return charFreq.empty();
  }
};

// Better performance
//
// Note: Only applicable for input parameters containing ASCII characters.
class Solution_2 {
public:
  // Constraints: `s` and `t` consist of lowercase English letters.
  bool isAnagram(string s, string t) {
    if (s.size() != t.size()) {
      return false;
    }

    int charFreq[26] = {0};
    /*
    for (auto const& c : s) {
      ++charFreq[c - 'a'];
    }

    for (auto const& c : t) {
      --charFreq[c - 'a'];
    }
    */
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
