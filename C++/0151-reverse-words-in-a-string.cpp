// HoNooD <honood@gmail.com>
// 2024.06.16 01:25

// 151. Reverse Words in a String
// https://leetcode.com/problems/reverse-words-in-a-string/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  string reverseWords(string s) {
    if (s.empty()) {
      return s;
    }

    vector<string> words{};
    int all_words_len = 0;
    // `std::stringstream` is also suitable
    std::istringstream ss{s};
    string word{};
    // https://en.cppreference.com/w/cpp/string/basic_string/operator_ltltgtgt
    // https://en.cppreference.com/w/cpp/io/basic_ios/operator_bool
    while (ss >> word) {
      all_words_len += word.size();
      words.emplace_back(std::move(word));
    }

    if (words.empty()) {
      return {};
    }

    string res{};
    res.reserve(all_words_len + words.size() - 1);
    for (int i = words.size() - 1; i >= 0; --i) {
      if (!res.empty()) {
        res += ' ';
      }
      res += words[i];
    }

    return res;
  }
};

// Efficient and less memory usage, but more complex and less intuitive.
class Solution_2 {
public:
  string reverseWords(string s) {
    if (s.empty()) {
      return s;
    }

    string res{};
    string word{};
    for (int i = s.size() - 1; i >= -1; --i) {
      if (i >= 0 && s[i] != ' ') {
        word += s[i];
      } else if (!word.empty()) {
        if (!res.empty()) {
          res += ' ';
        }
        for (int j = word.size() - 1; j >= 0; --j) {
          res += word[j];
        }

        if (i != -1) {
          word.clear();
        }
      }
    }

    return res;
  }
};

// Not recommended: more memory is used due to repeated string allocations
// (`res = word + ' ' + res;`) in the loop. Each concatenation operation
// allocates additional memory, leading to increased memory usage, especially
// with larger inputs.
class Solution_3 {
public:
  string reverseWords(string s) {
    if (s.empty()) {
      return s;
    }

    string res{};
    // `std::stringstream` is also suitable
    std::istringstream ss{s};
    string word{};
    // https://en.cppreference.com/w/cpp/string/basic_string/operator_ltltgtgt
    // https://en.cppreference.com/w/cpp/io/basic_ios/operator_bool
    while (ss >> word) {
      if (res.empty()) {
        res = std::move(word);
      } else {
        res = word + ' ' + res;
      }
    }

    return res;
  }
};

// Not recommended: more memory is used due to repeated string allocations
// (`res = word + ' ' + res;`) in the loop. Each concatenation operation
// allocates additional memory, leading to increased memory usage, especially
// with larger inputs.
class Solution_4 {
public:
  string reverseWords(string s) {
    if (s.empty()) {
      return s;
    }

    string res{};
    string word{};
    int n = s.size();
    for (int i = 0; i < n; ++i) {
      while (i < n && s[i] != ' ') {
        word += s[i];
        ++i;
      }

      if (!word.empty()) {
        if (res.empty()) {
          res = std::move(word);
        } else {
          res = word + ' ' + res;
        }
        word.clear();
      }
    }

    return res;
  }
};

// Not recommended: more memory is used due to repeated string allocations
// (`res = word + ' ' + res;`) in the loop. Each concatenation operation
// allocates additional memory, leading to increased memory usage, especially
// with larger inputs.
class Solution_5 {
public:
  string reverseWords(string s) {
    if (s.empty()) {
      return s;
    }

    string res{};
    string word{};
    int n = s.size();
    for (int i = 0; i <= n; ++i) {
      if (i < n && s[i] != ' ') {
        word += s[i];
      } else if (!word.empty()) {
        if (res.empty()) {
          res = std::move(word);
        } else {
          res = word + ' ' + res;
        }

        if (i != n) {
          word.clear();
        }
      }
    }

    return res;
  }
};
