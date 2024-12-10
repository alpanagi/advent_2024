#include <cmath>
#include <format>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

const int MAP_SIZE = 50;
const double EPSILON = 0.0000001;

struct Antenna {
  int row;
  int col;
  char val;
};

inline double distance(double row, double col, Antenna &antenna) {
  return std::sqrt((row - antenna.row) * (row - antenna.row) +
                   (col - antenna.col) * (col - antenna.col));
}

int main() {
  char map[MAP_SIZE][MAP_SIZE];

  std::string line;
  std::ifstream input_file("../input");
  int row = 0;
  while (std::getline(input_file, line)) {
    line.copy(map[row], MAP_SIZE);
    row++;
  }

  std::vector<Antenna> antennas;
  for (int row = 0; row < MAP_SIZE; row++) {
    for (int col = 0; col < MAP_SIZE; col++) {
      if (map[row][col] != '.') {
        antennas.push_back(Antenna{
            .row = row,
            .col = col,
            .val = map[row][col],
        });
      }
    }
  }

  std::set<int> locations;
  for (int row = 0; row < MAP_SIZE; row++) {
    for (int col = 0; col < MAP_SIZE; col++) {
      for (int i = 0; i < antennas.size(); i++) {
        for (int j = 0; j < antennas.size(); j++) {
          if (i == j) {
            continue;
          }

          double distance_i = distance(row, col, antennas[i]);
          double distance_j = distance(row, col, antennas[j]);
          double dot_prod = (antennas[i].row - row) * (antennas[j].row - row) +
                            (antennas[i].col - col) * (antennas[j].col - col);
          if (antennas[i].val == antennas[j].val && distance_i > EPSILON &&
              distance_j > EPSILON &&
              std::abs(distance_i - 2 * distance_j) < EPSILON &&
              std::abs(dot_prod - distance_i * distance_j) < EPSILON) {
            locations.insert(row * 1000 + col);
          }
        }
      }
    }
  }

  std::cout << locations.size() << std::endl;
}
