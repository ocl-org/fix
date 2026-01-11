# AMLALE: Hm?
cmake_minimum_required(VERSION 3.15...3.31)

project(
  FixExample
  VERSION 1.0
  LANGUAGES CXX)

find_package(Boost REQUIRED)

add_executable(FixExample example.cpp)
target_include_directories(FixExample PUBLIC ${BOOST_INCLUDE_DIRS})

set_property(TARGET FixExample PROPERTY CXX_STANDARD 20)
target_include_directories(FixExample PUBLIC ../../include/ocl)
target_link_libraries(FixExample PRIVATE ocl_fix)
