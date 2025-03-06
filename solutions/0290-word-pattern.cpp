// HoNooD <honood@gmail.com>
// 2024.06.08 12:48

// 290. Word Pattern
// https://leetcode.com/problems/word-pattern/description/?envType=study-plan-v2&envId=top-interview-150

// Similar to: 205. Isomorphic Strings
// https://leetcode.com/problems/isomorphic-strings/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  // Constraints:
  // 1. `s` contains only lowercase English letters and spaces `' '`;
  // 2. `s` does not contain any leading or trailing spaces;
  // 3. All the words in `s` are separated by a single space.
  bool wordPattern(string pattern, string s) {
    vector<string> words{wordsFromString(s)};
    if (pattern.size() != words.size()) {
      return false;
    }

    if (pattern.empty()) {
      return true;
    }

    unordered_map<char, string> charToWord{};
    unordered_map<string, char> wordToChar{};
    for (int i = 0; i < pattern.size(); ++i) {
      char c = pattern[i];
      string w = words[i];

      if (charToWord.contains(c) && charToWord[c] != w) {
        return false;
      }

      if (wordToChar.contains(w) && wordToChar[w] != c) {
        return false;
      }

      charToWord[c] = w;
      wordToChar[w] = c;
    }

    return true;
  }

private:
  vector<string> wordsFromString(string const& s) {
    vector<string> words{};
    // std::stringstream is OK, too.
    istringstream ss{s};
    string word{};
    // https://en.cppreference.com/w/cpp/string/basic_string/operator_ltltgtgt
    // https://en.cppreference.com/w/cpp/io/basic_ios/operator_bool
    while (ss >> word) {
      words.emplace_back(word);
    }

    return words;
  }

  vector<string> wordsFromString2(string const& s) {
    vector<string> words{};
    string::size_type pos = 0;
    string::size_type space = string::npos;
    while ((space = s.find(' ', pos)) != string::npos) {
      string word = s.substr(pos, space - pos);
      words.emplace_back(word);
      pos = space + 1;
    }
    words.emplace_back(s.substr(pos, s.size() - pos));

    return words;
  }
};
