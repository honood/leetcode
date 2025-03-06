// HoNooD <honood@gmail.com>
// 2024.07.04 08:25

// 139. Word Break
// https://leetcode.com/problems/word-break/description/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Dynamic_programming

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  bool wordBreak(string s, vector<string> const& word_dict) {
    unordered_set<string_view> const word_set{word_dict.cbegin(), word_dict.cend()};

    // `dp[i]` indicates whether `s[0...i-1]` can be segmented into words in the
    // `word_dict`
    vector<bool> dp(s.size() + 1, false);
    // base case: an empty string can always be segmented
    dp[0] = true;

    for (int i = 1; i <= s.size(); ++i) {
      // check all possible end positions `j` within the string
      for (int j = 0; j < i; ++j) {
        if (dp[j] && word_set.contains(string_view(s).substr(j, i - j))) {
          dp[i] = true;
          // no need to check further, we found a valid segmentation
          break;
        }
      }
    }

    return dp[s.size()];
  }

  bool word_break_debug(string s, vector<string> const& word_dict) {
    unordered_set<string_view> const word_set{word_dict.cbegin(), word_dict.cend()};

    // `dp[i]` indicates whether `s[0...i-1]` can be segmented into words in the
    // `word_dict`
    vector<bool> dp(s.size() + 1, false);
    // base case: an empty string can always be segmented
    dp[0] = true;

    for (int i = 1; i <= s.size(); ++i) {
      // check all possible end positions `j` within the string
      for (int j = 0; j < i; ++j) {
        auto substr = string_view(s).substr(j, i - j);
        bool contains = word_set.contains(substr);
        cout << "i = " << setw(2) << i
          << "; j = " << setw(2) << j
          << "; substr = " << setw(s.size() + 2) << std::quoted(substr)
          << "; dp[" << setw(2) << j << "] = " << setw(5) << (dp[j] ? "true" : "false")
          << "; word_set.contains(" << setw(s.size() + 2) << std::quoted(substr) << ") = " << setw(5) << (contains ? "true" : "false")
          << "; dp[" << setw(2) << i << "] = ";
        if (dp[j] && contains) {
          cout << "true\n";
          dp[i] = true;
          // no need to check further, we found a valid segmentation
          break;
        } else {
          cout << "  / \n";
        }
      }
      cout << '\n';
    }

    return dp[s.size()];
  }
};
