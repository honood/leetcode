// HoNooD <honood@gmail.com>
// 2025.03:01 16:20

// 394. Decode String
// https://leetcode.com/problems/decode-string/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  // Constraints:
  //   1. `1 <= s.length <= 30`
  //   2. `s` consists of lowercase English letters, digits, and square brackets
  //   `'[]'`.
  //   3. `s` is guaranteed to be a valid input.
  //   4. All the integers in `s` are in the range `[1, 300]`.
  string decodeString(string s) {
    return decode_string_v1(s);
  }

private:
  string decode_string_v1(string const& s) {
    std::stack<int> count_stack{};
    std::stack<string> string_stack{};

    string curr_string{};
    int curr_count = 0;

    for (char c : s) {
      if (std::isdigit(c)) {
        curr_count = curr_count * 10 + (c - '0');
      } else if (c == '[') {
        count_stack.push(curr_count);
        curr_count = 0;

        string_stack.push(std::move(curr_string));
        curr_string = ""; // No need to reset after `std::move`
      } else if (c == ']') {
        int repeat_times = count_stack.top();
        count_stack.pop();

        string repeated{};
        repeated.reserve(curr_string.size() * repeat_times);
        while (repeat_times > 0) {
          repeated += curr_string;
          --repeat_times;
        }

        curr_string = string_stack.top() + repeated;
        string_stack.pop();
      } else {
        curr_string += c;
      }
    }

    return curr_string;
  }

  string decode_string_v2(string const& s) {
    int pos = 0;
    return decode_helper(s, pos);
  }

  string decode_helper(string const& s, int& pos) {
    string result{};
    while (pos < s.size() && s[pos] != ']') {
      if (!std::isdigit(s[pos])) {
        result += s[pos];
        ++pos;
        continue;
      }

      int count = 0;
      while (pos < s.size() && std::isdigit(s[pos])) {
        count = count * 10 + (s[pos] - '0');
        ++pos;
      }

      ++pos; // skip '['
      string decoded_str = decode_helper(s, pos);
      ++pos; // skip ']'

      while (count > 0) {
        result += decoded_str;
        --count;
      }
    }

    return result;
  }
};
