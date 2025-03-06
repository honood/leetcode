// HoNooD
// 2024.06.04 08:12

// 13. Roman to Integer
// https://leetcode.com/problems/roman-to-integer/description/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Roman_numerals
// https://en.wikipedia.org/wiki/Arabic_numerals
// https://en.wikipedia.org/wiki/Latin_numerals
// https://en.wikipedia.org/wiki/Numeral_system

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// https://en.wikipedia.org/wiki/Roman_numerals#Standard_form
//
// Note: No validation performed!
class Solution {
public:
  int romanToInt(string s) {
    assert(!s.empty());

    unordered_map<char, int> const romanMap{
      {'I', 1},
      {'V', 5},
      {'X', 10},
      {'L', 50},
      {'C', 100},
      {'D', 500},
      {'M', 1000}
    };

    int total = 0;
    for (int i = s.size() - 1, prevVal = 0; i >= 0; --i) {
      int currVal = romanMap.at(s[i]);

      if (currVal >= prevVal) {
        total += currVal;
      } else {
        assert(s[i] == 'I' && (s[i + 1] == 'V' || s[i + 1] == 'X') ||
               s[i] == 'X' && (s[i + 1] == 'L' || s[i + 1] == 'C') ||
               s[i] == 'C' && (s[i + 1] == 'D' || s[i + 1] == 'M'));
        total -= currVal;
      }

      prevVal = currVal;
    }

    assert(total >= 1 && total <= 3999);
    return total;
  }
};
