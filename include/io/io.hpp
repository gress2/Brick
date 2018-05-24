#ifndef BRICK_IO_IO_HPP_
#define BRICK_IO_IO_HPP_

#include <fstream>

#include "tree/tree.hpp"

namespace brick::io
{
  // TODO: why can't this be outside the namespace?
  template <class T>
  using tree = brick::tree::tree<T>;

  template <class T>
  tree<T> read_ast(std::ifstream& input_file) {
    tree<T> t("3");
    return t;
  }

  template <class T>
  bool write_ast(T& t, std::ofstream& output_file) {
    for (auto it = t.begin_bfs(); it != t.end_dfs(); ++it) {
      auto level = it->get_level();
      auto value = it->get_value();
      output_file << std::string(level, '\t') << value << std::endl;
    }
    return true;
  }

  template <class T>
  tree<T> read_latex(std::ifstream& input_file) {
    tree<T> t("3");
    return t;
  }

  template <class T>
  void write_latex(T& t, std::ofstream& output_file) {

  }
}

#endif
