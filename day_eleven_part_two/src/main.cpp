#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

const int ITERATIONS = 75;

std::map<long, long> memo[76];

int main() {
  long number;
  std::ifstream input_file("../input");
  std::vector<long> stones;
  while (input_file >> number) {
    stones.push_back(number);
  }

  std::deque<std::pair<long, long>> search_space;
  for (auto el : stones) {
    search_space.push_back({el, ITERATIONS});
  }

  while (!search_space.empty()) {
    auto [stone, iteration] = search_space.front();
    search_space.pop_front();

    auto it = memo[iteration].find(stone);
    if (it != memo[iteration].end()) {
      continue;
    }

    if (iteration == 0) {
      memo[0].insert({stone, 1});
      continue;
    }

    if (stone == 0) {
      auto it = memo[iteration - 1].find(1);
      if (it != memo[iteration - 1].end()) {
        memo[iteration].insert({stone, it->second});
        continue;
      }

      search_space.push_front({stone, iteration});
      search_space.push_front({1, iteration - 1});
      continue;
    }

    std::string digits = std::to_string(stone);
    if (digits.size() % 2 == 0) {
      long side_1 = atol(digits.substr(0, digits.size() / 2).c_str());
      long side_2 = atol(digits.substr(digits.size() / 2).c_str());

      auto it_1 = memo[iteration - 1].find(side_1);
      auto it_2 = memo[iteration - 1].find(side_2);

      if (it_1 != memo[iteration - 1].end() &&
          it_2 != memo[iteration - 1].end()) {
        memo[iteration].insert({stone, it_1->second + it_2->second});
        continue;
      }

      search_space.push_front({stone, iteration});
      if (it_1 == memo[iteration - 1].end()) {
        search_space.push_front({side_1, iteration - 1});
      }

      if (it_2 == memo[iteration - 1].end()) {
        search_space.push_front({side_2, iteration - 1});
      }
      continue;
    }

    it = memo[iteration - 1].find(stone * 2024);
    if (it != memo[iteration - 1].end()) {
      memo[iteration].insert({stone, it->second});
      continue;
    }

    search_space.push_front({stone, iteration});
    search_space.push_front({stone * 2024, iteration - 1});
  }

  long count = 0;
  for (auto el : stones) {
    auto it = memo[ITERATIONS].find(el);
    count += it->second;
  }

  std::cout << count << std::endl;
}
