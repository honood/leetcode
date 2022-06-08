// HoNooD
// 2022.06.09 02:40

#include <iostream>
#include <type_traits>
#include <array>
#include <vector>
#include <cstdlib>

int main(int argc, char* argv[]) {
  int const num_rows = 2;
  int const num_cols = 3;

  {
    std::cout << "sizeof(int) = " << sizeof(int) << '\n';

    static_assert(sizeof(int[num_cols]) == (sizeof(int) * num_cols));
    {
      std::cout << "sizeof(int[" << num_cols << "]) = "
                << sizeof(int[num_cols]) << '\n';
      std::cout << "sizeof(int) * " << num_cols << " = "
                << sizeof(int) * num_cols << '\n';
    }

    static_assert(sizeof(int[num_rows][num_cols]) == (sizeof(int) * num_cols * num_rows));
    {
      std::cout << "sizeof(int[" << num_rows << "][" << num_cols << "]) = "
                << sizeof(int[num_rows][num_cols]) << '\n';
      std::cout << "sizeof(int) * " << num_cols << " * " << num_rows << " = "
                << sizeof(int) * num_cols * num_rows << '\n';
    }

    std::cout << '\n';
  }

  {
    std::vector<std::vector<int>> two_d_array(num_rows, std::vector<int>(num_cols, 0));

    int initial = 0;

    // for (int i = 0; i < num_rows; ++i) {
    //   for (int j = 0; j < num_cols; ++j) {
    //     two_d_array[i][j] = ++initial;
    //   }
    // }

    for (auto& row: two_d_array) {
      for (auto& e: row) {
        e = ++initial;
      }
    }

    for (auto const& arr: two_d_array) {
      for (auto const& e: arr) {
        std::cout << e << " ";
      }
      std::cout << '\n';
    }

    std::cout << '\n';
  }

  {
    std::array<std::array<int, num_cols>, num_rows> two_d_array{};

    int initial = 0;

    // for (int i = 0; i < num_rows; ++i) {
    //   for (int j = 0; j < num_cols; ++j) {
    //     two_d_array[i][j] = ++initial;
    //   }
    // }

    for (auto& row: two_d_array) {
      for (auto& e: row) {
        e = ++initial * 10;
      }
    }

    for (auto const& arr: two_d_array) {
      for (auto const& e: arr) {
        std::cout << e << " ";
      }
      std::cout << '\n';
    }

    std::cout << '\n';
  }

  {
    int (*two_d_array)[num_cols] = new int[num_rows][num_cols];

    int initial = 0;
    for (int i = 0; i < num_rows; ++i) {
      for (int j = 0; j < num_cols; ++j) {
        two_d_array[i][j] = ++initial * 100;
      }
    }

    for (int i = 0; i < num_rows; ++i) {
      for (int j = 0; j < num_cols; ++j) {
        std::cout << two_d_array[i][j] << " ";
      }
      std::cout << '\n';
    }

    {
      using array_t = int[num_cols];
      static_assert(std::is_same_v<decltype(two_d_array), array_t*>);
      static_assert(std::is_same_v<std::decay_t<decltype(*two_d_array)>, std::decay_t<array_t>>);
      static_assert(std::is_same_v<std::decay_t<array_t>, int*>);

      // 2D-array -> 1D-array
      int* one_d_array = *two_d_array;
      for (int i = 0; i < num_cols * num_rows; ++i) {
        std::cout << one_d_array[i] << " ";
      }
      std::cout << '\n';
    }

    std::cout << '\n';

    delete[] two_d_array;
  }

  {
    std::size_t size = sizeof(int[num_rows][num_cols]);
    int* one_d_array = static_cast<int*>(std::malloc(size));

    int initial = 0;
    for (int i = 0; i < num_cols * num_rows; ++i) {
      one_d_array[i] = ++initial * 1000;
    }

    // 1D-array -> 2D-array
    int (*two_d_array)[num_cols] = reinterpret_cast<int (*)[num_cols]>(one_d_array);
    for (int i = 0; i < num_rows; ++i) {
      for (int j = 0; j < num_cols; ++j) {
        std::cout << two_d_array[i][j] << " ";
      }
      std::cout << '\n';
    }

    {
      for (int i = 0; i < num_cols * num_rows; ++i) {
        std::cout << one_d_array[i] << " ";
      }
      std::cout << '\n';
    }

    std::cout << '\n';

    std::free(one_d_array);
  }

  {
    std::size_t size = sizeof(int) * num_cols * num_rows;
    int* one_d_array = reinterpret_cast<int*>(std::malloc(size));
    int* simulated_2d_array = one_d_array;

    int initial = 0;
    for (int i = 0; i < num_rows; ++i) {
      for (int j = 0; j < num_cols; ++j) {
        simulated_2d_array[num_cols * i + j] = ++initial * 10000;
      }
    }

    for (int i = 0; i < num_rows; ++i) {
      for (int j = 0; j < num_cols; ++j) {
        std::cout << simulated_2d_array[i * num_cols + j] << " ";
      }
      std::cout << '\n';
    }

    {
      for (int i = 0; i < num_cols * num_rows; ++i) {
        std::cout << one_d_array[i] << " ";
      }
      std::cout << '\n';
    }

    std::cout << '\n';

    std::free(one_d_array);
  }

  return 0;
}

// sizeof(int) = 4
// sizeof(int[3]) = 12
// sizeof(int) * 3 = 12
// sizeof(int[2][3]) = 24
// sizeof(int) * 3 * 2 = 24
//
// 1 2 3
// 4 5 6
//
// 10 20 30
// 40 50 60
//
// 100 200 300
// 400 500 600
// 100 200 300 400 500 600
//
// 1000 2000 3000
// 4000 5000 6000
// 1000 2000 3000 4000 5000 6000
//
// 10000 20000 30000
// 40000 50000 60000
// 10000 20000 30000 40000 50000 60000

// Other references:
// 
// 1. [How to dynamically allocate a 2D array in C?](https://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/)
// 2. [new expression - cppreference.com](https://en.cppreference.com/w/cpp/language/new#Explanation)
