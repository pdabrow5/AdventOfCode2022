#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>
#include <sstream>
#include<functional>
#include<optional>
#include<memory>

#include "tasks_1-6.h"
#include "task_7.h"
#include "task_8.h"
#include "task_9.h"
void fxx(int& count, const std::string& s, int offset) {
  count += s.size() + offset;
}

int main()
{   
    //task1("1st_task.txt");
    //task2("2nd_task.txt");
    //task3_1("3rd_task.txt");
    //task3_2("3rd_task.txt");
    //task4("4th_task.txt");
    //task5("5th_task.txt");
    //task6("6th_task.txt");
    //task7("7th_task.txt");
    task9_1("9th_task.txt");
    task9_2("9th_task.txt");
    return 0;
}
