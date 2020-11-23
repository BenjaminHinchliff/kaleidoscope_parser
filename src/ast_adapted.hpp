#ifndef KALEIDOSCOPE_AST_ADAPTED_HPP
#define KALEIDOSCOPE_AST_ADAPTED_HPP

#include <boost/fusion/include/adapt_struct.hpp>

#include "ast.hpp"

BOOST_FUSION_ADAPT_STRUCT(kaleidoscope::ast::call, callee, args)

BOOST_FUSION_ADAPT_STRUCT(kaleidoscope::ast::operation, operator_, operand)

BOOST_FUSION_ADAPT_STRUCT(kaleidoscope::ast::operations, first, rest)

BOOST_FUSION_ADAPT_STRUCT(kaleidoscope::ast::prototype, name, args)

BOOST_FUSION_ADAPT_STRUCT(kaleidoscope::ast::function, proto, body)

#endif // !KALEIDOSCOPE_AST_ADAPTED_HPP