// HoNooD
// 2024.06.05 15:15

// 58. Length of Last Word
// https://leetcode.com/problems/length-of-last-word/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  int lengthOfLastWord(string s) {
    if (s.empty()) {
      return 0;
    }

    int length = 0;
    for (int i = s.size() - 1; i >= 0; --i) {
      if (s[i] == ' ' && length > 0) {
        return length;
      }

      if (s[i] != ' ') {
        ++length;
      }
    }

    return length;
  }
};
