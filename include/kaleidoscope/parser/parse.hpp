#ifndef KALEIDOSCOPE_PARSE_HPP
#define KALEIDOSCOPE_PARSE_HPP

#include "config.hpp"
#include "ast.hpp"
#include "ast_adapted.hpp"
#include "ast_simplify.hpp"
#include "parser.hpp"

namespace kaleidoscope {
namespace x3 = boost::spirit::x3;

bool parse(const std::string &input, ast::result &output);
bool parse_all(const std::string &input, std::list<ast::result> &output);
} // namespace kaleidoscope

#endif // !KALEIDOSCOPE_PARSE_HPP
