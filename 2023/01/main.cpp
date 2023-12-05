#include <iostream>
#include <fstream>

class Parser{
public:
  Parser(std::string file_location) : 
    m_fl(file_location)
    {}

  int parse(){
    std::string line;
    std::fstream file(m_fl);
    int count;

    while(std::getline(file, line)){
      int line_total = searchFront(line) + searchBack(line); 
      count += line_total;
      std::cout << line << " | " << line_total << " | " << count << std::endl;
    }
    
    std::cout << "TOTAL: " << count << std::endl;
    return count;
  }

private:
  int searchFront(std::string line){
    for(int i = 0; i < line.size(); i++){
      if(isdigit(line[i])){
        return 10 * (line[i] - '0');
      }
    }

    return -1;
  }

  int searchBack(std::string line){
    for(int i = line.size() - 1; i >= 0; i--){
      if(isdigit(line[i])){
        return line[i] - '0';
      }
    }

    return -1;
  }

  std::string m_fl;
};

int main (int argc, char *argv[]) {
  Parser parser("../data/input.txt");
  parser.parse();
  return 0;
}
