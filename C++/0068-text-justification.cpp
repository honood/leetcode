// HoNooD <honood@gmail.com>
// 2024.06.19 08:25

// 68. Text Justification
// https://leetcode.com/problems/text-justification/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// IMO: The solution's logic is straightforward, but writing clear, concise, and
// readable code is quite challenging.
class Solution {
public:
  vector<string> fullJustify(vector<string>& words, int maxWidth) {
    if (words.empty()) {
      return {};
    }

    vector<string> res{};
    int n = words.size();
    int i = 0;
    while (i < n) {
      int lineLength = 0;
      int lineStart = i;

      // determine the words that can fit in the current line
      while (i < n && lineLength + words[i].size() + (i - lineStart) <= maxWidth) {
        lineLength += words[i].size();
        ++i;
      }

      // calculate the number of words and spaces in the current line
      int wordCount = i - lineStart;
      int spaceCount = maxWidth - lineLength;

      string line{};
      line.reserve(maxWidth);

      // check if this is the last line or the line has only one word
      if (i == words.size() || wordCount == 1) {
        // left-justified: add a single space between words
        for (int j = lineStart; j < i; ++j) {
          line += words[j];
          if (j < i - 1) {
            line += ' ';
          }
        }

        // fill the end of the line with spaces
        line += string(maxWidth - line.size(), ' ');
      } else {
        // full-justified
        int spacesBetweenWords = spaceCount / (wordCount - 1);
        int extraSpaces = spaceCount % (wordCount - 1);
        for (int j = lineStart; j < i; ++j) {
          line += words[j];
          if (j < i - 1) {
            // add spaces after the current word
            int spaceCount = spacesBetweenWords;
            if (j - lineStart < extraSpaces) {
              spaceCount += 1;
            }
            line += string(spaceCount, ' ');
          }
        }
      }

      res.emplace_back(std::move(line));
    }

    return res;
  }
};
