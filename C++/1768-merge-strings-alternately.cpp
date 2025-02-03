// HoNooD <honood@gmail.com>
// 2025.02.04 00:54

// 1768. Merge Strings Alternately
// https://leetcode.com/problems/merge-strings-alternately/description/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  string mergeAlternately(string word1, string word2) {
    string result(word1.size() + word2.size(), '\0');

    size_t i = 0, j = 0, k = 0;
    while (j < word1.size() && k < word2.size()) {
      result[i++] = word1[j++];
      result[i++] = word2[k++];
    }

    while (j < word1.size()) { result[i++] = word1[j++]; }
    while (k < word2.size()) { result[i++] = word2[k++]; }

    return result;
  }
};
