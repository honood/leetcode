// HoNooD
// 2022.09.07 02:58

// https://en.wikipedia.org/wiki/Selection_sort
// https://en.wikipedia.org/wiki/Sorting_algorithm

#include <iostream>
#include <vector>
#include <utility> // for `std::swap` or <algorithm>

void selection_sort(std::vector<int>& vi) {
  if (vi.empty()) {
    return;
  }

  for (int i = 0; i < vi.size() - 1; ++i) {
    int j_min = i;

    for (int j = i + 1; j < vi.size(); ++j) {
      if (vi[j_min] > vi[j]) {
        j_min = j;
      }
    }

    if (i != j_min) {
      std::swap(vi[i], vi[j_min]);
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
  selection_sort(vi);
  show(vi); // 1 2 3 5 6 8 9 

  return 0;
}
