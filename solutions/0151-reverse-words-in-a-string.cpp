// HoNooD <honood@gmail.com>
// 2024.06.16 01:25

// 151. Reverse Words in a String
// https://leetcode.com/problems/reverse-words-in-a-string/description/?envType=study-plan-v2&envId=top-interview-150
// https://leetcode.com/problems/reverse-words-in-a-string/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  string reverseWords(string s) {
    return reverse_words_v2(std::move(s));
  }

private:
  string reverse_words_v1(string s) {
    if (s.empty()) {
      return s;
    }

    string result{};
    string word{};
    for (char c : s) {
      if (c != ' ') {
        word += c;
      } else if (!word.empty()) {
        if (!result.empty()) {
          word += ' ';
        }
        word += result;
        result.swap(word);
        word.clear();
      }
    }

    if (!word.empty()) {
      if (!result.empty()) {
        word += ' ';
      }
      word += result;
      result.swap(word);
    }

    return result;
  }

  string reverse_words_v2(string s) {
    if (s.empty()) {
      return s;
    }

    vector<string> words{};
    int all_words_len = 0;
    // `std::stringstream` is also suitable
    std::istringstream iss{s};
    string word{};
    // https://en.cppreference.com/w/cpp/string/basic_string/operator_ltltgtgt
    // https://en.cppreference.com/w/cpp/io/basic_ios/operator_bool
    // https://en.cppreference.com/w/cpp/io/basic_ios/eof#See_also
    while (iss >> word) {
      all_words_len += word.size();
      words.emplace_back(std::move(word));
    }

    if (words.empty()) {
      return {};
    }

    string result{};
    result.reserve(all_words_len + words.size() - 1);
    for (int i = words.size() - 1; i >= 0; --i) {
      if (!result.empty()) {
        result += ' ';
      }
      result += words[i];
    }

    return result;
  }

  string reverse_words_v3(string s) {
    if (s.empty()) {
      return s;
    }

    string result{};
    string word{};
    for (int i = s.size() - 1; i >= -1; --i) {
      if (i >= 0 && s[i] != ' ') {
        word += s[i];
      } else if (!word.empty()) {
        if (!result.empty()) {
          result += ' ';
        }
        for (int j = word.size() - 1; j >= 0; --j) {
          result += word[j];
        }

        if (i != -1) {
          word.clear();
        }
      }
    }

    return result;
  }

  string reverse_words_v4(string s) {
    if (s.empty()) {
      return s;
    }

    string result{};
    // `std::stringstream` is also suitable
    std::istringstream ss{s};
    string word{};
    // https://en.cppreference.com/w/cpp/string/basic_string/operator_ltltgtgt
    // https://en.cppreference.com/w/cpp/io/basic_ios/operator_bool
    // https://en.cppreference.com/w/cpp/io/basic_ios/eof#See_also
    while (ss >> word) {
      if (result.empty()) {
        result = std::move(word);
      } else {
        word += ' ';
        word += result;
        result.swap(word);
      }
    }

    return result;
  }

  string reverse_words_v5(string s) {
    if (s.empty()) {
      return s;
    }

    string result{};
    string word{};
    int n = s.size();
    for (int i = 0; i < n; ++i) {
      while (i < n && s[i] != ' ') {
        word += s[i];
        ++i;
      }

      if (!word.empty()) {
        if (result.empty()) {
          result = std::move(word);
        } else {
          word += ' ';
          word += result;
          result.swap(word);
        }

        if (i != n) {
          word.clear();
        }
      }
    }

    return result;
  }

  string reverse_words_v6(string s) {
    if (s.empty()) {
      return s;
    }

    string result{};
    string word{};
    int n = s.size();
    for (int i = 0; i <= n; ++i) {
      if (i < n && s[i] != ' ') {
        word += s[i];
      } else if (!word.empty()) {
        if (result.empty()) {
          result = std::move(word);
        } else {
          word += ' ';
          word += result;
          result.swap(word);
        }

        if (i != n) {
          word.clear();
        }
      }
    }

    return result;
  }
};
