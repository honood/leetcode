// HoNooD <honood@gmail.com>
// 2024.06.08 00:24

// 383. Ransom Note
// https://leetcode.com/problems/ransom-note/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  bool canConstruct(string ransomNote, string magazine) {
    if (magazine.empty()) {
      return ransomNote.empty();
    }

    unordered_map<char, int> letterCount{};
    for (auto const& c : magazine) {
      ++letterCount[c];
    }

    for (auto const& c : ransomNote) {
      if (letterCount[c]-- <= 0) {
        return false;
      }
    }

    return true;
  }
};
