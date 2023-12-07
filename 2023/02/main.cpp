#include <climits>
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
    int result = 0;

    while(std::getline(m_fs, line)){
      ParsedLine parsed_line = parseLine(line);
      // std::cout << parsed_line.id << ": " << (part1(parsed_line) != 0 ? "Valid" : "Invalid") << std::endl;
      // result += part1(parsed_line);
      std::cout << parsed_line.id << ": " << part2(parsed_line) << std::endl;
      result += part2(parsed_line);
    }
    
    // possible_id_sum += parseLine("Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green");
    return result;
  }

private:
  std::ifstream m_fs;
  std::map<std::string, int> m_valid_color_map;

  struct ParsedLine{
    int id;
    std::vector<std::vector<std::string>> plays;
  };

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

  std::string printMap(std::map<std::string, int> map){
    std::vector<std::vector<std::string>> converted_map;
    for(auto it : map){
      std::vector<std::string> key_value;
      key_value.push_back(it.first);
      key_value.push_back(std::to_string(it.second));
      converted_map.push_back(key_value);
    }

    return print2DVector(converted_map);
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

  ParsedLine parseLine(std::string line){
    // std::cout << line << std::endl;

    // Split string and get ID
    int id = std::stoi(line.substr(line.find(' ') + 1, line.find(": ") - line.find(' ') - 1));

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

    return {id, plays};
  }

  int part1(ParsedLine line){
    // Loop through
    for(std::vector<std::string> play : line.plays){
      for(std::string p : play){
        std::vector<std::string> split_p = split(p, " ");
        if(std::stoi(split_p[0]) > m_valid_color_map[split_p[1]]){
          return 0; 
        }
      }
    }

    return line.id;
  }

  int part2(ParsedLine line){
    std::map<std::string, int> color_map = {
      {"red", 0},
      {"green", 0},
      {"blue", 0}
    };

    for(std::vector<std::string> play : line.plays){
      for(std::string p : play){
        std::vector<std::string> split_p = split(p, " ");
        if(color_map[split_p[1]] < std::stoi(split_p[0])){
          color_map[split_p[1]] = std::stoi(split_p[0]);
        }
      }
    }

    int product = color_map["red"] * color_map["green"] * color_map["blue"];
    return product;
  }
};

int main (int argc, char *argv[]) {
  BoxGame game("../data/input.txt");
  int count = game.count();
  std::cout << count << std::endl;
  return 0;
}
