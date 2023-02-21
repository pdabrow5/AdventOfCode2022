#pragma once
#include<memory>
#include<vector>
#include<string>

void task7(std::string filename);

class File {
    public:
        File(std::string filename, size_t size) : size_(size), name_(filename){};

    private:
        size_t size_;
        std::string name_;
        friend class Dir;
};

class Dir: public std::enable_shared_from_this<Dir> {
    public:
        Dir(std::string dir_name, Dir* outer_dir = nullptr);
        unsigned long int GetFilesSize();
        unsigned long int GetDirSize(unsigned long int offset = 0);
        void AddFile(std::string filename, size_t size);
        void AddDir(std::string dirame);
        std::shared_ptr<Dir> GetOuterDir() { return std::shared_ptr<Dir>(outer_dir_); };
        std::shared_ptr<Dir> GetDir(std::string dirname); 
        std::vector<std::shared_ptr<Dir>> included_dirs_ = {};
        std::vector<std::unique_ptr<File>> included_files_ = {};

    private:
        void SetOuterDir(std::shared_ptr<Dir> outer_dir);
        std::string name_;
        std::weak_ptr<Dir> outer_dir_ = std::shared_ptr<Dir>(nullptr);

};


class FilesystermInterface {
 public:
  FilesystermInterface();
  void GoToDir(std::string destination);
  void AddDir(std::string dirname);
  void AddFile(std::string filename, size_t size);
  unsigned long int GetFilesSize() { return current_dir_->GetFilesSize(); };
  std::shared_ptr<Dir> current_dir_;
  std::shared_ptr<Dir> outermost_dir_;
};
