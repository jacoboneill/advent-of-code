#ifndef STRING


class String{
public:
  static std::vector<std::string> split(std::string input, std::string delimiter){
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
};
#endif // !STRING
