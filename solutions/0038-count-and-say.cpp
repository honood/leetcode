// HoNooD <honood@gmail.com>
// 2025.02.21 22:15

// 38. Count and Say
// https://leetcode.com/problems/count-and-say/description/

// Run-length encoding
// https://en.wikipedia.org/wiki/Run-length_encoding

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  string countAndSay(int n) {
    return count_and_say_v2(n);
  }

private:
  string count_and_say_v1(int n) {
    assert(n >= 1);
    if (n == 1) {
      return "1";
    }

    string previous = count_and_say_v1(n - 1);

    string result{};
    int len = previous.size();
    for (int i = 0; i < len; ++i) {
      char current_char = previous[i];
      int count = 1;
      while (i + 1 < len && previous[i + 1] == current_char) {
        ++count;
        ++i;
      }

      result += std::to_string(count);
      result += current_char;
    }

    return result;
  }

  string count_and_say_v2(int n) {
    assert(n >= 1);
    if (n == 1) {
      return "1";
    }

    string current = "1";
    for (int i = 2; i <= n; ++i) {
      string next{};

      int len = current.size();
      for (int i = 0; i < len; ++i) {
        char current_char = current[i];
        int count = 1;
        while (i + 1 < len && current[i + 1] == current_char) {
          ++count;
          ++i;
        }

        next += std::to_string(count);
        next += current_char;
      }

      current.swap(next);
    }

    return current;
  }
};
