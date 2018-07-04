#include "AST/AST.hpp"

namespace brick::AST
{

  // LIFECYCLE
  AST::AST(std::unique_ptr<node>&& node)
    : node_(std::move(node))
  {}

  AST::~AST() {}

  // MODIFIERS
  void AST::set_node(std::unique_ptr<node>&& node) {
    node_ = std::move(node);
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

  void AST::set_parent(AST* parent) {
    parent_ = parent;
  }

  void AST::propagate_depth(int depth) {
    depth_ = depth;
    for (auto& child : children_) {
      child->propagate_depth(depth + 1);
    }
  }

  // ACCESSORS
  
  node* AST::get_node() const {
    return node_.get();
  }

  bool AST::is_full() const {
    return node_->num_children() == children_.size();
  }

  std::size_t AST::vacancy() const {
    return node_->num_children() - children_.size();
  }

  bool AST::is_terminal() const {
    return node_->is_terminal();
  }

  bool AST::has_children() const {
    return children_.size() > 0;
  }

  std::shared_ptr<AST> AST::get_child(std::size_t idx) const {
    if (idx >= children_.size()) {
      std::cerr << "Tried to access child outside of vector bounds" << std::endl;
      return nullptr;
    }

    return children_[idx];
  }

  const std::vector<std::shared_ptr<AST>>& AST::get_children() const {
    return children_;
  }

  std::vector<std::shared_ptr<AST>>& AST::get_children() {
    return const_cast<std::vector<std::shared_ptr<AST>>&>
      (const_cast<const AST*>(this)->get_children());
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
    ss << "  " << node_id << " [label=\"" << node_->get_gv_label() << "\"]" << std::endl;
    for (auto child : children_) {
      ss << "  " << node_id << " -- " << child->get_node_id() << std::endl;
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

  // TODO - get rid of this method
  std::size_t AST::get_level() const {
    std::size_t level = 0;
    auto* tmp = this;
    while(tmp->get_parent() != nullptr) {
      tmp = tmp->get_parent();
      level++;
    }
    return level;
  }

  int AST::get_depth() const {
    return depth_;
  }

  bool AST::is_valid() const {
    if (!is_full()) {
      return false;
    } 
    for (auto& child : children_) {
      if (!child->is_valid()) {
        return false;
      }
    }
    return true;
  }

  // OPERATORS
  bool AST::operator==(const AST& other) const {
    if (*node_ == *(other.get_node())) {
      if (children_.size() == other.get_children().size()) {
        for (std::size_t idx = 0; idx < children_.size(); idx++) {
          if (*children_[idx] != *other.get_children()[idx]) {
            return false;
          }
        }
        return true;
      }
    }
    return false;
  }

  bool AST::operator!=(const AST& other) const {
    return !(operator==(other));
  }

  // ITERATORS
  dfs_iterator AST::begin_dfs() {
    return dfs_iterator(this, this);
  }

  dfs_iterator AST::end_dfs() {
    return dfs_iterator(nullptr, this);
  }

  bfs_iterator AST::begin_bfs() {
    return bfs_iterator(this, this);
  }

  bfs_iterator AST::end_bfs() {
    return bfs_iterator(nullptr, this);
  }

}
