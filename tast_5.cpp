#include "tasks.h"
#include <sstream>



std::vector<unsigned int> decode_line(std::string line) {
    unsigned int elements, from, into;
    std::string numbers;
    std::stringstream ss;
  for (std::string::iterator i = line.begin(); i != line.end(); i++) {
      if (int(*i) <= 57) numbers.push_back(*i); // digits (and whitespace) in my charset (ASCII) are before letters! 0-9 ->48-57
  }
  ss << numbers;
  ss >> elements >> from >> into;
  return std::vector<unsigned int>{elements, from, into};
}

void move_elements_1(unsigned int elements, unsigned int from, unsigned int into,
                   std::vector<std::vector<char>> &stacks) {

  for (unsigned int i = 0; i < elements; ++i) {
    stacks[into - 1].push_back(stacks[from - 1].back());
    stacks[from - 1].pop_back();
  }

}

void move_elements_2(unsigned int elements, unsigned int from,
                     unsigned int into,
                     std::vector<std::vector<char>> &stacks) {
  std::vector<char> buffor;
  for (unsigned int i = 0; i < elements and not stacks[from - 1].empty(); ++i) {
    buffor.push_back(stacks[from - 1].back());
    stacks[from - 1].pop_back();
  }
  size_t buff_size = buffor.size();
  for (unsigned int j = 0; j < buff_size; ++j) {
    stacks[into - 1].push_back(buffor.back());
    buffor.pop_back();
  }
}

void task5(std::string filename) {
  std::fstream file;
  // A-Z => 65-90
  // a-z => 97-122

  file.open(
      filename,
      std::ios::in);  // open a file to perform read operation using file object
  if (file.is_open()) {  // checking whether the file is open
    std::string tp;
    unsigned int columns(0);
    std::vector<std::vector<char>> all_stacks;
    while (getline(file, tp) and tp[1] != '1') {
      columns = (tp.length() + 1) / 4;
      if (all_stacks.empty()) all_stacks = std::vector<std::vector<char>>{columns};
      for (unsigned int col = 0; col < columns; ++col)
        if (tp[col * 4 + 1] != ' ') all_stacks[col].insert(all_stacks[col].begin(), tp[col * 4 + 1]);
    }
    getline(file, tp);
    getline(file, tp);
    std::vector<unsigned int> operation_code;
    while (getline(file, tp)) {
      operation_code = decode_line(tp);
      move_elements_2(operation_code[0], operation_code[1], operation_code[2], all_stacks);

    }
    std::cout << "Result: ";
    for (unsigned int n = 0; n < columns; ++n) std::cout << all_stacks[n].back();

    file.close();
  }
}
