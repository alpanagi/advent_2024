#include "code.h"
#include <fstream>
#include <print>

int main() {
  std::ifstream input_file("../input");
  Map map = read_map(input_file);
  State state = initialize_state(map);
  auto result = find_path(state);
  std::print("{}\n", result);
}
