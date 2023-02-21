#include "task_7.h"
#include<iostream>
#include<sstream>
#include<fstream>
#include<algorithm>

void Sum_all_filesizes_below(std::shared_ptr<Dir> const directory,
                       unsigned long int& sum_of_sizes) {
  unsigned long int size = directory->GetDirSize();
  if (size <= 100000) sum_of_sizes += size;
  for (auto inner_dir = directory->included_dirs_.cbegin();
       inner_dir != directory->included_dirs_.cend(); inner_dir++)
    Sum_all_filesizes_below(*inner_dir, sum_of_sizes);
}
void Add_directories_above_size(
    std::shared_ptr<Dir> dir, unsigned long int min_size,
    std::vector<unsigned long int> &vec_of_sizes) {
  unsigned long int current_size = dir->GetDirSize();
  if (current_size >= min_size) {
    vec_of_sizes.push_back(current_size);
    for (auto inner_dir = dir->included_dirs_.cbegin();
           inner_dir != dir->included_dirs_.cend(); inner_dir++)
        Add_directories_above_size(*inner_dir, min_size, vec_of_sizes);
  } 

}



Dir::Dir(std::string dir_name, Dir* outer_dir) {
    
    name_= dir_name;
}

unsigned long int Dir::GetFilesSize() {
    unsigned long int sum_of_sizes(0);
    for (auto file = included_files_.cbegin(); file != included_files_.cend();
        file++)
        sum_of_sizes += file->get()->size_;
    return sum_of_sizes;
}

unsigned long int Dir::GetDirSize(unsigned long int offset) { 
  offset += GetFilesSize();
  for (auto inner_dir = included_dirs_.cbegin();
         inner_dir != included_dirs_.cend(); inner_dir++) {
  
        offset = (*inner_dir)->GetDirSize(offset);
        }

  return offset;
}

void Dir::AddFile(std::string filename, size_t size) {
  included_files_.push_back(std::make_unique<File>(filename, size));
}

void Dir::AddDir(std::string dirname) {
    std::shared_ptr<Dir> new_dir = std::make_shared<Dir>(dirname);
    new_dir->SetOuterDir(shared_from_this());
    included_dirs_.push_back(new_dir);
}

std::shared_ptr<Dir> Dir::GetDir(std::string dirname) {
    if (dirname == ".." and !outer_dir_.expired()) return std::shared_ptr<Dir>(outer_dir_);  
    for (auto dir = included_dirs_.cbegin(); dir != included_dirs_.cend(); dir++)
    if ((*dir)->name_ == dirname) return *dir;
    std::cout << "Directory " << name_
            << " does not include directory named: " << dirname << std::endl; 
    return nullptr;
}

void Dir::SetOuterDir(std::shared_ptr<Dir> outer_dir) {
    outer_dir_ = outer_dir;
}


FilesystermInterface::FilesystermInterface() { 
    current_dir_ = std::make_shared<Dir>("/");
    outermost_dir_ = current_dir_;
}

void FilesystermInterface::GoToDir(std::string destination) {
    std::shared_ptr<Dir> destination_dir = current_dir_->GetDir(destination);
    if (destination_dir) current_dir_ = destination_dir;

}

void FilesystermInterface::AddDir(std::string dirname) {
  current_dir_->AddDir(dirname);
}

void FilesystermInterface::AddFile(std::string filename, size_t size) {
  current_dir_->AddFile(filename, size);
}


void task7(std::string filename) {
  std::fstream file;
  FilesystermInterface filesys;

  file.open(
      filename,
      std::ios::in); 
  if (file.is_open()) { 
    std::string tp;
    getline(file, tp); //need to skip first lane because filesystem is in / dir by default
    while (getline(file, tp)) {
      if (tp[0] == '$') {
        if (tp[2] == 'c' and tp[3] == 'd') {
          std::string dir_name;
          std::stringstream ss;
          ss << tp;
          ss >> dir_name >> dir_name >> dir_name; //overwrites two first strings: "$" and "cd" 
                                                  // and replace it with directory name
          filesys.GoToDir(dir_name);

        }
      } else if (tp[0] == 'd' and tp[1] == 'i' and tp[2] == 'r') {
        std::string dir_name;
        std::stringstream ss;
        ss << tp;
        ss >> dir_name >> dir_name;
        filesys.AddDir(dir_name);
      } else {
        int size;
        std::string file_name;
        std::stringstream ss;
        ss << tp;
        ss >> size >> file_name;
        filesys.AddFile(file_name, (size_t)size);
      }

    }

 
    file.close();
  }
  unsigned long int available_space = 70000000;
  unsigned long int min_unused_space = 30000000;
  unsigned long int used_space = filesys.outermost_dir_->GetDirSize();
  unsigned long int min_freed_space = min_unused_space -(available_space - used_space);
  unsigned long int sum_of_sizes = 0;
  std::vector<unsigned long int> dirs_bigger_than;


  Sum_all_filesizes_below(filesys.outermost_dir_, sum_of_sizes);
  Add_directories_above_size(filesys.outermost_dir_, min_freed_space, dirs_bigger_than );
  std::sort(dirs_bigger_than.begin(), dirs_bigger_than.end());
  std::cout << "Part 1: " << sum_of_sizes << std::endl;
  std::cout << "Part 2: " << dirs_bigger_than[0] << std::endl; 
}