#include <deque>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

const int MAP_SIZE = 140;
const std::pair<int, int> directions[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

char map[MAP_SIZE + 2][MAP_SIZE + 2];
std::set<int> visited;

int calculate_perimeter(std::vector<std::pair<int, int>> tiles) {
  std::set<int> hashes;
  for (auto el : tiles) {
    hashes.insert(el.first * 100'000 + el.second);
  }

  int sides = 0;

  int is_new_side_top = true;
  int is_new_side_bottom = true;
  for (int row = 1; row < MAP_SIZE + 1; row++) {
    for (int col = 1; col < MAP_SIZE + 1; col++) {

      // Horizontal top sides
      if (!hashes.contains(row * 100'000 + col) ||
          hashes.contains((row - 1) * 100'000 + col)) {
        is_new_side_top = true;
      } else if (is_new_side_top) {
        sides += 1;
        is_new_side_top = false;
      }

      // Horizontal bottom sides
      if (!hashes.contains(row * 100'000 + col) ||
          hashes.contains((row + 1) * 100'000 + col)) {
        is_new_side_bottom = true;
      } else if (is_new_side_bottom) {
        sides += 1;
        is_new_side_bottom = false;
      }
    }
  }

  bool is_new_side_left = true;
  bool is_new_side_right = true;
  for (int col = 1; col < MAP_SIZE + 1; col++) {
    for (int row = 1; row < MAP_SIZE + 1; row++) {

      // Vertical left sides
      if (!hashes.contains(row * 100'000 + col) ||
          hashes.contains(row * 100'000 + (col - 1))) {
        is_new_side_left = true;
      } else if (is_new_side_left) {
        sides += 1;
        is_new_side_left = false;
      }

      // Vertical right sides
      if (!hashes.contains(row * 100'000 + col) ||
          hashes.contains(row * 100'000 + (col + 1))) {
        is_new_side_right = true;
      } else if (is_new_side_right) {
        sides += 1;
        is_new_side_right = false;
      }
    }
  }

  return sides;
}

int flood_region(int row, int col) {
  char id = map[row][col];
  std::deque<std::pair<int, int>> search_space{{row, col}};
  std::vector<std::pair<int, int>> tiles;

  int area = 0;
  int perimeter = 0;
  while (!search_space.empty()) {
    auto [row, col] = search_space.front();
    search_space.pop_front();

    if (visited.contains(row * 100'000 + col)) {
      continue;
    }

    tiles.push_back({row, col});
    visited.insert(row * 100'000 + col);
    area += 1;

    for (int i = 0; i < 4; i++) {
      if (row + directions[i].first < 1 ||
          row + directions[i].first == MAP_SIZE + 1 ||
          col + directions[i].second < 1 ||
          col + directions[i].second == MAP_SIZE + 1) {
        continue;
      }

      if (map[row + directions[i].first][col + directions[i].second] == id) {
        search_space.push_back(
            {row + directions[i].first, col + directions[i].second});
      }
    }
  }

  perimeter = calculate_perimeter(tiles);
  return area * perimeter;
}

int main() {
  std::string line;
  std::ifstream input_file("../input");
  int row = 1;
  while (std::getline(input_file, line)) {
    line.copy(&map[row][1], MAP_SIZE);
    row++;
  }

  // Draw a perimeter to ease caclulations
  for (int i = 0; i < MAP_SIZE + 2; i++) {
    map[0][i] = '#';
    map[i][0] = '#';
    map[MAP_SIZE + 1][i] = '#';
    map[i][MAP_SIZE + 1] = '#';
  }

  int acc = 0;
  for (int row = 1; row < MAP_SIZE + 1; row++) {
    for (int col = 1; col < MAP_SIZE + 1; col++) {
      if (visited.contains(row * 100'000 + col)) {
        continue;
      }

      acc += flood_region(row, col);
    }
  }

  std::cout << acc << std::endl;
}
