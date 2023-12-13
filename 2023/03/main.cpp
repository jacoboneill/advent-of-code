#include <fstream>
#include <iostream>
#include <vector>
#include "util.hpp"

class Day{
public:
  Day(std::string file_location){
    std::ifstream file_stream;
    file_stream.open(file_location);

    if(file_stream.is_open()){
      std::string line_buf;
      while(getline(file_stream, line_buf)){
        m_file.push_back(line_buf);
      }
      file_stream.close();
    }else{
      std::cerr << "Error, can't open: " << file_location << std::endl;
    }
  }

  int* play(){
    int* answers = new int[2];

    m_log = m_file;

    for(int row = 0; row < m_file.size(); row++){
      for(int col = 0; col < m_file[row].size(); col++){
        char character = m_file[row][col];

        if(!std::isdigit(character) && character != '.'){
          m_log[row].replace(m_log[row].find(character), 1, Util::formatString(std::string(1, character), 0x00FF00));
        }
      }
      std::cout << std::endl;
    }

    return answers;
  }

  std::string debug(){
    return Util::debug(m_file, m_log);
  }

private:
  std::vector<std::string> m_file;
  std::vector<std::string> m_log;
};

int main (int argc, char *argv[]) {
  std::string path = "../data/" + (argc == 2 ? std::string(argv[1]) + ".txt" : "input.txt");
  Day day(path);

  int* answers = day.play();

  std::cout << "\n\n\n";

  std::cout <<
    day.debug() <<
    Util::formatString("Answers: \n", 0xFFFFFF, true) <<
    "Part 1: " << answers[0] << std::endl <<
    "Part 2: " << answers[1] <<
  std::endl;

  return 0;
}
