// HoNooD <honood@gmail.com>
// 2024.07.13 15:30

// 556. Next Greater Element III
// https://leetcode.com/problems/next-greater-element-iii/description/

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// To find the next greater permutation of a given number, the algorithm focuses
// on minimally modifying the current permutation to produce the smallest
// possible number that is larger than the given one. The key is to keep the
// initial portion of the number as unchanged as possible while rearranging the
// latter part into the smallest possible order.
//
// Example 1: n = 12431
// 1 █▉              1 █▉              1 █▉
// 2 █▉█▉            3 █▉█▉█▉          3 █▉█▉█▉
// 4 █▉█▉█▉█▉   =>   4 █▉█▉█▉█▉   =>   1 █▉
// 3 █▉█▉█▉          2 █▉█▉            2 █▉█▉
// 1 █▉              1 █▉              4 █▉█▉█▉█▉
//
// Example 2: n = 536321
// 5 █▉█▉█▉█▉█▉          5 █▉█▉█▉█▉█▉          5 █▉█▉█▉█▉█▉
// 3 █▉█▉█▉              6 █▉█▉█▉█▉█▉█▉        6 █▉█▉█▉█▉█▉█▉
// 6 █▉█▉█▉█▉█▉█▉   =>   3 █▉█▉█▉         =>   1 █▉
// 3 █▉█▉█▉              3 █▉█▉█▉              2 █▉█▉
// 2 █▉█▉                2 █▉█▉                3 █▉█▉█▉
// 1 █▉                  1 █▉                  3 █▉█▉█▉
class Solution {
public:
  int nextGreaterElement(int n) {
    return next_greater_element_v1(n);
  }

private:
  int next_greater_element_v1(int n) {
    if (n <= 0) {
      return -1;
    }

    string digits{std::to_string(n)};

    // step 1: find the first decreasing element from the end
    //
    // Note: '0' < '1' < '2' < '3' < '4' < '5' < '6' < '7' < '8' < '9'
    int len = digits.size();
    int i = len - 2;
    while (i >= 0 && digits[i] >= digits[i + 1]) {
      --i;
    }
    // if no such element is found, return `-1`
    if (i < 0) {
      return -1;
    }

    // step 2: find the element just larger than `digits[i]` to its right
    int j = len - 1;
    while (digits[j] <= digits[i]) {
      --j;
    }

    // step 3: swap the elements at `i` and `j`
    std::swap(digits[i], digits[j]);

    // step 4: reverse the elements to the rigth of `i`
    std::reverse(std::next(digits.begin(), i + 1), digits.end());

    long long res = std::stoll(digits);
    if (res > std::numeric_limits<int>::max()) {
      return -1;
    }

    return static_cast<int>(res);
  }

  int next_greater_element_v2(int n) {
    if (n <= 0) {
      return -1;
    }

    vector<int> digits{};
    while (n > 0) {
      digits.emplace_back(n % 10);
      n /= 10;
    }
    std::reverse(digits.begin(), digits.end());

    // step 1: find the first decreasing element from the end
    int len = digits.size();
    int i = len - 2;
    while (i >= 0 && digits[i] >= digits[i + 1]) {
      --i;
    }
    // if no such element is found, return `-1`
    if (i < 0) {
      return -1;
    }

    // step 2: find the element just larger than `digits[i]` to its right
    int j = len - 1;
    while (digits[j] <= digits[i]) {
      --j;
    }

    // step 3: swap the elements at `i` and `j`
    std::swap(digits[i], digits[j]);

    // step 4: reverse the elements to the rigth of `i`
    std::reverse(std::next(digits.begin(), i + 1), digits.end());

    long long res = 0;
    for (int digit : digits) {
      res = res * 10 + digit;
      if (res > std::numeric_limits<int>::max()) {
        return -1;
      }
    }

    return static_cast<int>(res);
  }
};
