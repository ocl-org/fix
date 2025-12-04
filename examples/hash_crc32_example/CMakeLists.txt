
cmake_minimum_required(VERSION 3.15...3.31)

project(
  HashExample
  VERSION 1.0
  LANGUAGES CXX)

find_package(Boost REQUIRED COMPONENTS container)

add_executable(HashExample example.cc)

set_property(TARGET HashExample PROPERTY CXX_STANDARD 20)
target_include_directories(HashExample PUBLIC ../../include/ocl)
target_link_libraries(HashExample PRIVATE Boost::container)
