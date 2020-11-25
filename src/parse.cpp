#include "kaleidoscope/parser/parse.hpp"

namespace kaleidoscope {
bool parse(const std::string &input, ast::result &output) {
  parser::iterator_type iter = input.cbegin();
  parser::iterator_type end = input.cend();

  bool s = x3::phrase_parse(iter, end, result(), x3::ascii::space, output);
  if (!s || iter != end) {
    return false;
  }
  output = boost::apply_visitor(ast::simplify_result{}, output);
  return true;
}

bool parse_all(const std::string &input, std::list<ast::result> &output) {
  parser::iterator_type iter = input.cbegin();
  parser::iterator_type end = input.cend();

  bool s = x3::phrase_parse(iter, end, result_all(), x3::ascii::space, output);
  if (!s || iter != end) {
    return false;
  }
  for (ast::result &part : output) {
    part = boost::apply_visitor(ast::simplify_result{}, part);
  }
  return true;
}
} // namespace kaleidoscope
