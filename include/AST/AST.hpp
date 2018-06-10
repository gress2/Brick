#ifndef BRICK_AST_AST_HPP_
#define BRICK_AST_AST_HPP_

#include <memory>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "AST/node.hpp"

namespace brick::AST
{
  using node = brick::AST::node;

  class AST {
    private:
      std::unique_ptr<node> node_;
      std::vector<std::shared_ptr<AST>> children_; // TODO: unnecessary?
      AST* parent_ = nullptr;
    public:
      AST(std::unique_ptr<node>&&);
      node* get_node() const;
      void set_node(std::unique_ptr<node>&&);
      bool is_full() const;
      bool is_terminal() const;
      std::shared_ptr<AST> add_child(std::shared_ptr<AST>);
      std::shared_ptr<AST> add_child(std::unique_ptr<node>&&);
      bool has_children() const;
      std::shared_ptr<AST> get_child(std::size_t) const;
      const std::vector<std::shared_ptr<AST>>& get_children() const;
      void set_parent(AST*);
      AST* get_parent() const;
      std::string to_string() const;
      void print() const;
      double eval(std::unordered_map<std::string, double>* = nullptr) const;
      std::string get_node_id() const;
      std::string gv_helper() const;
      std::string to_gv() const;
      bool operator==(const AST&) const;
      ~AST();
  };

  AST::AST(std::unique_ptr<node>&& node)
    : node_(std::move(node))
  {}

  AST::~AST() {}

  node* AST::get_node() const {
    return node_.get();
  }

  void AST::set_node(std::unique_ptr<node>&& node) {
    node_ = std::move(node);
  }

  bool AST::is_full() const {
    return node_->num_children() == children_.size();
  }

  bool AST::is_terminal() const {
    return node_->is_terminal();
  }

  std::shared_ptr<AST> AST::add_child(std::shared_ptr<AST> child) {
    if (is_full() || is_terminal()) {
      return nullptr;
    }
    children_.push_back(child);
    child->set_parent(this);
    return child;
  }

  std::shared_ptr<AST> AST::add_child(std::unique_ptr<node>&& node) {
    if (is_full() || is_terminal()) {
      return nullptr;
    }
    std::shared_ptr<AST> child = std::make_shared<AST>(std::move(node));
    children_.push_back(child);

    child->set_parent(this);
    return child;
  }

  bool AST::has_children() const {
    return children_.size() > 0;
  }

  const std::vector<std::shared_ptr<AST>>& AST::get_children() const {
    return children_;
  }

  std::shared_ptr<AST> AST::get_child(std::size_t idx) const {
    return children_[idx];
  }

  void AST::set_parent(AST* parent) {
    parent_ = parent;
  }

  AST* AST::get_parent() const {
    return parent_;
  }

  std::string AST::to_string() const {
    if (children_.size() == 0) {
      return node_->to_string();
    } else if (children_.size() == 1) {
      if (node_->wraps()) {
        return node_->wrap_left() +
          children_[0]->to_string() +
          node_->wrap_right();
      } else {
        return node_->to_string() +
          children_[0]->to_string();
      }
    } else {
      return children_[0]->to_string() +
        node_->to_string() + 
        children_[1]->to_string();
    } 
  }

  void AST::print() const {
    std::cout << to_string() << std::endl;
  }

  double AST::eval(std::unordered_map<std::string, double>* sym_tbl) const {
    if (node_->is_parens() || node_->is_brackets() || node_->is_posit()) {
      return children_[0]->eval(sym_tbl);
    } else if (node_->is_negate()) {
      return -children_[0]->eval(sym_tbl);
    } else if (node_->is_addition()) {
      return children_[0]->eval(sym_tbl) + children_[1]->eval(sym_tbl);
    } else if (node_->is_subtraction()) {
      return children_[0]->eval(sym_tbl) - children_[1]->eval(sym_tbl);
    } else if (node_->is_multiplication()) {
      return children_[0]->eval(sym_tbl) * children_[1]->eval(sym_tbl);
    } else if (node_->is_division()) {
      return children_[0]->eval(sym_tbl) / children_[1]->eval(sym_tbl);
    } else if (node_->is_function()) {
      return dynamic_cast<function_node*>(node_.get())
              ->operator()(children_[0]->eval(sym_tbl));
    } else if (node_->is_number()) {
      return dynamic_cast<number_node*>(node_.get())->get_number(); 
    } else if (node_->is_id()) {
      std::string id = dynamic_cast<id_node*>(node_.get())->get_id();
      if (sym_tbl) {
        if (sym_tbl->count(id)) {
          return sym_tbl->operator[](id);
        } else {
          std::cerr << "Symbol with undefined value in AST: " << id << " not found in symbol table" << std::endl;
        }
      } else {
        std::cerr << "Symbol encountered in AST but no symbol table was passed" << std::endl;
      }
      std::cerr << "Using a value of 0 for this symbol..." << std::endl;
      return 0;
    } else {
      std::cerr << "Something went wrong: unhandled node type in AST evaluation" << std::endl;
      std::cerr << "Using a value of 0 for this node..." << std::endl;
      return 0;
    }
  }

  std::string AST::get_node_id() const {
    return node_->get_node_id();
  }

  std::string AST::gv_helper() const {
    std::stringstream ss;
    auto node_id = get_node_id();
    ss << node_id << " [label=\"" << node_->get_gv_label() << "\"]" << std::endl;
    for (auto child : children_) {
      ss << node_id << " -- " << child->get_node_id() << std::endl;
      ss << child->gv_helper();
    }
    return ss.str();
  }

  std::string AST::to_gv() const {
    std::stringstream ss;
    ss << "graph {" << std::endl;
    ss << gv_helper();
    ss << "}" << std::endl;
    return ss.str();
  }

  bool AST::operator==(const AST& other) const {
    return node_.get() == other.get_node()
      && children_ == other.get_children();
  }

}

#endif
