// HoNooD <honood@gmail.com>
// 2024.06.20 14:30

#pragma once

#include <chrono>
#include <iostream>

class Timer {
public:
  /**
   * @brief Measures the execution time of a callable object.
   *
   * This function measures the execution time of a function or a lambda expression.
   * It can optionally print the elapsed time with a provided label.
   *
   * @tparam Print A boolean template parameter that determines whether the elapsed time
   *               should be printed. Defaults to false.
   * @tparam Func The type of the callable object (function or lambda).
   * @tparam Args The types of the arguments to be passed to the callable object.
   *
   * @param label A string label used for printing the elapsed time, if Print is true.
   * @param func The callable object whose execution time is to be measured.
   * @param args The arguments to be passed to the callable object.
   *
   * @return The execution time of the callable object in milliseconds (ms) as a double.
   */
  template<bool Print = false, typename Func, typename... Args>
  static double measure(std::string const& label, Func&& func, Args&&... args) {
    auto start = std::chrono::high_resolution_clock::now();
    std::forward<Func>(func)(std::forward<Args>(args)...);
    auto end = std::chrono::high_resolution_clock::now();
    double duration_ms = std::chrono::duration<double, std::milli>(end - start).count();

    if constexpr (Print) {
      std::cout << label << ": " << duration_ms << " ms" << std::endl;
    }

    return duration_ms;
  }

  Timer() : start_{std::chrono::high_resolution_clock::now()}, end_{start_}, running_{true} {}

  void start() {
    start_ = std::chrono::high_resolution_clock::now();
    running_ = true;
  }

  void stop() {
    end_ = std::chrono::high_resolution_clock::now();
    running_ = false;
  }

  [[nodiscard]] long long elapsed_ns() const {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed()).count();
  }

  [[nodiscard]] long long elapsed_us() const {
    return std::chrono::duration_cast<std::chrono::microseconds>(elapsed()).count();
  }

  [[nodiscard]] long long elapsed_ms() const {
    return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed()).count();
  }

  [[nodiscard]] long long elapsed_s() const {
    return std::chrono::duration_cast<std::chrono::seconds>(elapsed()).count();
  }

  void print(const std::string& label) const {
    std::cout << label << ": "
      << elapsed_ns() << " ns | "
      << elapsed_us() << " µs | "
      << elapsed_ms() << " ms | "
      << elapsed_s() << " s"
      << std::endl;
  }

  [[nodiscard]] double elapsed_ns_f() const {
    return std::chrono::duration<double, std::nano>(elapsed()).count();
  }

  [[nodiscard]] double elapsed_us_f() const {
    return std::chrono::duration<double, std::micro>(elapsed()).count();
  }


  [[nodiscard]] double elapsed_ms_f() const {
    return std::chrono::duration<double, std::milli>(elapsed()).count();
  }

  [[nodiscard]] double elapsed_s_f() const {
    return std::chrono::duration<double>(elapsed()).count();
  }

  void print_f(const std::string& label) const {
    std::cout << label << ": "
      << elapsed_ns_f() << " ns | "
      << elapsed_us_f() << " µs | "
      << elapsed_ms_f() << " ms | "
      << elapsed_s_f() << " s"
      << std::endl;
  }

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> start_;
  std::chrono::time_point<std::chrono::high_resolution_clock> end_;
  bool running_;

  [[nodiscard]] std::chrono::duration<double> elapsed() const {
    return (running_ ? std::chrono::high_resolution_clock::now() : end_) - start_;
  }
};

/*
#include <vector>
#include <numeric>

void exampleFunction() {
  std::vector<int> v(1000, 42);
  int sum = std::accumulate(v.begin(), v.end(), 0);
  std::cout << "Sum: " << sum << std::endl;
}

int main() {
  // Measure the execution time of exampleFunction without printing
  double duration_ms = Timer::measure("", exampleFunction);
  std::cout << "exampleFunction duration: " << duration_ms << " ms (not printed inside measure)" << std::endl;

  // Measure the execution time of a lambda without printing
  double lambda_duration_ms = Timer::measure<>("", []() {
    std::vector<int> v(1000, 42);
    int sum = std::accumulate(v.begin(), v.end(), 0);
    std::cout << "Sum: " << sum << std::endl;
  });
  std::cout << "Lambda duration: " << lambda_duration_ms << " ms (not printed inside measure)" << std::endl;

  // Measure the execution time of exampleFunction with printing
  Timer::measure<true>("exampleFunction duration", exampleFunction);

  // Measure the execution time of a lambda with printing
  Timer::measure<true>("Lambda duration", []() {
    std::vector<int> v(1000, 42);
    int sum = std::accumulate(v.begin(), v.end(), 0);
    std::cout << "Sum: " << sum << std::endl;
  });

  {
    Timer timer{};

    // Measure time taken by exampleFunction using manual start and stop
    timer.start();
    exampleFunction();
    timer.stop();
    timer.print("exampleFunction");

    // Measure time taken by a lambda using manual start and stop
    timer.start(); {
      std::vector<int> v(1000, 42);
      int sum = std::accumulate(v.begin(), v.end(), 0);
      std::cout << "Sum: " << sum << std::endl;
    }
    timer.stop();
    timer.print_f("Lambda");
  }

  return 0;
}
*/
