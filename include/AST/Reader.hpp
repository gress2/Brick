#ifndef BRICK_AST_READER_HPP_
#define BRICK_AST_READER_HPP_

#include <fstream>
#include <string>
#include <utility>

namespace Brick::AST
{

class Reader {
private:
  std::ifstream ifs_; 
public:
  Reader(std::string);
  Tree read(); 
};

Reader::Reader(std::string input_file) : ifs_(std::ifstream(input_file)) {}

Tree build_ast_recursively(std::vector<std::pair<int, std::string>>& node_data, int i, int j) {
  Tree tree(node_data[i].second); 

  if (i == j) {
    return tree;
  }

  std::vector<Tree> children;

  int cur_level = node_data[i].first;
  for (int k = i + 1; k <= j; k++) {
    if (node_data[k].first == cur_level + 1) {
      int range_child = j;
      for (int m = k + 1; m <= j; m++) {
        if (node_data[m].first > cur_level + 1) {
          range_child = m - 1;
          break;
        }
      } 
      children.push_back(build_ast_recursively(node_data, k, range_child));
    }
  }
  tree.set_children(children);
  return tree;
} 

Tree Reader::read() {
  std::vector<std::pair<int, std::string>> node_data; 
  
  for (std::string line; getline(ifs_, line);) {
    int idx = line.find_first_not_of("\t");
    std::string data = line.substr(idx);
    node_data.push_back(std::make_pair(idx, data));
  }
  
  return build_ast_recursively(node_data, 0, node_data.size() - 1);
}

}

#endif
