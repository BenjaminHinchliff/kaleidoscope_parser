#include "kaleidoscope/parser/ast_simplify.hpp"

namespace kaleidoscope {
namespace ast {
ast::expr simplify_expr::operator()(double number) const {
  return ast::expr(number);
}

ast::expr simplify_expr::operator()(const std::string &ident) const {
  return ast::expr(ident);
}

ast::expr simplify_expr::operator()(ast::call call) const {
  for (auto &arg : call.args) {
    arg = boost::apply_visitor(*this, arg);
  }
  return ast::expr(call);
}

ast::expr simplify_expr::operator()(ast::operations ops) const {
  if (ops.rest.empty()) {
    return boost::apply_visitor(*this, ops.first);
  } else {
    ops.first = boost::apply_visitor(*this, ops.first);
    for (auto &op : ops.rest) {
      op.operand = boost::apply_visitor(*this, op.operand);
    }
    return ast::expr(ops);
  }
}

ast::top_function simplify::operator()(ast::function function) const {
  function.body = boost::apply_visitor(simplify_expr{}, function.body);
  return ast::top_function(function);
}

ast::top_function simplify::operator()(const ast::prototype &prototype) const {
  return ast::top_function(prototype);
}

} // namespace ast
} // namespace kaleidoscope
