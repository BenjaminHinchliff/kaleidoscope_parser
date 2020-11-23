#ifndef KALEIDOSCOPE_AST_HPP
#define KALEIDOSCOPE_AST_HPP

#include <boost/fusion/include/io.hpp>
#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>

#include <iostream>
#include <list>
#include <string>

namespace kaleidoscope {
namespace ast {
namespace x3 = boost::spirit::x3;

struct call;
struct operations;

struct expr : public x3::variant<double, std::string, x3::forward_ast<call>,
                                 x3::forward_ast<operations>> {
  using base_type::base_type;
  using base_type::operator=;
};

struct call {
  std::string callee;
  std::list<expr> args;
};

struct operation {
  char operator_;
  expr operand;
};

struct operations {
  expr first;
  std::list<operation> rest;
};

struct prototype {
  std::string name;
  std::list<std::string> args;
};

struct function {
  prototype proto;
  expr body;
};

struct top_function : public x3::variant<prototype, function> {
  using base_type::base_type;
  using base_type::operator=;
};

} // namespace ast
} // namespace kaleidoscope

#endif // !KALEIDOSCOPE_AST_HPP