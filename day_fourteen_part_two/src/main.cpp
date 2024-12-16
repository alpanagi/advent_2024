#include <chrono>
#include <cmath>
#include <fstream>
#include <print>
#include <regex>
#include <thread>
#include <vector>

const int MAP_WIDTH = 101;
const int MAP_HEIGHT = 103;

struct Robot {
  std::pair<int, int> position;
  std::pair<int, int> velocity;
};

std::vector<Robot> parse_input() {
  std::vector<Robot> robots;

  std::regex parser(R"(p=(-?\d+),(-?\d+)\s+v=(-?\d+),(-?\d+))");
  std::smatch matches;

  std::string line;
  std::ifstream input_file("../input");
  while (std::getline(input_file, line)) {
    if (std::regex_match(line, matches, parser)) {
      Robot data;

      data.position = {std::stoi(matches[1].str()),
                       std::stoi(matches[2].str())};
      data.velocity = {std::stoi(matches[3].str()),
                       std::stoi(matches[4].str())};

      robots.push_back(data);
    }
  }

  return robots;
}

inline std::pair<int, int> move(const std::pair<int, int> &position,
                                const std::pair<int, int> &velocity) {
  return {((position.first + velocity.first + MAP_WIDTH) % MAP_WIDTH),
          ((position.second + velocity.second + MAP_HEIGHT) % MAP_HEIGHT)};
}

void print_map(const std::vector<Robot> &robots) {
  char map[MAP_HEIGHT][MAP_WIDTH];
  for (int row = 0; row < MAP_HEIGHT; row++) {
    for (int col = 0; col < MAP_WIDTH; col++) {
      map[row][col] = '.';
    }
  }

  for (auto el : robots) {
    map[el.position.second][el.position.first] = '*';
  }

  for (int row = 0; row < MAP_HEIGHT; row++) {
    for (int col = 0; col < MAP_WIDTH; col++) {
      std::print("{}", map[row][col]);
    }
    std::print("\n");
  }
}

int main() {
  std::vector<Robot> robots = parse_input();

  for (int iteration = 1; iteration < 1'000'000; iteration++) {
    for (Robot &robot : robots) {
      robot.position = move(robot.position, robot.velocity);
    }

    int dist = 0;
    for (int i = 1; i < robots.size(); i++) {
      int a = (robots[i - 1].position.first - robots[i].position.first);
      int b = (robots[i - 1].position.second - robots[i].position.second);
      dist += sqrt(a * a + b * b);
    }

    if (dist < 25000) {
      std::print("Iteration: {}\n", iteration);
      print_map(robots);
      std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
  }
}
