#ifndef KALEIDOSCOPE_PRINTER_HPP
#define KALEIDOSCOPE_PRINTER_HPP

#include <boost/variant/static_visitor.hpp>

#include <ostream>

#include "ast.hpp"

namespace kaleidoscope {
namespace ast {
class printer : public boost::static_visitor<void> {
public:
  printer(std::ostream &out, size_t tabsize = 2, size_t indent = 0);

  void operator()(double number) const;
  void operator()(const std::string &ident) const;
  void operator()(const ast::call &call) const;
  void operator()(const ast::operations &ops) const;

private:
  std::string tab(size_t spaces) const;

private:
  std::ostream &out;

public:
  size_t tabsize;
  size_t indent;
};

std::ostream &operator<<(std::ostream &out, const expr &in);
} // namespace ast
} // namespace kaleidoscope

#endif // !KALEIDOSCOPE_PRINTER_HPP
