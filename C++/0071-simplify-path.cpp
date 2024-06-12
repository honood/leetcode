// HoNooD <honood@gmail.com>
// 2024.06.12 13:53

// 71. Simplify Path
// https://leetcode.com/problems/simplify-path/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  string simplifyPath(string path) {
    assert(!path.empty() && path[0] == '/');

    // Using `std::vector` instead of `std::stack` allows easier access and
    // iteration, making it more flexible for this task."
    vector<string> pathComponents{};
    int pos = 1;
    while (pos < path.size()) {
      int found = path.find('/', pos);
      string&& segment = path.substr(pos, (found == path.npos ? path.size() : found) - pos);
      if (segment == "..") {
        if (!pathComponents.empty()) {
          pathComponents.pop_back();
        }
      } else if (segment != "." && !segment.empty()) {
        pathComponents.emplace_back(segment);
      }

      if (found == path.npos) {
        break;
      }

      pos = found + 1;
    }

    string res{'/'};
    for (int i = 0; i < pathComponents.size(); ++i) {
      res += pathComponents[i];
      if (i != pathComponents.size() - 1) {
        res += '/';
      }
    }

    return res;
  }
};

// Use `std::istringstream` and `std::getline`
class Solution_2 {
public:
  string simplifyPath(string path) {
    assert(!path.empty() && path[0] == '/');

    // Using `std::vector` instead of `std::stack` allows easier access and
    // iteration, making it more flexible for this task."
    vector<string> pathComponents{};
    // `std::stringstream` is also suitable.
    istringstream ss{path};
    string token{};
    // https://en.cppreference.com/w/cpp/io/basic_ios/operator_bool
    while (std::getline(ss, token, '/')) {
      if (token == "." || token.empty()) {
        continue;
      }

      if (token == "..") {
        if (!pathComponents.empty()) {
          pathComponents.pop_back();
        }
      } else {
        pathComponents.emplace_back(token);
      }
    }

    string res{'/'};
    for (int i = 0; i < pathComponents.size(); ++i) {
      res += pathComponents[i];
      if (i != pathComponents.size() - 1) {
        res += '/';
      }
    }

    return res;
  }
};
