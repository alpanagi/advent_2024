#include <fstream>
#include <iostream>
#include <vector>

std::vector<long> iteration(const std::vector<long> &stones) {
  std::vector<long> result;

  for (auto stone : stones) {
    if (stone == 0) {
      result.push_back(1);
      continue;
    }

    std::string digits = std::to_string(stone);
    if (digits.size() % 2 == 0) {
      result.push_back(std::atol(digits.substr(0, digits.size() / 2).c_str()));
      result.push_back(std::atol(digits.substr(digits.size() / 2).c_str()));
      continue;
    }

    result.push_back(stone * 2024);
  }

  return result;
}

int main() {
  long number;
  std::ifstream input_file("../input");

  std::vector<long> stones;
  while (input_file >> number) {
    stones.push_back(number);
  }

  for (int i = 0; i < 25; i++) {
    stones = iteration(stones);
  }

  std::cout << stones.size() << std::endl;
}
