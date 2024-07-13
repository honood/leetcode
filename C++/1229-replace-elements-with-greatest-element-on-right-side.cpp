// HoNooD <honood@gmail.com>
// 2024.07.13 13:39

// 1299. Replace Elements with Greatest Element on Right Side
// https://leetcode.com/problems/replace-elements-with-greatest-element-on-right-side/description/

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  vector<int> replaceElements(vector<int>& arr) {
    if (arr.empty()) {
      return arr;
    }

    int n = arr.size();
    int right_max = arr[n - 1];
    arr[n - 1] = -1;

    for (int i = n - 2; i >= 0; --i) {
      int curr = arr[i];
      arr[i] = right_max;
      right_max = std::max(right_max, curr);
    }

    return arr;
  }
};
