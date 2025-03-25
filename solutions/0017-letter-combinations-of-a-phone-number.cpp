// HoNooD <honood@gmail.com>
// 2025.03.25 09:30
// 2024.05.21 10:12

// 17. Letter Combinations of a Phone Number
// https://leetcode.com/problems/letter-combinations-of-a-phone-number/?envType=study-plan-v2&envId=top-interview-150
// https://leetcode.com/problems/koko-eating-bananas/description/?envType=study-plan-v2&envId=leetcode-75

// https://en.wikipedia.org/wiki/Backtracking

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  vector<string> letterCombinations(string digits) {
    return letter_combinations_v1(digits);
  }

private:
  // - Time complexity: O(4^n) where n is the length of `digits`
  // - Space complexity: O(n)
  vector<string> letter_combinations_v1(string const& digits) {
    if (digits.empty()) {
      return {};
    }

    unordered_map<char, string> const mapping{
      {'2', "abc"}, {'3', "def"},  {'4', "ghi"}, {'5', "jkl"},
      {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"},
    };

    vector<string> result{};
    string current{};

    std::function<void(int)> backtrack
      = [&backtrack, &digits, &mapping, &current, &result](int index) {
          if (index == digits.size()) {
            result.emplace_back(current);
            return;
          }

          string const& letters = mapping.at(digits[index]);
          for (char letter : letters) {
            current.push_back(letter);
            backtrack(index + 1);
            current.pop_back();
          }
        };

    backtrack(0);

    return result;
  }

  // - Time complexity: O(4^n) where n is the length of `digits`
  // - Space complexity: O(4^n)
  vector<string> letter_combinations_v2(string const& digits) {
    if (digits.empty()) {
      return {};
    }

    unordered_map<char, string> const mapping{
      {'2', "abc"}, {'3', "def"},  {'4', "ghi"}, {'5', "jkl"},
      {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"},
    };

    std::queue<string> queue{{""}};
    for (char digit : digits) {
      int size = queue.size();
      for (int i = 0; i < size; ++i) {
        string current = queue.front();
        queue.pop();

        string const& letters = mapping.at(digit);
        for (char letter : letters) {
          queue.emplace(current + letter);
        }
      }
    }

    vector<string> result{};
    while (!queue.empty()) {
      result.emplace_back(queue.front());
      queue.pop();
    }
    return result;
  }
};
