#include <iostream>
#include <fstream>

class Parser{
  public:
    std::string input;

    Parser(std::string file_path){
      m_answers[0]= 0;
      m_answers[1]= 0;

      m_file_stream.open(file_path);
      if(!m_file_stream.is_open()){
        std::cerr << "Error, can't open: " << file_path << std::endl;
      }
      std::string line;
      while(std::getline(m_file_stream, line)){
        input += line + '\n';
      }
      m_file_stream.close();
    }

    ~Parser(){
      if(m_file_stream.is_open()) m_file_stream.close();
    }

    int* solve(){
      if(m_answers[0] != 0 || m_answers[1] != 0) return m_answers;

      m_answers[0] = part1();
      // m_answers[1] = part2();
      
      return m_answers;
    }

  private:
    std::ifstream m_file_stream;
    int m_answers[2];

    int part1(){
      int sum = 0;

      for(int i = 0; i < input.size(); i++){
        if(std::isdigit(input[i])){
          int full_number = getFullNumber(i);
          if(touchingSpecialCharacter(i, full_number)){
            sum += full_number;
          }
          i += std::to_string(full_number).size() - 1;
        }
      }

      return sum;
    }

    int searchForStart(int original_index){
      int i = original_index;
      while(std::isdigit(input[i])){
        i--;
      }
      return i + 1;
    }

    int getFullNumber(int original_index){
      int i = searchForStart(original_index);
      
      int full_number = 0;
      while(std::isdigit(input[i])){
        full_number = (full_number * 10) + input[i] - '0';
        i++;
      }

      return full_number;
    }

    bool checkCharacter(int index){
      return input[index] != '.' && input[index] != '\n' && !std::isdigit(input[index]);
    }

    bool touchingSpecialCharacter(int original_index, int full_number){
      int start = searchForStart(original_index);
      int end = start + std::to_string(full_number).size() - 1;

      int row = input.find('\n') + 1;

      // Check Sides
      if(start - 1 >= 0 && checkCharacter(start - 1)){
        // std::cout << "Index: " << start - 1 << " | ";
        return true;
      }

      if(end + 1 < input.size() && checkCharacter(end + 1)){
        // std::cout << "Index: " << end + 1 << " | ";
        return true;
      }


      // Check Diagonals, Above, and Below
      for(int i = start - 1; i <= end + 1; i++){
        if(i - row >= 0 && checkCharacter(i - row)){
          // std::cout << "Index: " << i - row << " | ";
          return true;
        }

        if(i + row < input.size() && checkCharacter(i + row)){
          // std::cout << "Index: " << i + row << " | ";
          return true;
        }
      }

      return false;
    }
};

int main (int argc, char *argv[]) {
  Parser parser("../data/input.txt");
  parser.solve();
  std::cout <<
    "Input:\n" << parser.input << "\n\n" <<
    "Part 1 Answer: " << parser.solve()[0] << std::endl <<
    "Part 2 Answer: " << parser.solve()[1] <<
  std::endl;
  return 0;
}
