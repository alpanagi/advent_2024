#include <fstream>
#include <print>
#include <regex>
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

long count_robots_in_quadrants(const std::vector<Robot> &robots) {
  long top_left = 0;
  long top_right = 0;
  long bottom_left = 0;
  long bottom_right = 0;

  for (const Robot &robot : robots) {
    int x = robot.position.first;
    int y = robot.position.second;

    if (x == MAP_WIDTH / 2 || y == MAP_HEIGHT / 2) {
      continue;
    }

    if (x < MAP_WIDTH / 2 && y < MAP_HEIGHT / 2) {
      top_left++;
    } else if (x > MAP_WIDTH / 2 && y < MAP_HEIGHT / 2) {
      top_right++;
    } else if (x < MAP_WIDTH / 2 && y > MAP_HEIGHT / 2) {
      bottom_left++;
    } else if (x > MAP_WIDTH / 2 && y > MAP_HEIGHT / 2) {
      bottom_right++;
    }
  }

  return top_left * top_right * bottom_left * bottom_right;
}

int main() {
  std::vector<Robot> robots = parse_input();
  for (Robot &robot : robots) {
    for (int i = 0; i < 100; i++) {
      robot.position = move(robot.position, robot.velocity);
    }
  }

  std::print("{}\n", count_robots_in_quadrants(robots));
}
