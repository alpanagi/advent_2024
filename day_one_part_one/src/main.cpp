#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

int main() {
  std::regex parser_regex("^(\\d+)\\s+(\\d+)$");
  std::smatch matches;

  std::vector<int> list_a;
  std::vector<int> list_b;

  std::string line;
  std::ifstream input_file("../input");
  while (std::getline(input_file, line)) {
    if (std::regex_search(line, matches, parser_regex)) {
      list_a.push_back(atoi(matches[1].str().c_str()));
      list_b.push_back(atoi(matches[2].str().c_str()));
    }
  }

  std::sort(list_a.begin(), list_a.end());
  std::sort(list_b.begin(), list_b.end());

  int acc = 0;
  for (int i = 0; i < list_a.size(); i++) {
    acc += std::abs(list_a[i] - list_b[i]);
  }

  std::cout << acc << std::endl;
}
