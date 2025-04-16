// HoNooD <honood@gmail.com>
// 2022.06.04 18:39
// 2025.04.16 10:05

// 3. Longest Substring Without Repeating Characters
// https://leetcode.com/problems/longest-substring-without-repeating-characters/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  int lengthOfLongestSubstring(string s) {
    return length_of_longest_substring_v3(std::move(s));
  }

private:
  // Brute Force
  //
  // - Time complexity: O(n^2), where n is the length of the string
  // - Space complexity: O(min(m, n)), where m is the size of the character set
  //   and n is the length of the string
  int length_of_longest_substring_v1(string const& s) {
    if (s.empty()) {
      return 0;
    }

    int max_len = 0;
    for (int n = s.length(), i = 0; i < n; ++i) {
      unordered_set<char> seen{};
      for (int j = i; j < n; ++j) {
        if (seen.contains(s[j])) {
          break;
        }

        seen.emplace(s[j]);
        max_len = std::max(max_len, j - i + 1);
      }
    }
    return max_len;
  }

  // - Time complexity: O(n), where n is the length of the string
  // - Space complexity: O(min(m, n)), where m is the size of the character set
  //   and n is the length of the string
  int length_of_longest_substring_v2(string const& s) {
    if (s.empty()) {
      return 0;
    }

    int max_len = 0;
    unordered_set<char> window_chars{};

    for (int n = s.length(), left = 0, right = 0; right < n; ++right) {
      while (window_chars.contains(s[right])) {
        window_chars.erase(s[left]);
        ++left;
      }

      window_chars.emplace(s[right]);
      max_len = std::max(max_len, right - left + 1);
      // Alternatively:
      // max_len = std::max(max_len, static_cast<int>(window_chars.size()));
    }

    // Alternatively:
    /*
    int left = 0;
    int right = 0;
    while (right < s.length()) {
      if (window_chars.contains(s[right])) {
        window_chars.erase(s[left]);
        ++left;
      } else {
        window_chars.emplace(s[right]);
        max_len = std::max(max_len, right - left + 1);
        // Alternatively:
        // max_len = std::max(max_len, static_cast<int>(window_chars.size()));

        ++right;
      }
    }
    */

    return max_len;
  }

  // - Time complexity: O(n), where n is the length of the string
  // - Space complexity: O(min(m, n)), where m is the size of the character set
  //   and n is the length of the string
  int length_of_longest_substring_v3(string const& s) {
    if (s.empty()) {
      return 0;
    }

    int max_len = 0;
    unordered_map<char, int> last_seen_index{};

    for (int n = s.length(), left = 0, right = 0; right < n; ++right) {
      if (last_seen_index.contains(s[right])) {
        // Note: Use std::max to ensure 'left' only moves forward.
        //
        // The last occurrence (last_seen_index[s[right]]) might be before the
        // current 'left'. Using std::max prevents 'left' from moving backward.
        //
        // Example: s = "abba". When right = 3 ('a'), last_seen_index['a'] = 0.
        // If simply 'left = last_seen_index[s[right]] + 1', left would become
        // 1, moving back from its current value of 2. std::max(2, 0 + 1)
        // correctly keeps left = 2.
        left = std::max(left, last_seen_index[s[right]] + 1);
      }

      last_seen_index[s[right]] = right;
      max_len = std::max(max_len, right - left + 1);
    }

    return max_len;
  }

  // - Time complexity: O(n), where n is the length of the string
  // - Space complexity: O(1)
  int length_of_longest_substring_v4(string const& s) {
    if (s.empty()) {
      return 0;
    }

    int max_len = 0;
    // Assuming ASCII character set (128 characters)
    vector<int> last_seen_index(128, -1);

    for (int n = s.length(), left = 0, right = 0; right < n; ++right) {
      if (last_seen_index[s[right]] >= left) {
        left = last_seen_index[s[right]] + 1;
      }

      last_seen_index[s[right]] = right;
      max_len = std::max(max_len, right - left + 1);
    }

    return max_len;
  }

  // - Time complexity: O(n), where n is the length of the string
  // - Space complexity: O(1)
  int length_of_longest_substring_v4_2(string const& s) {
    if (s.empty()) {
      return 0;
    }

    int max_len = 0;
    // Assuming ASCII character set (128 characters)
    vector<int> next_left_index(128, 0);

    for (int n = s.length(), left = 0, right = 0; right < n; ++right) {
      left = std::max(left, next_left_index[s[right]]);
      max_len = std::max(max_len, right - left + 1);
      next_left_index[s[right]] = right + 1;
    }

    return max_len;
  }
};
