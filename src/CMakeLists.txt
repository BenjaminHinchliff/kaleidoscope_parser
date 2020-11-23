cmake_minimum_required(VERSION 3.8)

set(KALEIDOSCOPE_INCLUDE_PREFIX "../include")

set(KALEIDOSCOPE_INCLUDE
"${KALEIDOSCOPE_INCLUDE_PREFIX}/ast.hpp"
"${KALEIDOSCOPE_INCLUDE_PREFIX}/ast_adapted.hpp"
"${KALEIDOSCOPE_INCLUDE_PREFIX}/config.hpp"
"${KALEIDOSCOPE_INCLUDE_PREFIX}/parser.hpp"
"${KALEIDOSCOPE_INCLUDE_PREFIX}/parser_def.hpp"
"${KALEIDOSCOPE_INCLUDE_PREFIX}/ast_printer.hpp"
"${KALEIDOSCOPE_INCLUDE_PREFIX}/ast_simplify.hpp"
"${KALEIDOSCOPE_INCLUDE_PREFIX}/parse.hpp")

set(KALEIDOSCOPE_SRCS
"parser.cpp"
"ast_printer.cpp"
"ast_simplify.cpp"
"parse.cpp")

add_library(kaleidoscope_parse ${KALEIDOSCOPE_SRCS} ${KALEIDOSCOPE_INCLUDE})

target_include_directories(kaleidoscope_parse PUBLIC ${KALEIDOSCOPE_INCLUDE_PREFIX})

find_package(Boost 1.70.0 REQUIRED)
target_include_directories(kaleidoscope_parse PUBLIC ${Boost_INCLUDE_DIRS})
