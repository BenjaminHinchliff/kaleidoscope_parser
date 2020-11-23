#ifndef KALEIDOSCOPE_AST_SIMPLIFY_HPP
#define KALEIDOSCOPE_AST_SIMPLIFY_HPP

#include <boost/variant/static_visitor.hpp>

#include "ast.hpp"

namespace kaleidoscope {
namespace ast {
class simplify_expr : public boost::static_visitor<ast::expr> {
public:
  ast::expr operator()(double number) const;
  ast::expr operator()(const std::string &ident) const;
  ast::expr operator()(ast::call call) const;
  ast::expr operator()(ast::operations ops) const;
};

class simplify : public boost::static_visitor<ast::top_function> {
public:
  ast::top_function operator()(ast::function function) const;
  ast::top_function operator()(const ast::prototype &prototype) const;
};
} // namespace ast
} // namespace kaleidoscope

#endif // !KALEIDOSCOPE_AST_SIMPLIFY_HPP
