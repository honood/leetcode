// HoNooD <honood@gmail.com>
// 2025.02.20 09:42

// 345. Reverse Vowels of a String
// https://leetcode.com/problems/reverse-vowels-of-a-string/description/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  string reverseVowels(string s) {
    for (int i = 0, j = s.size() - 1; i < j;) {
      if (!is_vowel(s[i])) {
        ++i;
        continue;
      }

      if (!is_vowel(s[j])) {
        --j;
        continue;
      }

      std::swap(s[i], s[j]);
      ++i;
      --j;
    }

    return s;
  }

private:
  bool is_vowel(char c) {
    c = std::toupper(c);
    return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
  }
};
