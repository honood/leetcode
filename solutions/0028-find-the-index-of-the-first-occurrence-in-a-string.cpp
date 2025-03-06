// HoNooD
// 2024.06.05 11:58

// 28. Find the Index of the First Occurrence in a String
// https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  // Note: The parameter names `haystack` and `needle` in the problem statement
  // have a metaphorical origin, referring to the common idiom "finding a needle
  // in a haystack." This idiom means trying to find something small and
  // difficult to locate within a large, messy context.
  int strStr(string haystack, string needle) {
    if (needle.empty()) {
      return 0;
    }

    int m = haystack.size();
    int n = needle.size();
    if (m < n) {
      return -1;
    }

    for (int i = 0; i <= m - n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (haystack[i + j] != needle[j]) {
          break;
        }

        if (j == n - 1) {
          return i;
        }
      }
    }

    return -1;
  }
};
