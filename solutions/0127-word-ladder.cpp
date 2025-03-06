// HoNooD <honood@gmail.com>
// 2024.06.27 10:30

// 127. Word Ladder
// https://leetcode.com/problems/word-ladder/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// Note:
// This problem is very similar to "433. Minimum Genetic Mutation".
// https://leetcode.com/problems/minimum-genetic-mutation/description/
//
// Refer to `0433-minimum-genetic-mutation.cpp` for details.
class Solution {
public:
  // Note: `beginWord`, `endWord`, and `wordList[i]` consist of lowercase
  // English letters.
  int ladderLength(string begin_word, string end_word, vector<string>& word_list) {
    if (begin_word.empty() || end_word.size() != begin_word.size() ||
        word_list.empty() ||
        std::any_of(word_list.cbegin(), word_list.cend(), [&](auto const& w) { return w.size() != end_word.size(); })) {
      return 0;
    }

    unordered_set<string> word_set{word_list.cbegin(), word_list.cend()};
    if (!word_set.contains(end_word)) {
      return 0;
    }

    queue<pair<string, int>> q{};
    q.emplace(begin_word, 1);
    while (!q.empty()) {
      // Note: `q.pop()` invalidates references, so do NOT use:
      // 1. auto const& [word, len] = q.front();
      // 2. auto& [word, len] = q.front();
      auto [word, len] = q.front();
      q.pop();

      // try changing each character of the word
      for (int i = 0; i < word.size(); ++i) {
        char original = word[i];
        for (char c = 'a'; c <= 'z'; ++c) {
          if (c == original) {
            continue;
          }

          word[i] = c;
          if (word == end_word) {
            return len + 1;
          }

          if (word_set.contains(word)) {
            q.emplace(word, len + 1);
            word_set.erase(word);
          }
        }
        word[i] = original;
      }
    }

    return 0;
  }
};
