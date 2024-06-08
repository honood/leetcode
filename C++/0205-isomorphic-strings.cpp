// HoNooD <honood@gmail.com>
// 2024.06.08 12:10

// 205. Isomorphic Strings
// https://leetcode.com/problems/isomorphic-strings/description/?envType=study-plan-v2&envId=top-interview-150

// Two strings `s` and `t` are isomorphic if the characters in `s` can be replaced to get `t`.

// Similar to: 290. Word Pattern
// https://leetcode.com/problems/word-pattern/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  // Please check:
  //   isIsomorphic("badc", "baba")
  //   isIsomorphic("egcd", "adfd")
  bool isIsomorphic(string s, string t) {
    if (s.size() != t.size()) {
      return false;
    }

    if (s.empty()) {
      return true;
    }

    unordered_map<char, char> mapST{};
    unordered_map<char, char> mapTS{};
    for (int i = 0; i < s.size(); ++i) {
      char sc = s[i];
      char tc = t[i];

      if (!mapST.contains(sc)) {
        mapST[sc] = tc;
      } else if (mapST[sc] != tc) {
        return false;
      }

      if (!mapTS.contains(tc)) {
        mapTS[tc] = sc;
      } else if (mapTS[tc] != sc) {
        return false;
      }
    }

    return true;
  }
};
