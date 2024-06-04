// HoNooD
// 2024.06.04 10:40

// 12. Integer to Roman
// https://leetcode.com/problems/integer-to-roman/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Roman_numerals
// https://en.wikipedia.org/wiki/Arabic_numerals
// https://en.wikipedia.org/wiki/Latin_numerals
// https://en.wikipedia.org/wiki/Numeral_system

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// Not recommended
class Solution {
public:
  string intToRoman(int num) {
    assert(num >= 1 && num <= 3999);

    string res{};
    while (num > 0) {
      if (num >= 1000) {
        num -= 1000;
        res += 'M';
      } else if (num >= 900) {
        num -= 900;
        res += "CM";
      } else if (num >= 500) {
        num -= 500;
        res += 'D';
      } else if (num >= 400) {
        num -= 400;
        res += "CD";
      } else if (num >= 100) {
        num -= 100;
        res += 'C';
      } else if (num >= 90) {
        num -= 90;
        res += "XC";
      } else if (num >= 50) {
        num -= 50;
        res += 'L';
      } else if (num >= 40) {
        num -= 40;
        res += "XL";
      } else if (num >= 10) {
        num -= 10;
        res += 'X';
      } else if (num >= 9) {
        num -= 9;
        res += "IX";
      } else if (num >= 5) {
        num -= 5;
        res += 'V';
      } else if (num >= 4) {
        num -= 4;
        res += "IV";
      } else {
        num -= 1;
        res += 'I';
      }
    } // while

    return res;
  }
};

class Solution_2 {
public:
  string intToRoman(int num) {
    assert(num >= 1 && num <= 3999);

    vector<pair<int, string>> const roman{
      {1000, "M"},
      {900, "CM"},
      {500, "D"},
      {400, "CD"},
      {100, "C"},
      {90, "XC"},
      {50, "L"},
      {40, "XL"},
      {10, "X"},
      {9, "IX"},
      {5, "V"},
      {4, "IV"},
      {1, "I"}
    };

    string res{};
    for (auto const& [val, sym] : roman) {
      while (num >= val) {
        num -= val;
        res += sym;
      }
    }

    return res;
  }
};

class Solution_3 {
public:
  string intToRoman(int num) {
    assert(num >= 1 && num <= 3999);

    vector<pair<int, vector<char const*>>> const baseSymbols{
      {1000, {"", "M", "MM", "MMM"}},
      {100, {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"}},
      {10, {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"}},
      {1, {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"}}
    };

    string res{};
    for (auto const& [base, syms] : baseSymbols) {
      res += syms[num / base];
      num %= base;
    }

    return res;
  }
};
