#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <vector>

int main() {
  std::regex parser_regex("^(\\d+)\\s+(\\d+)$");
  std::smatch matches;

  std::vector<int> list_a;
  std::map<int, int> map_b;

  std::ifstream file("../input");
  std::string line;
  while (std::getline(file, line)) {
    std::regex_match(line, matches, parser_regex);
    list_a.push_back(atoi(matches[1].str().c_str()));

    int location_id = atoi(matches[2].str().c_str());
    auto iterator = map_b.find(location_id);
    if (iterator == map_b.end()) {
      map_b.insert(std::pair<int, int>(location_id, 1));
    } else {
      iterator->second += 1;
    }
  }

  int acc = 0;
  for (int el : list_a) {
    auto iterator = map_b.find(el);
    if (iterator != map_b.end()) {
      acc += iterator->second * el;
    }
  }

  std::cout << acc << std::endl;
}
