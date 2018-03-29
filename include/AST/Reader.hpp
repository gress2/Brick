#ifndef BRICK_AST_READER_HPP_
#define BRICK_AST_READER_HPP_

#include <fstream>
#include <string>

namespace Brick::AST
{

class Reader {
private:
  std::fstream fs_; 
public:
  Reader(std::string);
  AST read(); 
};

Reader::Reader(std::string input_file) : fs_(std::fstream(input_file, std::fstream::in)) {}

AST Reader::read() {
  AST ast;


  return ast;
}

}

#endif
