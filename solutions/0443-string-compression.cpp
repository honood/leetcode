// HoNooD <honood@gmail.com>
// 2025.02.21 14:16

// 443. String Compression
// https://leetcode.com/problems/string-compression/description/?envType=study-plan-v2&envId=leetcode-75

// You must write an algorithm that uses only constant extra space.

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  int compress(vector<char>& chars) {
    int len = chars.size();
    int write_pos = 0;
    for (int i = 0; i < len; ++i) {
      char curr_char = chars[i];
      int count = 1;
      while (i + 1 < len && chars[i + 1] == curr_char) {
        ++count;
        ++i;
      }

      chars[write_pos++] = curr_char;
      if (count > 1) {
        for (char c : to_string(count)) {
          chars[write_pos++] = c;
        }
      }
    }

    return write_pos;
  }

private:
  string to_string(int num) {
    assert(num > 0);
    string temp{};
    while (num > 0) {
      temp += '0' + num % 10;
      num /= 10;
    }

    return {temp.crbegin(), temp.crend()};
  }
};
