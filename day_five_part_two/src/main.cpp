#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

std::map<std::string, std::vector<std::string>> rules;
std::vector<std::vector<std::string>> updates;

void read_rule(const std::string &line) {
  std::string key_page = line.substr(0, 2);

  if (rules.contains(key_page)) {
    auto entry = rules.find(key_page);
    entry->second.push_back(line.substr(3));
  } else {
    rules.insert({key_page, {line.substr(3)}});
  }
}

void read_update(const std::string &line) {
  std::stringstream ss(line);

  std::string page;
  std::vector<std::string> update;
  while (std::getline(ss, page, ',')) {
    update.push_back(page);
  }

  updates.push_back(update);
}

bool is_valid_update(const std::vector<std::string> &update) {
  std::map<std::string, int> indices;
  for (int i = 0; i < update.size(); i++) {
    indices.insert({update[i], i});
  }

  for (auto page : update) {
    int page_idx = indices.find(page)->second;

    if (rules.contains(page)) {
      auto rule = rules.find(page);
      for (auto el : rule->second) {
        auto it = indices.find(el);
        if (it != indices.end() && it->second < page_idx) {
          return false;
        }
      }
    }
  }

  return true;
}

void fix_update(std::vector<std::string> &update) {
  for (int i = 1; i < update.size(); i++) {
    if (rules.contains(update[i])) {
      auto rule = rules.find(update[i]);
      for (int j = 0; j < i; j++) {
        if (std::find(rule->second.begin(), rule->second.end(), update[j]) !=
            rule->second.end()) {
          std::string temp = update[i];
          update.erase(update.begin() + i);
          update.insert(update.begin() + j, temp);
          break;
        }
      }
    }
  }
}

inline int find_middle(const std::vector<std::string> &update) {
  return atoi(update[update.size() / 2].c_str());
}

int main() {
  auto parser = &read_rule;

  std::string line;
  std::ifstream input_file("../input");
  while (std::getline(input_file, line)) {
    if (line == "") {
      parser = &read_update;
      continue;
    }

    parser(line);
  }

  int acc = 0;
  for (auto update : updates) {
    if (!is_valid_update(update)) {
      fix_update(update);
      acc += find_middle(update);
    }
  }

  std::cout << acc << std::endl;
}
