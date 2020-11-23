#include "ast_simplify.hpp"

namespace kaleidoscope {
namespace ast {
ast::expr simplify::operator()(double number) const {
  return ast::expr(number);
}

ast::expr simplify::operator()(const std::string &ident) const {
  return ast::expr(ident);
}

ast::expr simplify::operator()(ast::call call) const {
  for (auto &arg : call.args) {
    arg = boost::apply_visitor(*this, arg);
  }
  return ast::expr(call);
}

ast::expr simplify::operator()(ast::operations ops) const {
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

} // namespace ast
} // namespace kaleidoscope
