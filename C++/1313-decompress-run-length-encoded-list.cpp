// HoNooD <honood@gmail.com>
// 2025.02.21 14:16

// 1313. Decompress Run-Length Encoded List
// https://leetcode.com/problems/decompress-run-length-encoded-list/description/

// Run-length encoding
// https://en.wikipedia.org/wiki/Run-length_encoding

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  vector<int> decompressRLElist(vector<int>& nums) {
    int n = nums.size();
    assert(n % 2 == 0);

    vector<int> result{};
    for (int i = 0; i < n; i += 2) {
      int freq = nums[i];
      int val = nums[i + 1];
      result.resize(result.size() + freq, val);
    }
    return result;
  }
};
