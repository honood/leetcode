// HoNooD <honood@gmail.com>
// 2024.06.17 10:13

// 274. H-Index
// https://leetcode.com/problems/h-index/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/H-index
//
// The h-index (Hirsch index, Hirsch number) is defined as the maximum value of
// `h` such that the given author/journal has published at least `h` papers that
// have each been cited at least `h` times.
//
// https://en.wikipedia.org/wiki/H-index#Calculation

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  // testcase:
  // 1. [2, 0, 6, 1, 5]
  // 2. [100]
  // 3. [1, 3, 1]
  // 4. [9, 7, 6, 2, 1]
  // 5. [25, 8, 5, 3, 3]
  //
  // Complexity Analysis:
  // - Time complexity: O(n * log(n))
  // - Space complexity: O(1)
  int hIndex(vector<int>& citations) {
    // sort `citations` in descending order
    std::sort(citations.begin(), citations.end(), std::greater<int>{});

    int h = 0;
    for (int i = 0; i < citations.size(); ++i) {
      if (citations[i] >= i + 1) {
        h = i + 1;
      } else {
        break;
      }
    }

    return h;
  }
};
