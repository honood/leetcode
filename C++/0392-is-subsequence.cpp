// HoNooD <honood@gmail.com>
// 2025.02.22 15:28

// 392. Is Subsequence
// https://leetcode.com/problems/is-subsequence/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  bool isSubsequence(string s, string t) {
    return is_subsequence_v2(s, t);
  }

private:
  bool is_subsequence_v1(string const& s, string const& t) {
    if (s.empty()) {
      return true;
    }

    int s_len = s.size();
    int t_len = t.size();
    if (t.empty() || s_len > t_len) {
      return false;
    }

    int si = 0;
    for (int i = 0; i < t_len; ++i) {
      if (t[i] == s[si]) {
        ++si;
        if (si == s_len) {
          return true;
        }
      }
    }

    return false;
  }

  bool is_subsequence_v2(string const& s, string const& t) {
    int i = 0, j = 0;
    int s_len = s.size(), t_len = t.size();
    while (i < s_len && j < t_len) {
      if (s[i] == t[j]) {
        ++i;
      }
      ++j;
    }
    return i == s_len;
  }

  // Follow up: Suppose there are lots of incoming s, say s1, s2, ..., sk
  // where k >= 10^9, and you want to check one by one to see if t has its
  // subsequence. In this scenario, how would you change your code?
  //
  // Constraints: s and t consist only of lowercase English letters.
  vector<vector<int>> build_index(string const& t) {
    vector<vector<int>> char_index('z' - 'a' + 1);
    for (int i = 0; i < t.size(); ++i) {
      char_index[t[i] - 'a'].emplace_back(i);
    }
    return char_index;
  }

  bool is_subsequence_v3(string const& s, string const& t) {
    if (t.empty()) {
      return s.empty();
    }

    int s_len = s.size();
    int t_len = t.size();
    if (t_len < s_len) {
      return false;
    }

    static auto char_index = build_index(t);
    static string last_t = t;
    if (last_t != t) {
      char_index = build_index(t);
      last_t = t;
    }

    int prev_pos = -1;
    for (char c : s) {
      auto const& positions = char_index[c - 'a'];
      auto it = std::lower_bound(positions.begin(), positions.end(), prev_pos + 1);
      if (it == positions.end()) {
        return false;
      }
      prev_pos = *it;
    }
    return true;
  }
};
