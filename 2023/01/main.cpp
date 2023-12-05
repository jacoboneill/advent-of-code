#include <iostream>
#include <fstream>
#include <map>

class Parser{
public:
  Parser(std::string file_location) : 
    m_fl(file_location),
    m_map({
      {"zero", 0},
      {"one", 1},
      {"two", 2},
      {"three", 3},
      {"four", 4},
      {"five", 5},
      {"six", 6},
      {"seven", 7},
      {"eight", 8},
      {"nine", 9}
    })
    {}

  int parse(){
    std::string line;
    std::fstream file(m_fl);
    int count = 0;

    while(std::getline(file, line)){
      int line_total = (searchFront(line) * 10) + searchBack(line); 
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
        return line[i] - '0';
      }

      for(auto it : m_map){
        if(line[i] == it.first[0]){
          if(line.substr(i, it.first.size()) == it.first){
            return it.second;
          }
        }
      }
    }

    return -1;
  }

  int searchBack(std::string line){
    for(int i = line.size() - 1; i >= 0; i--){
      if(isdigit(line[i])){
        return line[i] - '0';
      }

      for(auto it : m_map){
        if(line[i] == it.first[it.first.size() - 1]){
          if(i - static_cast<int>(it.first.size()) + 1 >= 0){ // Have to static cast as size is a unsigned size_t
            if(line.substr(i - it.first.size() + 1, it.first.size()) == it.first){
              return it.second;
            }
          }
        }
      }
    }

    return -1;
  }
  std::string m_fl;
  std::map<std::string, int> m_map;
};

int main (int argc, char *argv[]) {
  Parser parser("../data/input.txt");
  parser.parse();
  return 0;
}
