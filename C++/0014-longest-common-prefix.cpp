// HoNooD
// 2024.06.05 15:37

// 14. Longest Common Prefix
// https://leetcode.com/problems/longest-common-prefix/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// Not recommended, see `Solution_2`
class Solution {
public:
  string longestCommonPrefix(vector<string>& strs) {
    if (strs.empty()) {
      return "";
    }

    int pos = 0;
    while (true) {
      char c{};
      bool reachEnd = false;
      for (int i = 0; i < strs.size(); ++i) {
        string const& str = strs[i];
        if (pos >= str.size()) {
          reachEnd = true;
          break;
        }

        if (i == 0) {
          c = str[pos];
        } else if (str[pos] != c) {
          reachEnd = true;
          break;
        }
      }

      if (reachEnd) {
        break;
      }

      ++pos;
    }

    return strs[0].substr(0, pos);
  }
};

// Best
class Solution_2 {
public:
  string longestCommonPrefix(vector<string>& strs) {
    if (strs.empty()) {
      return "";
    }

    string const& first = strs[0];
    for (int col = 0; col < first.size(); ++col) {
      char c = first[col];
      for (int row = 1; row < strs.size(); ++row) {
        string const& str = strs[row];
        if (col == str.size() || str[col] != c) {
          return first.substr(0, col);
        }
      }
    }

    return first;
  }
};

// C++17 needed
class Solution_3 {
public:
  string longestCommonPrefix(vector<string>& strs) {
    if (strs.empty()) {
      return "";
    }

    string_view prefix = strs[0];
    for (int i = 1; i < strs.size(); ++i) {
      while (strs[i].find(prefix) != 0) {
        prefix = prefix.substr(0, prefix.size() - 1);
        if (prefix.empty()) {
          return "";
        }
      }
    }

    return static_cast<string>(prefix);
  }
};
