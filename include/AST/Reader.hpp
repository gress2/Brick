#ifndef BRICK_AST_READER_HPP_
#define BRICK_AST_READER_HPP_

#include <fstream>
#include <string>

namespace Brick::AST
{

class Reader {
private:
  std::ifstream ifs_; 
public:
  Reader(std::string);
  AST read(); 
};

Reader::Reader(std::string input_file) : ifs_(std::ifstream(input_file)) {}

AST Reader::read() {
  AST ast;
  for (std::string line; getline(ifs_, line);) {
    std::cout << line << std::endl;
  }
  return ast;
}

}

#endif
