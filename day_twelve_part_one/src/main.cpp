#include <deque>
#include <fstream>
#include <iostream>
#include <set>

const int MAP_SIZE = 140;
const std::pair<int, int> directions[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

char map[MAP_SIZE][MAP_SIZE];
std::set<int> visited;

int flood_region(int row, int col) {
  char id = map[row][col];
  std::deque<std::pair<int, int>> search_space{{row, col}};

  int area = 0;
  int perimeter = 0;
  while (!search_space.empty()) {
    auto [row, col] = search_space.front();
    search_space.pop_front();

    if (visited.contains(row * 100000 + col)) {
      continue;
    }

    visited.insert(row * 100000 + col);
    area += 1;

    for (int i = 0; i < 4; i++) {
      if (row + directions[i].first < 0 ||
          row + directions[i].first == MAP_SIZE ||
          col + directions[i].second < 0 ||
          col + directions[i].second == MAP_SIZE) {
        perimeter += 1;
        continue;
      }

      if (map[row + directions[i].first][col + directions[i].second] != id) {
        perimeter += 1;
      } else {
        search_space.push_back(
            {row + directions[i].first, col + directions[i].second});
      }
    }
  }

  return area * perimeter;
}

int main() {
  std::string line;
  std::ifstream input_file("../input");
  int row = 0;
  while (std::getline(input_file, line)) {
    line.copy(map[row], MAP_SIZE);
    row++;
  }

  int acc = 0;
  for (int row = 0; row < MAP_SIZE; row++) {
    for (int col = 0; col < MAP_SIZE; col++) {
      if (visited.contains(row * 100000 + col)) {
        continue;
      }

      acc += flood_region(row, col);
    }
  }

  std::cout << acc << std::endl;
}
