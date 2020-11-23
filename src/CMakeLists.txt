cmake_minimum_required(VERSION 3.8)

set(KALEIDOSCOPE_INCLUDE
"ast.hpp"
"ast_adapted.hpp"
"config.hpp"
"parser.hpp"
"parser_def.hpp"
"ast_printer.hpp"
"ast_simplify.hpp")

set(KALEIDOSCOPE_SRCS
"parser.cpp"
"ast_printer.cpp"
"ast_simplify.cpp")

add_library(kaleidoscope_parser ${KALEIDOSCOPE_SRCS} ${KALEIDOSCOPE_INCLUDE})

target_include_directories(kaleidoscope_parser PUBLIC ".")

find_package(Boost 1.70.0 REQUIRED)
target_include_directories(kaleidoscope_parser PUBLIC ${Boost_INCLUDE_DIRS})
