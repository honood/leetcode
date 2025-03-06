// HoNooD
// 2022.09.08 21:59

// https://en.wikipedia.org/wiki/Merge_sort
// https://en.wikipedia.org/wiki/Sorting_algorithm

#include <iostream>
#include <vector>

std::vector<int> merge(std::vector<int> const& sorted_left,
                       std::vector<int> const& sorted_right) {
  if (sorted_left.empty()) {
    return sorted_right;
  }

  if (sorted_right.empty()) {
    return sorted_left;
  }

  std::vector<int> result{};
  result.reserve(sorted_left.size() + sorted_right.size());

  auto sl_it = sorted_left.cbegin();
  auto sr_it = sorted_right.cbegin();
  while (sl_it != sorted_left.cend() || sr_it != sorted_right.cend()) {
    if (sl_it == sorted_left.cend()) {
      result.push_back(*sr_it++);
    } else if (sr_it == sorted_right.cend()) {
      result.push_back(*sl_it++);
    } else {
      if (*sl_it < *sr_it) {
        result.push_back(*sl_it++);
      } else if (*sl_it > *sr_it) {
        result.push_back(*sr_it++);
      } else {
        result.push_back(*sl_it++);
        result.push_back(*sr_it++);
      }
    }
  }

  return std::move(result);
}

std::vector<int> merge_sort(std::vector<int> const& vi) {
  if (vi.empty() || vi.size() == 1U) {
    return vi;
  }

  auto mid = vi.size() / 2;
  std::vector<int> left{vi.cbegin(), vi.cbegin() + mid};
  std::vector<int> right{vi.cbegin() + mid, vi.end()};

  auto sorted_left = merge_sort(left);
  auto sorted_right = merge_sort(right);

  return std::move(merge(sorted_left, sorted_right));
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
  show(merge_sort(vi)); // 1 2 3 5 6 8 9

  return 0;
}
