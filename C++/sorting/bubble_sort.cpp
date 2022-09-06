// HoNooD
// 2022.09.07 01:37

// https://en.wikipedia.org/wiki/Bubble_sort
// https://en.wikipedia.org/wiki/Sorting_algorithm

#include <iostream>
#include <vector>
#include <utility> // for `std::swap` or <algorithm>

void bubble_sort(std::vector<int>& vi) {
  if (vi.empty()) {
    return;
  }

  for (int i = 0; i < vi.size(); ++i) {
    for (int j = i + 1; j < vi.size(); ++j) {
      if (vi[i] > vi[j]) {
        std::swap(vi[i], vi[j]);
      }
    }
  }
}

void show(std::vector<int> const& vi) {
  for (auto const& i: vi) {
    std::cout << i << ' ';
  }
  std::cout << '\n';
}

int main() {
  std::vector<int> vi{6, 2, 5, 8, 1, 3, 9};
  show(vi); // 6 2 5 8 1 3 9
  bubble_sort(vi);
  show(vi); // 1 2 3 5 6 8 9

  return 0;
}
