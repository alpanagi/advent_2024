#include <fstream>
#include <iostream>
#include <vector>

struct Position {
  long idx;
  long size;
  int id;
};

int main() {
  std::string input;
  std::ifstream input_file("../input");
  std::getline(input_file, input);

  int id = 0;
  long idx = 0;
  std::vector<Position> files;
  std::vector<Position> spaces;
  for (int i = 0; i < input.size(); i++) {
    long size = input[i] - '0';
    if (size == 0) {
      continue;
    }

    if (i % 2 == 0) {
      files.push_back(Position{.idx = idx, .size = size, .id = id});
      id++;
    } else {
      spaces.push_back(Position{.idx = idx, .size = size, .id = id});
    }

    idx += size;
  }

  for (int i = files.size() - 1; i >= 0; i--) {
    for (int j = 0; j < spaces.size(); j++) {
      Position &file = files[i];
      Position &space = spaces[j];

      if (space.idx > file.idx) {
        break;
      }

      if (file.size <= space.size) {
        file.idx = space.idx;
        space.size -= file.size;
        space.idx += file.size;
      }
    }
  }

  long sum = 0;
  for (int i = 0; i < files.size(); i++) {
    auto file = files[i];
    for (int i = 0; i < file.size; i++) {
      sum += file.id * (file.idx + i);
    }
  }

  std::cout << sum << std::endl;
}
