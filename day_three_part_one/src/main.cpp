#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

int main() {
  std::regex parser_regex("mul\\((\\d{1,3}),(\\d{1,3})\\)");
  std::smatch matches;

  std::string line;
  std::ifstream input_file("../input");

  int acc = 0;
  while (std::getline(input_file, line)) {
    auto begin = line.cbegin();
    while (std::regex_search(begin, line.cend(), matches, parser_regex)) {
      acc += atoi(matches[1].str().c_str()) * atoi(matches[2].str().c_str());
      begin = matches.suffix().first;
    }
  }

  std::cout << acc << std::endl;
}
