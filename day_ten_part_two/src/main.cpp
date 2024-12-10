#include <deque>
#include <fstream>
#include <iostream>
#include <vector>

const int MAP_SIZE = 59;

struct Tile {
  int row;
  int col;
  int val;
};
Tile tiles[MAP_SIZE][MAP_SIZE];

int main() {
  std::string line;
  std::ifstream input_file("../input");
  for (int row = 0; row < MAP_SIZE; row++) {
    std::getline(input_file, line);
    for (int col = 0; col < MAP_SIZE; col++) {
      tiles[row][col] = Tile{
          .row = row,
          .col = col,
          .val = line[col] - '0',
      };
    }
  }

  std::vector<Tile> trailheads;
  for (int row = 0; row < MAP_SIZE; row++) {
    for (int col = 0; col < MAP_SIZE; col++) {
      if (tiles[row][col].val == 0) {
        trailheads.push_back(tiles[row][col]);
      }
    }
  }

  const std::pair<int, int> directions[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

  int acc = 0;
  for (Tile trailhead : trailheads) {
    int count = 0;

    std::deque<Tile> search_space = {trailhead};
    while (!search_space.empty()) {
      auto el = search_space.front();
      search_space.pop_front();

      for (auto [i, j] : directions) {
        int row = el.row + i;
        int col = el.col + j;

        if (row < 0 || row == MAP_SIZE || col < 0 || col == MAP_SIZE) {
          continue;
        }

        if (el.val == 8 && tiles[row][col].val == 9) {
          count++;
          continue;
        }

        if (el.val + 1 == tiles[row][col].val) {
          search_space.push_front(tiles[row][col]);
        }
      }
    }

    acc += count;
  }

  std::cout << acc << std::endl;
}
