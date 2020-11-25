#ifndef KALEIDOSCOPE_EMPLOYEE_HPP
#define KALEIDOSCOPE_EMPLOYEE_HPP

#include <boost/spirit/home/x3.hpp>

#include "ast.hpp"

namespace kaleidoscope {
namespace parser {
namespace x3 = boost::spirit::x3;
class expr_class;
using expr_type = x3::rule<expr_class, ast::expr>;
class prototype_class;
using prototype_type = x3::rule<prototype_class, ast::prototype>;
class top_function_class;
using top_function_type = x3::rule<top_function_class, ast::top_function>;
class result_class;
using result_type = x3::rule<result_class, ast::result>;
BOOST_SPIRIT_DECLARE(expr_type, prototype_type, top_function_type, result_type);
} // namespace parser

parser::expr_type expr();
parser::prototype_type proto();
parser::top_function_type top_function();
parser::result_type result();
} // namespace kaleidoscope

#endif // !KALEIDOSCOPE_EMPLOYEE_HPP
