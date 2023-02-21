#include "tasks_1-6.h"
/*




*/
void task1(std::string filename) { 
  std::fstream file;
  file.open(
      filename,
      std::ios::in);  // open a file to perform read operation using file object
  if (file.is_open()) {  // checking whether the file is open
    std::string tp;
    int calories(0), max_calories(0);
    std::vector<int> elves;
    while (getline(file, tp)) {
      try {
        calories += std::stoi(tp);
        if (calories >= max_calories) {
          max_calories = calories;
        }

      } catch (const std::invalid_argument&) {
        elves.push_back(calories);
        calories = 0;
      }
    }
    std::sort(elves.rbegin(), elves.rend());
    std::for_each(elves.begin(), elves.end(),
                  [](const int n) { std::cout << n << std::endl; });
    std::cout << elves[0] + elves[1] + elves[2];

    file.close();  // close the file object.
  }


}

void task2(std::string filename) {
  std::fstream file;
  file.open(
      filename,
      std::ios::in);  // open a file to perform read operation using file object
  if (file.is_open()) {  // checking whether the file is open
    std::string tp;
    int my_score_1(0), my_score_2(0);
    char oponents_sign, my_sign;
    //part 1
    std::map<char, int> score_for_sign_1{
        {'A', 1}, {'X', 1},     //rock
        {'B', 2}, {'Y', 2},     //paper
        {'C', 3}, {'Z', 3}};    //scissors 
    std::map<std::string, int> score_for_result_1{
        {"A Z", 0}, {"B X", 0}, {"C Y", 0},     //lose
        {"A X", 3}, {"B Y", 3}, {"C Z", 3},     //draw
        {"A Y", 6}, {"B Z", 6}, {"C X", 6}};    //win

    //part 2
    std::map<std::string, int> score_for_result_and_sign_2{
        {"A X", 3}, {"B X", 1}, {"C X", 2},   // lose
        {"A Y", 4}, {"B Y", 5}, {"C Y", 6},   // draw
        {"A Z", 8}, {"B Z", 9}, {"C Z", 7}};  // win


    while (getline(file, tp)) {

      try {
        oponents_sign = tp[0];
        my_sign = tp[2];
        my_score_1 += score_for_sign_1[my_sign] + score_for_result_1[tp];
        my_score_2 += score_for_result_and_sign_2[tp];

      } catch (const std::invalid_argument&) {
        // todo
      }
    }

    file.close();  // close the file object.
    std::cout << "Part 1: "<<my_score_1 << "Part 2: " << my_score_2 << std::endl;
  }


}

void task3_1(std::string filename) {
  std::fstream file;
  // A-Z => 65-90
  // a-z => 97-122

  file.open(
      filename,
      std::ios::in);  // open a file to perform read operation using file object
  if (file.is_open()) {  // checking whether the file is open
    std::string tp;
    std::string first_half, second_half;
    char common_letter(0), common_letter_value(0);
    int lenght(0), priority_sum(0);
    while (getline(file, tp)) {
      lenght = tp.length();
      first_half.clear();
      second_half.clear();
      bool found_common_letter = false;
      for (int i(0); i < lenght / 2; i++) {
        first_half.push_back(tp[i]);
        second_half.push_back(tp[i + lenght / 2]);
      }

      for (std::string::const_iterator n = first_half.cbegin();
           n != first_half.cend(); n++) {
        if (found_common_letter) {
          break;
        }
        for (std::string::const_iterator m = second_half.cbegin();
             m != second_half.cend(); m++)
          if (*n == *m) {
            common_letter = *m;
            found_common_letter = true;
            break;
          }
      }
      if (int(common_letter) < 91)
        common_letter_value = int(common_letter) - 38;
      else {
        common_letter_value = int(common_letter) - 96;
      }
      std::cout << common_letter << " "<< int(common_letter_value)
                << std::endl;
      priority_sum += common_letter_value;
    }

    std::cout << "Part 1: " << priority_sum << std::endl;
    file.close();
  }
}
void task3_2(std::string filename) {
  std::fstream file;
  //A-Z => 65-90
  //a-z => 97-122

  file.open(
      filename,
      std::ios::in);  // open a file to perform read operation using file object
  if (file.is_open()) {  // checking whether the file is open
    std::string tp;
    std::string first_elve, second_elve, third_elve;
    char common_letter(0), common_letter_value(0);
    int priority_sum(0);
    while (getline(file, tp)) {
      first_elve = tp;
      getline(file, second_elve);
      getline(file, third_elve);
      bool found_common_letter = false;

      
      for (std::string::const_iterator n = first_elve.cbegin();
           n != first_elve.cend(); n++) {
        if (found_common_letter) {   
            break;
        }
        for (std::string::const_iterator m = second_elve.cbegin();
             m != second_elve.cend(); m++)
          if (*n == *m) {
            if (found_common_letter) {
                break;
            }
            for (std::string::const_iterator k = third_elve.cbegin();
                 k != third_elve.cend(); k++) {
              if (*m == *k) {
                common_letter = *k;
                found_common_letter = true;
                break;
              }
            }
          }
      }
      if (int(common_letter) < 91)
        common_letter_value = int(common_letter) - 38;
      else {
        common_letter_value = int(common_letter) - 96;
      }  
      priority_sum += common_letter_value;
    }
    
    std::cout << "Part 2: " << priority_sum << std::endl; //print solution
    file.close();
  }
}


