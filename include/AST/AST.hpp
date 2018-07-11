#ifndef BRICK_AST_AST_HPP_
#define BRICK_AST_AST_HPP_

#include <iostream>
#include <memory>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "AST/node.hpp"
#include "AST/dfs_iterator.hpp"
#include "AST/bfs_iterator.hpp"

namespace brick::AST
{
  using node = brick::AST::node;

  class AST {
    private:
      std::unique_ptr<node> node_;
      std::vector<std::shared_ptr<AST>> children_;
      AST* parent_ = nullptr;
      int depth_ = 0;
    public:
      // LIFECYCLE
      AST(std::unique_ptr<node>&&);
      ~AST();

      // MODIFIERS
      void set_node(std::unique_ptr<node>&&);
      std::shared_ptr<AST> add_child(std::shared_ptr<AST>);
      std::shared_ptr<AST> add_child(std::unique_ptr<node>&&);
      void set_parent(AST*);
      void propagate_depth(int);
      
      // ACCESSORS
      node* get_node() const;
      bool is_full() const;
      std::size_t vacancy() const;
      bool is_terminal() const;
      bool has_children() const;
      std::shared_ptr<AST> get_child(std::size_t) const;
      const std::vector<std::shared_ptr<AST>>& get_children() const;
      std::vector<std::shared_ptr<AST>>& get_children();
      AST* get_parent() const;
      std::string to_string() const;
      double eval(std::unordered_map<std::string, double>* = nullptr) const;
      double eval(std::vector<double>) const;
      double eval(double) const;
      std::string get_node_id() const;
      std::string gv_helper() const;
      std::string to_gv() const;
      // TODO - get rid of this method
      std::size_t get_level() const;
      std::size_t get_size() const;
      std::size_t get_num_unconnected() const;
      int get_depth() const;
      bool is_valid() const;
      
      // OPERATORS
      bool operator==(const AST&) const;
      bool operator!=(const AST&) const;

      // ITERATORS
      dfs_iterator begin_dfs();
      dfs_iterator end_dfs();
      bfs_iterator begin_bfs();
      bfs_iterator end_bfs();
  };

}

#endif
