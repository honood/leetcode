// HoNooD <honood@gmail.com>
// 2025.02.22 00:43

// 3163. String Compression III
// https://leetcode.com/problems/string-compression-iii/

// Run-length encoding
// https://en.wikipedia.org/wiki/Run-length_encoding

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  string compressedString(string word) {
    string result{};
    if (word.empty()) {
      return result;
    }

    int len = word.size();
    for (int i = 0; i < len; ++i) {
      char curr_char = word[i];
      int count = 1;
      while (i + 1 < len && count < 9 && word[i + 1] == curr_char) {
        ++count;
        ++i;
      }

      result += std::to_string(count);
      result += curr_char;
    }

    return result;
  }
};
