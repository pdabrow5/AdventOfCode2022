#include "tasks.h"

typedef std::tuple<int, int> range;

std::vector<int> convert_str_to_ranges(std::string line) {
    std::string num, letter;
    int number;
    line.push_back('-');
    std::vector<int> numbers;
    for (std::string::const_iterator i = line.cbegin(); i != line.cend(); i++) {
      try {
        num.push_back(*i);
        letter.push_back(*i);
        std::stoi(letter);
      } catch (const std::invalid_argument&) {
        num.pop_back();
        number = std::stoi(num);
        numbers.push_back(number);
        num.clear();
      }
        letter.clear();
    }  
    return numbers;
}

void task4(std::string filename) {
  std::fstream file;
  // A-Z => 65-90
  // a-z => 97-122

  file.open(
      filename,
      std::ios::in);  // open a file to perform read operation using file object
  if (file.is_open()) {  // checking whether the file is open
    std::string tp;
    std::vector<int> numbers;
    int fully_contained(0), partially_overlapped(0), propper(0);
    int radius_1, radius_2;
    int center_1, center_2;
    int distance;
    while (getline(file, tp)) {
      numbers = convert_str_to_ranges(tp);
      int a1, b1, a2, b2;
      a1 = numbers[0];
      b1 = numbers[1];
      a2 = numbers[2];
      b2 = numbers[3];
      if ((a1 <= a2 and b2 <= b1) or (a2 <= a1 and b1 <= b2) ) {
        ++fully_contained;
      } 
      if (a2 <= b1 and a1 <= b2) {
        ++partially_overlapped;
      }
    }

    std::cout << "Fully contained: " << fully_contained << " Partially overlapped:" << partially_overlapped<<std::endl;
    file.close();
  }
}

