// HoNooD <honood@gmail.com>
// 2022.06.04 18:39

// 3. Longest Substring Without Repeating Characters
// https://leetcode.com/problems/longest-substring-without-repeating-characters/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// sliding window technique
//
// See:
// 209. Minimum Size Subarray Sum (0209-minimum-size-subarray-sum.cpp)
// https://leetcode.com/problems/minimum-size-subarray-sum/description/?envType=study-plan-v2&envId=top-interview-150
class Solution {
public:
  int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> win_char_freq{};
    int max_len = 0;
    int left = 0;
    int n = s.size();
    for (int right = 0; right < n; ++right) {
      ++win_char_freq[s[right]];
      while (win_char_freq.size() < right - left + 1) {
        char c = s[left];
        --win_char_freq[c];
        if (win_char_freq[c] == 0) {
          win_char_freq.erase(c);
        }
        ++left;
      }

      max_len = std::max(max_len, right - left + 1);
    }

    return max_len;
  }
};

// sliding window technique
//
// Note: more efficient and easier to understand than `Solution`
class Solution_2 {
public:
  int lengthOfLongestSubstring(string s) {
    // store the last index of each character
    unordered_map<char, int> char_index{};
    int max_len = 0;
    int left = 0;
    int n = s.size();
    for (int right = 0; right < n; ++right) {
      char c = s[right];
      if (char_index.contains(c) && char_index[c] >= left) {
        left = char_index[c] + 1;
      }
      char_index[c] = right;

      max_len = std::max(max_len, right - left + 1);
    }

    return max_len;
  }
};

// sliding window technique
//
// Note: similar to `Solution`, but more efficient
class Solution_3 {
public:
  int lengthOfLongestSubstring(string s) {
    // Given that `s` contains English letters, digits, symbols, and spaces,
    // consider using the following code for better performance:
    //
    // std::array<int, std::numeric_limits<unsigned char>::max()> char_freq{};
    unordered_map<char, int> char_freq{};
    int max_len = 0;
    int left = 0;
    int n = s.size();
    for (int right = 0; right < n; ++right) {
      ++char_freq[s[right]];
      while (char_freq[s[right]] > 1) {
        --char_freq[s[left]];
        ++left;
      }

      max_len = std::max(max_len, right - left + 1);
    }

    return max_len;
  }
};
