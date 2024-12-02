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

bool is_report_safe(std::vector<int> &levels) {
  Direction direction;
  if (levels[0] < levels[1]) {
    direction = Direction::Increasing;
  } else if (levels[0] > levels[1]) {
    direction = Direction::Decreasing;
  } else {
    return false;
  }

  int idx = 0;
  for (; idx < levels.size() - 1; idx++) {
    if (direction == Direction::Increasing && levels[idx] >= levels[idx + 1]) {
      break;
    }
    if (direction == Direction::Decreasing && levels[idx] <= levels[idx + 1]) {
      break;
    }
    if (abs(levels[idx] - levels[idx + 1]) > 3) {
      break;
    }
  }

  if (idx == levels.size() - 1) {
    return true;
  }

  return false;
}

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
    if (is_report_safe(it->levels)) {
      safe_count += 1;
      continue;
    }

    for (int i = 0; i < it->levels.size(); i++) {
      auto new_levels = it->levels;
      new_levels.erase(new_levels.begin() + i);

      if (is_report_safe(new_levels)) {
        safe_count += 1;
        break;
      }
    }
  }

  std::cout << safe_count << std::endl;
}
