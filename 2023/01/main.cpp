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
      int a = 0;
      int b = 0;
      int line_total = 0;

      for(int i = 0; i < line.size(); i++){
        if(isdigit(line[i])){
          a = 10 * (line[i] - '0');
          break;
        }
      }

      for(int i = line.size() - 1; i >= 0; i--){
        if(isdigit(line[i])){
          b = line[i] - '0';
          break;
        }
      }
      
      line_total = a + b;
      count += line_total;

      std::cout << line << " | " << line_total << " | " << count << std::endl;
    }
    
    std::cout << "TOTAL: " << count << std::endl;
    return count;
  }

private:
  std::string newTableRow(std::string line, int number, int count){
    return line + ", " + std::to_string(number) + ", " + std::to_string(count);
  }

  std::string highlight(std::string line, int index_one, int index_two){
    const std::string bold_red = "\x1b[1;31m";
    const std::string reset = "\x1b[0m";

    std::string highlight = line.substr(0, index_one - 1);
    highlight += bold_red + line.substr(index_one - 1, 1) + reset;
    highlight += line.substr(index_one + 1, index_two - index_one - 1);
    highlight += bold_red + line.substr(index_two, 1) + reset;
    highlight += line.substr(index_two + 1, line.size() - index_two + 1);

    return highlight;
  }

  std::string m_fl;
};

int main (int argc, char *argv[]) {
  Parser parser("../data/input.txt");
  parser.parse();
  return 0;
}
