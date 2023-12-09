#include <fstream>
#include <iostream>
#include "../utils/print.hpp"
#include "../utils/string.hpp"

class Day{
public:
  Day(std::string file_location){
    m_fs.open(file_location);
    if(!m_fs.is_open()){
      std::cerr << "Error, can't open: " << file_location << std::endl;
    }
  }

  ~Day(){
    m_fs.close();
  }

  int* play(){
    int* answers = new int[2];
    
    std::string line;
    while(std::getline(m_fs, line)){
      // ParseLine
      // Update answers[0]
      // Update answers[1]
    }

    return answers;
  }

private:
  std::ifstream m_fs;
};

int main (int argc, char *argv[]) {
  Day day("../data/input.txt");

  return 0;
}
