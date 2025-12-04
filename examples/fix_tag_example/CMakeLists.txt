
cmake_minimum_required(VERSION 3.15...3.31)

project(
  FixExample
  VERSION 1.0
  LANGUAGES CXX)

find_package(Boost REQUIRED COMPONENTS container)

add_executable(FixExample example.cc)

set_property(TARGET FixExample PROPERTY CXX_STANDARD 20)
target_include_directories(FixExample PUBLIC ../../include/ocl)
target_link_libraries(FixExample PRIVATE Boost::container)
