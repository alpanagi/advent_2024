#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

struct Report {
  std::vector<int> levels;
};

enum class Direction {
  Increasing,
  Decreasing,
};

int main() {
  std::regex parser_regex("(\\d+)");
  std::smatch matches;

  std::vector<Report> reports;

  std::string line;
  std::ifstream input("../input");
  while (std::getline(input, line)) {
    Report report;

    std::string::const_iterator begin = line.cbegin();
    while (std::regex_search(begin, line.cend(), matches, parser_regex)) {
      report.levels.push_back(atoi(matches[0].str().c_str()));
      begin = matches.suffix().first;
    }

    reports.push_back(report);
  }

  int safe_count = 0;
  for (auto it = reports.begin(); it != reports.end(); it++) {
    Direction direction;
    if (it->levels[0] < it->levels[1]) {
      direction = Direction::Increasing;
    } else if (it->levels[0] > it->levels[1]) {
      direction = Direction::Decreasing;
    } else {
      continue;
    }

    int idx = 0;
    for (; idx < it->levels.size() - 1; idx++) {
      if (direction == Direction::Increasing &&
          it->levels[idx] >= it->levels[idx + 1]) {
        break;
      }
      if (direction == Direction::Decreasing &&
          it->levels[idx] <= it->levels[idx + 1]) {
        break;
      }
      if (abs(it->levels[idx] - it->levels[idx + 1]) > 3) {
        break;
      }
    }

    if (idx == it->levels.size() - 1) {
      safe_count += 1;
    }
  }

  std::cout << safe_count << std::endl;
}
