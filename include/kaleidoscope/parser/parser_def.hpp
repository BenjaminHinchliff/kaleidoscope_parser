#ifndef KALEIDOSCOPE_EMPLOYEE_DEF_HPP
#define KALEIDOSCOPE_EMPLOYEE_DEF_HPP

#include "ast.hpp"
#include "ast_adapted.hpp"
#include "parser.hpp"

namespace kaleidoscope {
namespace parser {
namespace x3 = boost::spirit::x3;

using x3::double_;
using x3::ascii::char_;
using x3::ascii::lit;

const x3::rule<class ident, std::string> ident = "identifier";
const x3::rule<class call, ast::call> call = "call";
const x3::rule<class term, ast::operations> term = "term";
const x3::rule<class factor, ast::expr> factor = "factor";
const x3::rule<class nested, ast::expr> nested = "nested";
const x3::rule<class operations, ast::operations> operations = "operations";
const expr_type expr = "expression";

const prototype_type prototype = "prototype";

const x3::rule<class extern_, ast::prototype> extern_ = "extern";
const x3::rule<class function, ast::function> function = "function";
const top_function_type top_function = "top function";

const result_type result = "parsing result";

const auto ident_def = char_("A-Za-z_") >> *char_("A-Za-z_0-9");
const auto call_def = ident >> '(' >> -(expr % ',') >> ')';

const auto factor_def = nested | '(' >> expr >> ')';
const auto term_def = factor >>
                      *((char_('*') >> factor) | (char_('/') >> factor));

const auto operations_def = term >>
                            *((char_('+') >> term) | (char_('-') >> term));

const auto nested_def = double_ | call | ident;

const auto expr_def = operations | nested;

const auto prototype_def = ident >> '(' >> -(ident % ',') >> ')';

const auto extern__def = lit("extern") >> prototype;
const auto function_def = lit("def") >> prototype >> expr;
const auto top_function_def = extern_ | function;

const auto result_def = top_function | expr;

BOOST_SPIRIT_DEFINE(ident, call, term, factor, operations, nested, expr,
                    prototype, extern_, function, top_function, result);
} // namespace parser

parser::expr_type expr() { return parser::expr; }

parser::prototype_type proto() { return parser::prototype; }

parser::top_function_type top_function() { return parser::top_function; }

parser::result_type result() { return parser::result; }
} // namespace kaleidoscope

#endif // !KALEIDOSCOPE_EMPLOYEE_DEF_HPP
