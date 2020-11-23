cmake_minimum_required (VERSION 3.8)

project ("menthol-parser")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory ("src")

find_package(GTest)
if(${GTEST_FOUND})
	enable_testing()
	add_subdirectory("unittest")
endif()
