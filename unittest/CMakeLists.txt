cmake_minimum_required(VERSION 3.8)

add_executable(kaleidoscope_parser_unittests "parser_unittest.cpp")

target_link_libraries(kaleidoscope_parser_unittests PUBLIC kaleidoscope_parser)

target_link_libraries(kaleidoscope_parser_unittests PUBLIC GTest::GTest GTest::Main)

include(GoogleTest)
gtest_add_tests(TARGET kaleidoscope_parser_unittests)
