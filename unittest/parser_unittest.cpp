#include <gtest/gtest.h>

#include <boost/spirit/home/x3.hpp>

#include <array>

#include <kaleidoscope/parser/parse.hpp>

namespace x3 = boost::spirit::x3;
using x3::ascii::space;

namespace ast = kaleidoscope::ast;

TEST(Parser, Number) {
  std::string numberStr = "21.2";

  auto iter = numberStr.cbegin();
  auto end = numberStr.cend();

  ast::expr numberExpr;
  bool r = x3::phrase_parse(iter, end, kaleidoscope::expr(), space, numberExpr);
  ASSERT_TRUE(r);
  ASSERT_EQ(iter, end);

  numberExpr = boost::apply_visitor(ast::simplify_expr{}, numberExpr);

  ASSERT_EQ(boost::get<double>(numberExpr), std::stod(numberStr));
}

TEST(Parser, Variable) {
  std::string variableStr = "z_asf123";

  auto iter = variableStr.cbegin();
  auto end = variableStr.cend();

  ast::expr variableExpr;
  bool r =
      x3::phrase_parse(iter, end, kaleidoscope::expr(), space, variableExpr);
  ASSERT_TRUE(r);
  ASSERT_EQ(iter, end);

  variableExpr = boost::apply_visitor(ast::simplify_expr{}, variableExpr);

  ASSERT_EQ(boost::get<std::string>(variableExpr), variableStr);
}

TEST(Parser, Call) {
  std::string callStr = "func(a, 234)";

  auto iter = callStr.cbegin();
  auto end = callStr.cend();

  kaleidoscope::ast::expr callExpr;
  bool r = x3::phrase_parse(iter, end, kaleidoscope::expr(), space, callExpr);
  ASSERT_TRUE(r);
  ASSERT_EQ(iter, end);

  callExpr = boost::apply_visitor(ast::simplify_expr{}, callExpr);

  const auto &call = boost::get<x3::forward_ast<ast::call>>(callExpr).get();
  ASSERT_EQ(call.callee, "func");
  auto argIter = call.args.cbegin();
  ASSERT_EQ(boost::get<std::string>(*argIter++), "a");
  ASSERT_EQ(boost::get<double>(*argIter++), 234);
  ASSERT_EQ(argIter, call.args.cend());
}

TEST(Parser, Operations) {
  std::string opsStr = "1 + a * 3";

  auto iter = opsStr.cbegin();
  auto end = opsStr.cend();

  ast::expr opsExpr;
  bool r = x3::phrase_parse(iter, end, kaleidoscope::expr(), space, opsExpr);
  ASSERT_TRUE(r);
  ASSERT_EQ(iter, end);

  opsExpr = boost::apply_visitor(ast::simplify_expr{}, opsExpr);

  const auto &ops = boost::get<x3::forward_ast<ast::operations>>(opsExpr).get();
  ASSERT_EQ(boost::get<double>(ops.first), 1);
  const auto &first = *ops.rest.cbegin();
  ASSERT_EQ(first.operator_, '+');
  const auto &nestedOps =
      boost::get<x3::forward_ast<ast::operations>>(first.operand).get();
  ASSERT_EQ(boost::get<std::string>(nestedOps.first), "a");
  const auto &nestedFirst = *nestedOps.rest.cbegin();
  ASSERT_EQ(nestedFirst.operator_, '*');
  ASSERT_EQ(boost::get<double>(nestedFirst.operand), 3);
}

TEST(Parser, Prototype) {
  std::string protoStr = "proto(xy, zyy, x)";

  auto iter = protoStr.cbegin();
  auto end = protoStr.cend();

  ast::prototype proto;
  bool r = x3::phrase_parse(iter, end, kaleidoscope::proto(), space, proto);
  ASSERT_TRUE(r);
  ASSERT_EQ(iter, end);

  ASSERT_EQ(proto.name, "proto");

  std::array<std::string, 3> args{"xy", "zyy", "x"};
  size_t i = 0;
  for (const std::string &arg : proto.args) {
    ASSERT_EQ(arg, args[i++]);
  }
}

TEST(Parser, Extern) {
  std::string externStr = "extern proto()";

  ast::result externExpr;
  bool r = kaleidoscope::parse(externStr, externExpr);
  ASSERT_TRUE(r);

  const auto &externFunc = boost::get<ast::top_function>(externExpr);

  const auto &extern_ = boost::get<ast::prototype>(externFunc);
  ASSERT_EQ(extern_.name, "proto");
  ASSERT_TRUE(extern_.args.empty());
}

TEST(Parser, Function) {
  std::string functionStr = "def two() 2";
  ast::result functionExpr;
  bool r = kaleidoscope::parse(functionStr, functionExpr);
  ASSERT_TRUE(r);

  const auto functionFunc = boost::get<ast::top_function>(functionExpr);

  auto &function = boost::get<ast::function>(functionFunc);
  ASSERT_EQ(function.proto.name, "two");
  ASSERT_TRUE(function.proto.args.empty());

  ASSERT_EQ(boost::get<double>(function.body), 2);
}
