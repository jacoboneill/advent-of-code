#include <fstream>
#include <iostream>
#include <map>
#include <vector>

class BoxGame{
public:
  BoxGame(std::string file_location){
    m_fs.open(file_location);
    if(!m_fs.is_open()){
      std::cerr << "Error, can't open: " << file_location << std::endl;
    }

    m_valid_color_map = {
      {"red", 12},
      {"green", 13},
      {"blue", 14}
    };
  }

  ~BoxGame(){
    m_fs.close();
  }

  int count(){
    std::string line;
    int possible_id_sum = 0;

    while(std::getline(m_fs, line)){
     possible_id_sum += parseLine(line);
    }
    
    // possible_id_sum += parseLine("Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green");
    return possible_id_sum;
  }

private:
  std::ifstream m_fs;
  std::map<std::string, int> m_valid_color_map;

  std::string printVector(std::vector<bool> vector){
    std::string out;
    out += "[";

    for(int i = 0; i < vector.size(); i++){
      if(i != 0){
        out += ", ";
      }
      out += "\"";
      out += vector[i] ? "True" : "False";
      out += "\"";
    }

    out += "]";

    return out;
  }

  std::string printVector(std::vector<std::string> vector){
    std::string out;
    out += "[";

    for(int i = 0; i < vector.size(); i++){
      if(i != 0){
        out += ", ";
      }
      out += "\"" + vector[i] + "\"";
    }

    out += "]";

    return out;
  }

  std::string print2DVector(std::vector<std::vector<std::string> > vector_2d){
    std::string out;
    out += "[\n";

    for(int i = 0; i < vector_2d.size(); i++){
      if(i != 0){
        out += ", \n";
      }
      out += '\t' + printVector(vector_2d[i]) ;
    }

    out += "\n]";

    return out;
  }
  
  std::vector<std::string> split(std::string input, std::string delimiter){
    std::vector<std::string> result;
    size_t pos_a = 0;
    size_t pos_b = input.find(delimiter);

    while(pos_b != std::string::npos){
      result.push_back(input.substr(pos_a, pos_b - pos_a));
      pos_a = pos_b + delimiter.size();
      pos_b = input.find(delimiter, pos_a);
    }

    result.push_back(input.substr(pos_a, std::min(pos_b, input.size()) - pos_a + 1));
    return result;
  }

  int parseLine(std::string line){
    std::cout << line << std::endl;

    // Split string and get ID
    int id = std::stoi(line.substr(line.find(' ') + 1, line.find(": ") - line.find(' ') - 1));
    // std::cout << id << std::endl;

    // Split ID from Games
    std::string games = line.substr(line.find(": ") + 2);

    // Split Games into Sets of Games
    std::vector<std::string> sets = split(games, "; ");
    // std::cout << printVector(sets) << std::endl;


    // Split Sets into Plays
    std::vector<std::vector<std::string>> plays;
    for(std::string set : sets){
      std::vector<std::string> play = split(set, ", ");
      plays.push_back(play);
    }

    // Split Plays into Entries of Number and Color
    std::vector<bool> valid_plays;
    for(std::vector<std::string> play : plays){
      for(std::string p : play){
        std::vector<std::string> split_p = split(p, " ");
        valid_plays.push_back(std::stoi(split_p[0]) <= m_valid_color_map[split_p[1]]);
      }
    }

    std::cout << printVector(valid_plays) << std::endl;

    // Check if any are not valid Plays
    for(bool valid_play : valid_plays){
      if(!valid_play){
        return 0;
      }
    }
    return id;
  }
};

int main (int argc, char *argv[]) {
  BoxGame game("../data/input.txt");
  int count = game.count();
  std::cout << count << std::endl;
  return 0;
}
