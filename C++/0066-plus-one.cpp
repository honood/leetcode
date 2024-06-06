// HoNooD <honood@gmail.com>
// 2024.06.06 18:08

// 66. Plus One
// https://leetcode.com/problems/plus-one/description/?envType=study-plan-v2&envId=top-interview-150

class Solution {
public:
  vector<int> plusOne(vector<int>& digits) {
    vector<int> res(digits.size(), 0);

    int carry = 1;
    for (int i = digits.size() - 1; i >= 0; --i) {
      int temp = digits[i] + carry;
      res[i] = temp % 10;
      carry = temp / 10;
    }

    if (carry == 0) {
      return res;
    }

    res.insert(res.begin(), carry);
    return res;
  }
};

// Better
class Solution_2 {
public:
  vector<int> plusOne(vector<int>& digits) {
    for (int i = digits.size() - 1; i >= 0; --i) {
      if (digits[i] < 9) {
        ++digits[i];
        return digits;
      }

      digits[i] = 0;
    }

    digits.insert(digits.begin(), 1);
    return digits;
  }
};
