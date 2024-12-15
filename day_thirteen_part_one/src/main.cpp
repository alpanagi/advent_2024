#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

struct Vector {
  int x;
  int y;
};

struct Machine {
  Vector button_a;
  Vector button_b;
  Vector prize;
};

std::vector<Machine> read_input_file() {
  std::regex button_regex("^Button [AB]: X\\+(\\d+), Y\\+(\\d+)$");
  std::regex prize_regex("^Prize: X=(\\d+), Y=(\\d+)$");
  std::smatch matches;

  std::vector<Machine> machines;

  std::string line;
  std::ifstream input_file("../input");
  while (std::getline(input_file, line)) {
    std::regex_match(line, matches, button_regex);
    Vector button_a = {atoi(matches[1].str().c_str()),
                       atoi(matches[2].str().c_str())};

    std::getline(input_file, line);
    std::regex_match(line, matches, button_regex);
    Vector button_b = {atoi(matches[1].str().c_str()),
                       atoi(matches[2].str().c_str())};

    std::getline(input_file, line);
    std::regex_match(line, matches, prize_regex);
    Vector prize = {atoi(matches[1].str().c_str()),
                    atoi(matches[2].str().c_str())};

    machines.push_back(
        Machine{.button_a = button_a, .button_b = button_b, .prize = prize});

    // Empty line
    std::getline(input_file, line);
  }

  return machines;
}

int calculate_cost(Machine m) {
  for (int i = 100; i >= 0; i--) {
    if (m.button_a.x * i > m.prize.x) {
      continue;
    }

    for (int j = 0; j <= 100; j++) {
      if (m.button_a.x * i + m.button_b.x * 100 < m.prize.x) {
        return 0;
      }

      if (m.button_a.x * i + m.button_b.x * j > m.prize.x) {
        break;
      }

      if (m.button_a.x * i + m.button_b.x * j == m.prize.x &&
          m.button_a.y * i + m.button_b.y * j == m.prize.y) {
        return i * 3 + j * 1;
      }
    }
  }

  return 0;
}

int main() {
  std::vector<Machine> machines = read_input_file();

  int acc = 0;
  for (auto el : machines) {
    acc += calculate_cost(el);
  }

  std::cout << acc << std::endl;
}
