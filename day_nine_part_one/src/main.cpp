#include <fstream>
#include <iostream>
#include <variant>
#include <vector>

struct File {
  int id;
};

struct Space {};

using Position = std::variant<File, Space>;

int main() {
  std::string input;
  std::ifstream input_file("../input");
  std::getline(input_file, input);

  int id = 0;
  std::vector<Position> positions;
  for (int i = 0; i < input.size(); i++) {
    if (i % 2 == 0) {
      for (int j = 0; j < input[i] - '0'; j++) {
        positions.push_back(File{.id = id});
      }
      id++;
    } else {
      for (int j = 0; j < input[i] - '0'; j++) {
        positions.push_back(Space{});
      }
    }
  }

  auto it = 0;
  auto rit = positions.size() - 1;
  while (it < rit) {
    while (std::holds_alternative<File>(positions[it])) {
      it++;
    }

    while (std::holds_alternative<Space>(positions[rit])) {
      rit--;
    }

    if (it >= rit) {
      break;
    }

    auto temp = positions[it];
    positions[it] = positions[rit];
    positions[rit] = temp;
  }

  long sum = 0;
  for (int i = 0; i < positions.size(); i++) {
    if (std::holds_alternative<File>(positions[i])) {
      auto file = std::get<File>(positions[i]);
      sum += file.id * i;
    }
  }

  std::cout << sum << std::endl;
}
