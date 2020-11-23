#include "parse.hpp"

namespace kaleidoscope {
bool parse(const std::string &input, ast::top_function &output) {
  parser::iterator_type iter = input.cbegin();
  parser::iterator_type end = input.cend();

  bool s =
      x3::phrase_parse(iter, end, top_function(), x3::ascii::space,
                   output);
  if (!s || iter != end) {
    return false;
  }
  output = boost::apply_visitor(ast::simplify{}, output);
  return true;
}
} // namespace kaleidoscope
