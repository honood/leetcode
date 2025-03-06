// HoNooD <honood@gmail.com>
// 2024.06.24 08:30

// 30. Substring with Concatenation of All Words
// https://leetcode.com/problems/substring-with-concatenation-of-all-words/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// sliding window technique
class Solution {
public:
// Constraints:
// 1. All the strings of `words` are of the same length.
// 2. `s` and `words[i]` consist of lowercase English letters.
  vector<int> findSubstring(string s, vector<string>& words) {
    if (s.empty() || words.empty()) {
      return {};
    }

    int word_len = words[0].size();
    int words_count = words.size();
    int substr_len = word_len * words_count;
    int n = s.size();
    if (n < substr_len) {
      return {};
    }

    unordered_map<string_view, int> word_freq{};
    for (auto const& word : words) {
      ++word_freq[word];
    }

    vector<int> res{};
    for (int i = 0; i < word_len; ++i) {
      unordered_map<string_view, int> curr_word_freq{};
      int left = i;
      int count = 0;
      for (int right = i; right <= n - word_len && n - left >= substr_len; right += word_len) {
        string_view word = string_view(s).substr(right, word_len);
        if (!word_freq.contains(word)) {
          curr_word_freq.clear();
          count = 0;

          left = right + word_len;
          continue;
        }

        ++curr_word_freq[word];
        ++count;

        while (curr_word_freq[word] > word_freq[word]) {
          string_view left_word = string_view(s).substr(left, word_len);
          --curr_word_freq[left_word];
          --count;

          left += word_len;
        }

        if (count == words_count) {
          res.emplace_back(left);
        }
      }
    }

    return res;
  }
};
