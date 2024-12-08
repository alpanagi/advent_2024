#include <fstream>
#include <functional>
#include <iostream>
#include <vector>

std::vector<std::function<long(long, long)>> operators = {
    [](long a, long b) { return a + b; }, [](long a, long b) { return a * b; }};

struct Equation {
  long result;
  std::vector<long> numbers;
};

std::vector<Equation> equations;

void parse_input() {
  std::string line;
  std::ifstream input_file("../input");
  while (std::getline(input_file, line)) {
    auto delimiter_pos = line.find(":");
    if (delimiter_pos == line.npos) {
      throw "Invalid input line";
    }

    Equation equation;
    equation.result = atol(line.substr(0, delimiter_pos).c_str());

    int start = delimiter_pos + 2;
    int next = start;
    while (next != line.npos) {
      next = line.find(' ', start);
      equation.numbers.push_back(
          atol(line.substr(start, next - start).c_str()));
      start = next + 1;
    }

    equations.push_back(equation);
  }
}

void next_operators(std::vector<long> &ops_idx) {
  int idx = 0;
  while (idx < ops_idx.size()) {
    if (ops_idx[idx] == operators.size() - 1) {
      ops_idx[idx] = 0;
      idx += 1;
    } else {
      ops_idx[idx] += 1;
      break;
    }
  }

  if (idx == ops_idx.size()) {
    ops_idx[idx - 1] = operators.size();
  }
}

bool is_valid(const Equation equation) {
  std::vector<long> ops_idx;
  for (int i = 0; i < equation.numbers.size() - 1; i++) {
    ops_idx.push_back(0);
  }

  while (ops_idx[ops_idx.size() - 1] < operators.size()) {
    long acc = operators[ops_idx[0]](equation.numbers[0], equation.numbers[1]);
    for (int i = 1; i < ops_idx.size(); i++) {
      acc = operators[ops_idx[i]](acc, equation.numbers[i + 1]);
    }

    if (acc == equation.result) {
      return true;
    }

    next_operators(ops_idx);
  }

  return false;
}

int main() {
  parse_input();
  long long acc = 0;
  for (auto equation : equations) {
    if (is_valid(equation)) {
      acc += equation.result;
    }
  }

  std::cout << acc << std::endl;
}
