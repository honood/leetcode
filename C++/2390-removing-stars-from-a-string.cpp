// HoNooD <honood@gmail.com>
// 2025.02.28 23:02

// 2390. Removing Stars From a String
// https://leetcode.com/problems/removing-stars-from-a-string/?envType=study-plan-v2&envId=leetcode-75
//
// Note:
// - The input will be generated such that the operation is always possible.
// - It can be shown that the resulting string will always be unique.

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  // Constraints:
  //   - `s` consists of lowercase English letters and stars `*`.
  string removeStars(string s) {
    return remove_stars_v4(s);
  }

private:
  string& remove_stars_v1(string& s, string::size_type start_search_pos = 0) {
    auto found = s.find('*');
    if (found == string::npos) {
      return s;
    }

    // assert(found - 1 >= 0);
    return remove_stars_v1(s.erase(found - 1, 2), found - 1);
  }

  string remove_stars_v2(string const& s) {
    stack<char> stack{};
    for (char c : s) {
      if (c != '*') {
        stack.emplace(c);
      } else if (!stack.empty()) {
        stack.pop();
      }
    }

    string result(stack.size(), '\0');
    for (auto it = result.rbegin(); it != result.rend(); ++it) {
      *it = stack.top();
      stack.pop();
    }
    return result;
  }

  // use `std::string` as stack
  string remove_stars_v3(string const& s) {
    string result{};
    for (char c : s) {
      if (c != '*') {
        result.push_back(c);
      } else if (!result.empty()) {
        result.pop_back();
      }
    }
    return result;
  }

  // Two Pointers
  string remove_stars_v4(string& s) {
    int write_pos = 0;
    for (int i = 0; i < s.size(); ++i) {
      if (s[i] != '*') {
        if (i != write_pos) {
          s[write_pos] = s[i];
        }
        ++write_pos;
      } else if (write_pos > 0) {
        --write_pos;
      }
    }

    return s.substr(0, write_pos);
  }
};
