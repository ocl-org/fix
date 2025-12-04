
cmake_minimum_required(VERSION 3.15...3.31)

project(
  NetworkExample
  VERSION 1.0
  LANGUAGES CXX)

find_package(Boost REQUIRED COMPONENTS container)

add_executable(NetworkExample example.cc)

set_property(TARGET NetworkExample PROPERTY CXX_STANDARD 20)
target_include_directories(NetworkExample PUBLIC ../../include/ocl)
target_link_libraries(NetworkExample PRIVATE Boost::container)
