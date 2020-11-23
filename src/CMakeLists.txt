cmake_minimum_required(VERSION 3.8)

set(KALEIDOSCOPE_INCLUDE_PREFIX "../include")

set(KALEIDOSCOPE_SRCS
"parser.cpp"
"ast_printer.cpp"
"ast_simplify.cpp"
"parse.cpp")

add_library(kaleidoscope_parse ${KALEIDOSCOPE_SRCS})

target_include_directories(kaleidoscope_parse PUBLIC ${KALEIDOSCOPE_INCLUDE_PREFIX})

find_package(Boost 1.70.0 REQUIRED)
target_include_directories(kaleidoscope_parse PUBLIC ${Boost_INCLUDE_DIRS})
