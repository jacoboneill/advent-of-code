#include <fstream>
#include <iostream>
#include <vector>
#include "../utils/print.hpp"
#include "../utils/string.hpp"

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

    for(int row = 0; row < m_file.size(); row++){
      for(int col = 0; col < m_file[row].size(); col++){
        char character = m_file[row][col];

        if(!std::isdigit(character) && character != '.'){
          
        }
      }
      // std::cout << std::endl;
    }

    return answers;
  }

  std::string getDebug(){
    std::string result;

    result += "\x1b[1mFile: \x1b[0m\n";
    result += vectorToString(m_file) + '\n';
    result += std::string(m_file.back().size() + 2, '-') + "\n\n";
    result += "\x1b[1mLog: \x1b[0m\n";
    result += vectorToString(m_log) + '\n';
    result += std::string(m_file.back().size() + 2, '-') + "\n\n";

    return result;
    
  }


private:
  std::vector<std::string> m_file;
  std::vector<std::string> m_log;

  std::string vectorToString(std::vector<std::string> input){
    std::string result;
    for(std::string s : input){
      result += s;
      result += '\n';
    }
    return result;
  }
};

int main (int argc, char *argv[]) {
  std::string path = "../data/" + (argc == 2 ? std::string(argv[1]) + ".txt" : "input.txt");
  Day day(path);

  int* answers = day.play();
  std::cout <<
    day.getDebug() <<
    "Part 1: " << answers[0] << std::endl <<
    "Part 2: " << answers[1] <<
  std::endl;

  return 0;
}
