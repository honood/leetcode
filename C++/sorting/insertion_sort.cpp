// HoNooD
// 2022.09.07 02:33

// https://en.wikipedia.org/wiki/Insertion_sort
// https://en.wikipedia.org/wiki/Sorting_algorithm

#include <iostream>
#include <vector>

void insertion_sort(std::vector<int>& vi) {
  if (vi.empty()) {
    return;
  }

  for (int i = 1; i < vi.size(); ++i) {
    int key = vi[i];

    int j = i - 1;
    while (j >= 0 && key < vi[j]) {
      vi[j + 1] = vi[j];
      --j;
    }

    vi[j + 1] = key;
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
  insertion_sort(vi);
  show(vi); // 1 2 3 5 6 8 9 

  return 0;
}
