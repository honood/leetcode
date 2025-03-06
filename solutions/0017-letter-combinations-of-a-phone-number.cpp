// HoNooD
// 2024.05.21 10:12

// 17. Letter Combinations of a Phone Number
// https://leetcode.com/problems/letter-combinations-of-a-phone-number/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Backtracking

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  vector<string> letterCombinations(string digits) {
    if (digits.empty()) {
      return {};
    }

    unordered_map<char, string> const mapping{
      {'2', "abc"},
      {'3', "def"},
      {'4', "ghi"},
      {'5', "jkl"},
      {'6', "mno"},
      {'7', "pqrs"},
      {'8', "tuv"},
      {'9', "wxyz"}
    };

    vector<string> res{""};
    for (auto const& c : digits) {
      combinate(res, mapping.at(c));
    }

    return res;
  }

private:
  void combinate(vector<string>& res, string const& letters) {
    vector<string> temp{};
    for (auto s : res) {
      for (auto const& c : letters) {
        temp.emplace_back(s + c);
      }
    }
    res.swap(temp);
  }
};

class Solution_2 {
public:
  vector<string> letterCombinations(string digits) {
    if (digits.empty()) {
      return {};
    }

    unordered_map<char, string> const mapping{
      {'2', "abc"},
      {'3', "def"},
      {'4', "ghi"},
      {'5', "jkl"},
      {'6', "mno"},
      {'7', "pqrs"},
      {'8', "tuv"},
      {'9', "wxyz"}
    };

    vector<string> combos{""};
    for (auto const& digit : digits) {
      vector<string> temp{};
      for (auto const& s: combos) {
        for (auto const& c : mapping.at(digit)) {
          temp.emplace_back(s + c);
        }
      }
      combos.swap(temp);
    }

    return combos;
  }
};

class Solution_3 {
public:
  vector<string> letterCombinations(string digits) {
    if (digits.empty()) {
      return {};
    }

    vector<string> res{};
    string curr{};
    backtrack(res, curr, 0, digits);

    return res;
  }

private:
  void backtrack(vector<string>& res, string& curr, int index, string const& digits) {
    if (digits.size() == index) {
      res.emplace_back(curr);
      return;
    }

    for (auto const& c : mapping_.at(digits[index])) {
      curr.push_back(c);
      backtrack(res, curr, index + 1, digits);
      curr.pop_back();
    }
  }

  unordered_map<char, string> const mapping_{
    {'2', "abc"},
    {'3', "def"},
    {'4', "ghi"},
    {'5', "jkl"},
    {'6', "mno"},
    {'7', "pqrs"},
    {'8', "tuv"},
    {'9', "wxyz"}
  };
};
