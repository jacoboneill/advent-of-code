#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>
#include <sstream>
#include <vector>

class Util{
public:
  static std::string formatString(const std::string& text, unsigned int color=0xFFFFFF, bool bold=false){
    if(color > 0xFFFFFF){
      std::cerr << color << " is not a valid color." << std::endl;
      return text;
    }

    std::stringstream result;
    result << "\x1b[";

    if(bold) result << "1;";

    result <<
      "38;2;" << // Add foreground color
      ((color >> 16) & 0xFF)  << ';' << // Add R
      ((color >> 8) & 0xFF) << ';' <<   // Add G
      (color & 0xFF) <<                 // Add B
      "m" << text << "\x1b[0m";

    return result.str();
  }

  static std::string vectorToString(const std::vector<std::string>& input){
    std::stringstream result;
    for(const auto& i : input){
      result << i << '\n';
    }
    return result.str();
  }

  static std::string debug(const std::vector<std::string>& file, const std::vector<std::string>& log){
    std::stringstream result;
    std::string divider = std::string(file.back().size() + 2, '-') + "\n";    

    result <<
      formatString("File: \n", 0xFFFFFF, true) <<
      vectorToString(file) << '\n' <<
      divider << '\n' <<
      formatString("Log: \n", 0xFFFFFF, true) << 
      vectorToString(log) << '\n' <<
      divider << '\n';

    return result.str();
  }
};

#endif // UTIL_HPP
