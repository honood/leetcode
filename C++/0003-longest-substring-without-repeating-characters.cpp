// HoNooD
// 2022.06.04 18:39

// https://leetcode.com/problems/longest-substring-without-repeating-characters/

// 思路：从左向右遍历字符串中的字符，当当前字符与其紧相邻的左侧不含重复字符的子
// 串构成新子串 (假设是 curr_substr) 时，如果其中没有重复字符，则更新已知最长子
// 串的位置 (latest_pos) 和长度 (latest_count) 信息；否则，从 curr_substr 的左
// 侧开始，一个一个地更新 (减少) 当前子串的长度，直到没有重复字符 (记得把当前)
// 字符加入到 set 中。
// 
class Solution {
public:
  int lengthOfLongestSubstring(std::string s) {
    std::unordered_set<char> unique_chars{};
    int longest_pos = 0;
    int longest_count = 0;

    int pos = 0;
    int count = 0;
    for (int i = 0; i < s.length(); ++i) {
      char c = s[i];
      if (unique_chars.find(c) == unique_chars.end()) {
        unique_chars.insert(c);
        ++count;
      } else {
        while (unique_chars.find(c) != unique_chars.end()) {
          unique_chars.erase(s[pos++]);
        }
        unique_chars.insert(c);
        count = i - pos + 1;
      }

      if (count > longest_count) {
        longest_pos = pos;
        longest_count = count;
      }
    }

    return longest_count;
  }
};

// 不记录最长子串的起始位置。
class Solution2 {
public:
  int lengthOfLongestSubstring(std::string s) {
    std::unordered_map<char, int> um{};
    int j = 0;
    int max_len = 0;
    for (int i = 0; i < s.length(); ++i) {
      ++um[s[i]];
      while (um[s[i]] > 1) {
        --um[s[j++]];
      }
      max_len = std::max(max_len, i - j + 1);
    }

    return max_len;
  }
};

// 参考下面链接中陈皓的方法，使用数组替代 map 功能，优化 Solution2 的方法，运行时间缩短。
// https://github.com/haoel/leetcode/blob/master/algorithms/cpp/longestSubstringWithoutRepeatingCharacters/longestSubstringWithoutRepeatingCharacters.cpp#L44-L61
// 
class Solution3 {
public:
  int lengthOfLongestSubstring(std::string s) {
    const int MAX_CHARS = 256;
    int um[MAX_CHARS];
    std::memset(um, 0, sizeof(um));
    
    int j = 0;
    int max_len = 0;
    for (int i = 0; i < s.length(); ++i) {
      ++um[s[i]];
      while (um[s[i]] > 1) {
        --um[s[j++]];
      }
      max_len = std::max(max_len, i - j + 1);
    }

    return max_len;
  }
};
