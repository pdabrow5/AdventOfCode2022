#include <sstream>
#include "tasks_1-6.h"



void task6(std::string filename) {
  std::fstream file;


  file.open(
      filename,
      std::ios::in);  // open a file to perform read operation using file object
  if (file.is_open()) {  // checking whether the file is open
    std::string tp;
    unsigned int size_of_marker = 14;
    unsigned int counter = size_of_marker;
    getline(file, tp);
    if (tp.size() < size_of_marker) std::cout << "Not enough signs";
    else {

    for (size_t i = 0; i < tp.size() - size_of_marker + 1; ++i) {
      bool pair_exists_in_set = false;
      for (int j = i; j < i+size_of_marker + 1; ++j) {
        for (int k = j + 1; k < i+size_of_marker; ++k)
          if (tp[j] == tp[k]) {
            pair_exists_in_set = true;
            break;
          }
        if (pair_exists_in_set) break;
      }
      if (!pair_exists_in_set) {
        std::cout << "first marker of lenght " <<size_of_marker<<" after character " << counter << std::endl;
        break;
      }
      ++counter;
    }
    file.close();

    }

  }
}
