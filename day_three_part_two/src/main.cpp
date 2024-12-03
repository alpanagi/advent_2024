#include <fstream>
#include <iostream>
#include <regex>

int main() {
  std::regex parser_regex(
      "(mul\\((\\d{1,3}),(\\d{1,3})\\)|do\\(\\)|don't\\(\\))");
  std::smatch matches;

  std::string line;
  std::ifstream input_file("../input");

  int acc = 0;
  bool should_calculate = true;
  while (std::getline(input_file, line)) {
    auto begin = line.cbegin();
    while (std::regex_search(begin, line.cend(), matches, parser_regex)) {
      if (matches[1] == "do()") {
        should_calculate = true;
      } else if (matches[1] == "don't()") {
        should_calculate = false;
      } else {
        if (should_calculate == true) {
          acc +=
              atoi(matches[2].str().c_str()) * atoi(matches[3].str().c_str());
        }
      }
      begin = matches.suffix().first;
    }
  }

  std::cout << acc << std::endl;
}
