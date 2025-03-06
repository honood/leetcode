// HoNooD <honood@gmail.com>
// 2025.02.20 08:30

// 605. Can Place Flowers
// https://leetcode.com/problems/can-place-flowers/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  bool canPlaceFlowers(vector<int>& flowerbed, int n) {
    if (n <= 0) {
      return true;
    }

    // if `flowerbed` is not mutable
    /*
    int i = 0;
    int size = flowerbed.size();
    while (n > 0 && i < size) {
      if (flowerbed[i] == 1) {
        i += 2;
        continue;
      }

      if (i - 1 >= 0 && flowerbed[i - 1] == 1) {
        ++i;
        continue;
      }

      if (i + 1 < size && flowerbed[i + 1] == 1) {
        i += 3;
        continue;
      }

      --n;
      i += 2;
    }
    return n == 0;
    */

    // if `flowerbed` is mutable:
    int size = flowerbed.size();
    for (int i = 0; i < size; ++i) {
      if (flowerbed[i] == 0
          && (i == 0 || flowerbed[i - 1] == 0)
          && (i == size - 1 || flowerbed[i + 1] == 0)) {
        flowerbed[i] = 1;
        --n;
        if (n == 0) {
          return true;
        }
      }
    }
    return n == 0;
  }
};
