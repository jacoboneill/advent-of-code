#ifndef PRINT
#define PRINT

#include <string>
#include <vector>

class Print{
public:
  static std::string vector(std::vector<std::string> input_vector){
    std::string out = "[";

    for(int i = 0; i < input_vector.size(); i++){
      if(i != 0){ out += ", "; }

      out += "\"" + input_vector[i] + "\"";
    }

    out += "]";
    return out;
  }

  static std::string vector(std::vector<bool> input_vector){
    std::string out = "[";
    for(int i = 0; i < input_vector.size(); i++){
      if(i != 0){ out += ", "; }
      out += input_vector[i] ? "\x1b[32mtrue\x1b[0m" : "\x1b[31mfalse\x1b[0m";
    }

    out += "]";
    return out;
  }

  static std::string vector_2d(std::vector<std::vector<std::string>> input_vector){
    std::string out = "[\n";

    for(int i = 0; i < input_vector.size(); i++){
      if(i != 0){ out += ", \n"; }
      out += '\t' + vector(input_vector[i]);
    }

    out += "\n]";
    return out;
  }

  static std::string map(std::map<std::string, int> input_map){
    std::vector<std::vector<std::string>> converted_map;

    for(auto it : input_map){
      converted_map.push_back({it.first, std::to_string(it.second)});
    }

    return vector_2d(converted_map);
  }
};

#endif // !PRINT
