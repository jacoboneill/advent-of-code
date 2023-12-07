#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include "../utils/print.hpp"
#include "../utils/string.hpp"

class BoxGame{
public:
  BoxGame(std::string file_location){
    m_fs.open(file_location);
    if(!m_fs.is_open()){
      std::cerr << "Error, can't open: " << file_location << std::endl;
    }

  }

  ~BoxGame(){
    m_fs.close();
  }

  int* count(){
    std::string line;
    int part_1_count = 0;
    int part_2_count = 0;

    while(std::getline(m_fs, line)){
      ParsedLine parsed_line = parseLine(line);
      part_1_count += part1(parsed_line);
      part_2_count += part2(parsed_line);
    }
    
    return new int[2]{part_1_count, part_2_count};
  }

private:
  std::ifstream m_fs;

  struct ParsedLine{
    int id;
    std::vector<std::vector<std::string>> plays;
  };

  ParsedLine parseLine(std::string line){
    // Split string and get ID
    int id = std::stoi(line.substr(line.find(' ') + 1, line.find(": ") - line.find(' ') - 1));

    // Split ID from Games
    std::string games = line.substr(line.find(": ") + 2);

    // Split Games into Sets of Games
    std::vector<std::string> sets = String::split(games, "; ");
    // std::cout << printVector(sets) << std::endl;


    // Split Sets into Plays
    std::vector<std::vector<std::string>> plays;
    for(std::string set : sets){
      std::vector<std::string> play = String::split(set, ", ");
      plays.push_back(play);
    }

    return {id, plays};
  }

  int part1(ParsedLine line){
    // Loop through and find if a color is larger than the map. If so return 0
    std::map<std::string, int> valid_color_map = {
      {"red", 12},
      {"green", 13},
      {"blue", 14}
    };
    for(std::vector<std::string> play : line.plays){
      for(std::string p : play){
        std::vector<std::string> split_p = String::split(p, " ");
        if(std::stoi(split_p[0]) > valid_color_map[split_p[1]]){
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

    // Loop through and find max value of colors and add to map
    for(std::vector<std::string> play : line.plays){
      for(std::string p : play){
        std::vector<std::string> split_p = String::split(p, " ");
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
  int* count = game.count();
  std::cout << "part 1: " << count[0] << "\npart 2: " << count[1] << std::endl;
  return 0;
}
