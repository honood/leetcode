// HoNooD <honood@gmail.com>
// 2024.07.08 15:27

// 5. Longest Palindromic Substring
// https://leetcode.com/problems/longest-palindromic-substring/description/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Longest_palindromic_substring
// https://en.wikipedia.org/wiki/Dynamic_programming

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// Expand Around Center
//
// Characteristics of palindromic substrings:
// 1. A palindromic substring is symmetric around its center.
// 2. For each character (or pair of characters) in the string, check if it can
//    be the center of a palindrome by expanding outward symmetrically.
//
// Note: intuitive and straightforward
//
// time complexity: O(n^2), as each expansion takes O(n) time, and we have O(n)
//                  possible centers.
// space complexity: O(1)
class Solution {
public:
  string longestPalindrome(string const& s) {
    if (s.size() < 2) {
      return s;
    }

    string_view longest{};
    for (int i = 0; i < s.size(); ++i) {
      // check odd length palindromes (single center)
      string_view odd_palindrome = expand_around_center(s, i, i);
      if (odd_palindrome.size() > longest.size()) {
        longest = odd_palindrome;
      }

      // check even length palindromes (double center)
      string_view even_palindrome = expand_around_center(s, i, i + 1);
      if (even_palindrome.size() > longest.size()) {
        longest = even_palindrome;
      }
    }

    return string{longest};
  }

private:
  string_view expand_around_center(string_view s, int left, int right) {
    if (s.empty()) {
      return "";
    }

    while (left >= 0 && right < s.size() && s[left] == s[right]) {
      --left;
      ++right;
    }

    return s.substr(left + 1, right - left  - 1);
  }
};

// Dynamic Programming (DP)
//
// 1. Define State:
//   - Use `dp[i][j]` to indicate whether the substring `s[i...j]` is a palindrome.
// 2. State Transition:
//   - `dp[i][j] = true` if `s[i] == s[j]` and `dp[i+1][j-1] == true`.
//   - For `j - i < 2`, only check if `s[i] == s[j]`.
// 3. Initialization:
//   - All substrings of length 1 are palindromes, i.e., `dp[i][i] = true`.
// 4. Finding the Longest Palindromic Substring:
//   - Track the start and length of the longest palindrome found during the iteration.
//
// time complexity: O(n^2), since checking each substring requires O(n^2) time.
// space complexity: O(n^2)
class Solution_2 {
public:
  string longestPalindrome(string const& s) {
    int n = s.size();
    if (n < 2) {
      return s;
    }

    vector<vector<bool>> dp(n, vector<bool>(n, false));
    int start = 0;
    int max_len = 1;

    // all substrings of length 1 are palindromes
    for (int i = 0; i < n; ++i) {
      dp[i][i] = true;
    }

    // check substrings of length greater than 1
    for (int len = 2; len <= n; ++len) {
      for (int i = 0; i <= n - len; ++i) {
        // ending index of the current substring
        int j = i + len - 1;
        if (s[i] == s[j]) {
          if (len == 2 || dp[i + 1][j - 1]) {
            dp[i][j] = true;

            if (len > max_len) {
              start = i;
              max_len = len;
            }
          }
        }
      }
    }

    return s.substr(start, max_len);
  }
};

// Manacher's algorithm
// https://en.wikipedia.org/wiki/Longest_palindromic_substring#Manacher's_algorithm
//
// time complexity: O(n), since each character is visited at most twice.
class Solution_3 {
public:
  string longestPalindrome(string const& s) {
    if (s.size() < 2) {
      return s;
    }

    // transform `s`
    string T = preprocess(s);
    int n = T.size();
    // store the radius of the palindrome centered at each character
    vector<int> P(n, 0);
    // current palindrome center
    int C = 0;
    // current palindrome right boundary
    int R = 0;

    for (int i = 0; i < n; ++i) {
      if (i < R) {
        // mirror index of `i` with respect to `C`
        // Note: i - C = C - mirr
        int mirr = C * 2 - i;
        P[i] = std::min(R - i, P[mirr]);
      }

      // expand around center `i`
      while (i - (P[i] + 1) >= 0 && i + (P[i] + 1) < n &&
             T[i - (P[i] + 1)] == T[i + (P[i] + 1)]) {
        ++P[i];
      }

      // update the center and right boundary
      if (i + P[i] > R) {
        C = i;
        R = i + P[i];
      }
    }

    int max_len = 0;
    int center_idx = 0;
    for (int i = 0; i < n; ++i) {
      if (P[i] > max_len) {
        max_len = P[i];
        center_idx = i;
      }
    }

    // `center_idx - max_len` gives the start index of the palindromic substring
    // in the transformed string. since each character in the original string is
    // separated by a '#', the actual start index in the original string is half
    // of the calculated index
    int start = (center_idx - max_len) / 2;
    return s.substr(start, max_len);
  }

private:
  string preprocess(string const& s) {
    string res{"#"};
    for (char c : s) {
      res += c;
      res += '#';
    }

    return res;
  }
};
