#ifndef BRICK_UTILS_HPP_
#define BRICK_UTILS_HPP_

#include <string>

namespace brick::utils 
{
  std::string random_string(size_t length) {
    auto randchar = []() -> char {
        const char charset[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };
    std::string str(length, 0);
    std::generate_n(str.begin(), length, randchar);
    return str;
  }    
}

#endif