// HoNooD <honood@gmail.com>
// 2025.02.25 09:30

// 1456. Maximum Number of Vowels in a Substring of Given Length
// https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  // Constraints:
  //   1. 1 <= s.length <= 10^5
  //   2. s consists of lowercase English letters.
  //   3. 1 <= k <= s.length
  int maxVowels(string s, int k) {
    assert(k > 0);
    int n = s.size();
    assert(n >= k);

    int current_vowels = std::count_if(s.cbegin(), std::next(s.cbegin(), k), [this](auto const& c) {
      return is_vowel(c);
    });
    int max_vowels = current_vowels;
    for (int left = 1, right = k; right < n; ++left, ++right) {
      if (is_vowel(s[right])) {
        ++current_vowels;
      }
      if (is_vowel(s[left - 1])) {
        --current_vowels;
      }
      max_vowels = std::max(max_vowels, current_vowels);
    }
    return max_vowels;
  }

private:
  bool is_vowel(char c) const noexcept {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
  }
};
