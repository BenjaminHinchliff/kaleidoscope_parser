#include "kaleidoscope/parser/ast_printer.hpp"

namespace kaleidoscope {
namespace ast {
printer::printer(std::ostream &out, size_t tabsize, size_t indent)
    : out(out), tabsize(tabsize), indent(indent) {}

void printer::operator()(double number) const {
  out << tab(indent) << "num{" << number << '}';
}

void printer::operator()(const std::string &ident) const {
  out << tab(indent) << "ident{" << ident << '}';
}

void printer::operator()(const ast::call &call) const {
  out << tab(indent) << "call{\n";
  out << tab(indent + tabsize) << "callee{" << call.callee << "},\n";
  out << tab(indent + tabsize) << "args{\n";
  if (!call.args.empty()) {
    for (auto it = call.args.cbegin(), end = call.args.cend(); it != end;
         ++it) {
      boost::apply_visitor(printer(out, tabsize, indent + 2 * tabsize), *it);
      if (std::next(it) != end) {
        out << ",\n";
      }
    }
  }
  out << '\n';
  out << tab(indent + tabsize) << "}\n";
  out << tab(indent) << "}";
}

void printer::operator()(const ast::operations &ops) const {
  out << tab(indent) << "ops{\n";
  boost::apply_visitor(printer(out, tabsize, indent + tabsize), ops.first);
  for (const auto &op : ops.rest) {
    out << '\n'
        << tab(indent + tabsize) << "op{" << op.operator_ << '}' << '\n';
    boost::apply_visitor(printer(out, tabsize, indent + tabsize), op.operand);
  }
  out << '\n' << tab(indent) << '}';
}

std::string printer::tab(size_t spaces) const {
  std::string tabs;
  for (size_t i = 0; i < spaces; ++i) {
    tabs += ' ';
  }
  return tabs;
}

std::ostream &operator<<(std::ostream &out, const expr &in) {
  boost::apply_visitor(printer(out), in);
  return out;
}
} // namespace ast
} // namespace kaleidoscope
