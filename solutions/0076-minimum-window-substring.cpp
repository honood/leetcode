// HoNooD <honood@gmail.com>
// 2024.06.24 14:30

// 76. Minimum Window Substring
// https://leetcode.com/problems/minimum-window-substring/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// sliding window technique
class Solution {
public:
  string minWindow(string s, string t) {
    if (t.empty() || s.size() < t.size()) {
      return "";
    }

    unordered_map<char, int> t_char_freq{};
    for (auto const& c : t) {
      ++t_char_freq[c];
    }

    int left = 0;
    int matched_unique_chars = 0;
    int min_window_start = 0;
    int min_window_len = std::numeric_limits<int>::max();
    unordered_map<char, int> window_char_freq{};
    for (int right = left; right < s.size(); ++right) {
      char c = s[right];
      if (t_char_freq.contains(c)) {
        ++window_char_freq[c];
        if (window_char_freq[c] == t_char_freq[c]) {
          ++matched_unique_chars;
        }
      }

      while (matched_unique_chars == t_char_freq.size()) {
        if (right - left + 1 < min_window_len) {
          min_window_len = right - left + 1;
          min_window_start = left;
        }

        char left_char = s[left];
        if (t_char_freq.contains(left_char)) {
          if (window_char_freq[left_char] == t_char_freq[left_char]) {
            --matched_unique_chars;
          }
          --window_char_freq[left_char];
        }
        ++left;
      } // while
    } // for

    return min_window_len == std::numeric_limits<int>::max()
               ? ""
               : s.substr(min_window_start, min_window_len);
  }
};

// Differences from `Solution`:
// 1. Uses `matched_chars` to count the total matched characters instead of
// `matched_unique_chars` to count the number of fully matched unique
// characters.
// 2. `while` condition checks if `matched_chars` equals `t.size()` rather than
// comparing `matched_unique_chars` to the number of unique characters in `t`.
// 3. Updates `matched_chars` when `window_char_freq[c]` is less than or equal
// to `t_char_freq[c]`, instead of checking for equality.
class Solution_2 {
public:
  string minWindow(string s, string t) {
    if (t.empty() || s.size() < t.size()) {
      return "";
    }

    unordered_map<char, int> t_char_freq{};
    for (auto const& c : t) {
      ++t_char_freq[c];
    }

    int left = 0;
    int matched_chars = 0;
    int min_window_start = 0;
    int min_window_len = std::numeric_limits<int>::max();
    unordered_map<char, int> window_char_freq{};
    for (int right = left; right < s.size(); ++right) {
      char c = s[right];
      if (t_char_freq.contains(c)) {
        ++window_char_freq[c];
        if (window_char_freq[c] <= t_char_freq[c]) {
          ++matched_chars;
        }
      }

      while (matched_chars == t.size()) {
        if (right - left + 1 < min_window_len) {
          min_window_len = right - left + 1;
          min_window_start = left;
        }

        char left_char = s[left];
        if (t_char_freq.contains(left_char)) {
          if (window_char_freq[left_char] == t_char_freq[left_char]) {
            --matched_chars;
          }
          --window_char_freq[left_char];
        }
        ++left;
      } // while
    } // for

    return min_window_len == std::numeric_limits<int>::max()
               ? ""
               : s.substr(min_window_start, min_window_len);
  }
};
