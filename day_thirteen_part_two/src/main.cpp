#include <fstream>
#include <print>
#include <regex>
#include <vector>

typedef long long bigint;

struct Vector {
  bigint x;
  bigint y;
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
    Vector button_a = {std::stoll(matches[1].str().c_str()),
                       std::stoll(matches[2].str().c_str())};

    std::getline(input_file, line);
    std::regex_match(line, matches, button_regex);
    Vector button_b = {std::stoll(matches[1].str().c_str()),
                       std::stoll(matches[2].str().c_str())};

    std::getline(input_file, line);
    std::regex_match(line, matches, prize_regex);
    Vector prize = {std::stoll(matches[1].str().c_str()) + 10000000000000,
                    std::stoll(matches[2].str().c_str()) + 10000000000000};

    machines.push_back(
        Machine{.button_a = button_a, .button_b = button_b, .prize = prize});

    // Empty line
    std::getline(input_file, line);
  }

  return machines;
}

bigint calculate_cost(Machine m) {
  bigint x00 = m.button_a.x;
  bigint x01 = m.button_b.x;
  bigint x10 = m.button_a.y;
  bigint x11 = m.button_b.y;
  bigint p0 = m.prize.x;
  bigint p1 = m.prize.y;

  if (x00 * x11 - x01 * x10 == 0) {
    return 0;
  }

  bigint f0 = (x11 * p0 - x01 * p1) / (x00 * x11 - x01 * x10);
  bigint f1 = (-x10 * p0 + x00 * p1) / (x00 * x11 - x01 * x10);

  if (f0 < 0 || f0 < 0 || f0 * x00 + f1 * x01 != p0 ||
      f0 * x10 + f1 * x11 != p1) {
    return 0;
  }

  return f0 * 3 + f1 * 1;
}

int main() {
  std::vector<Machine> machines = read_input_file();

  bigint acc = 0;
  for (auto el : machines) {
    acc += calculate_cost(el);
  }

  std::print("{}\n", acc);
}
