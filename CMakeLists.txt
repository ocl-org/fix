# PURPOSE: FIX module CMakeLists.

cmake_minimum_required(VERSION 3.10)
project(ocl_fix)

find_package(Boost REQUIRED)

add_library(ocl_fix src/fix/parser_impl.cpp)
target_link_libraries(ocl_fix boost_core)
target_include_directories(ocl_fix PUBLIC ${BOOST_INCLUDE_DIRS})

install(DIRECTORY include/ DESTINATION include)
install(TARGETS ocl_fix DESTINATION lib)

set_property(TARGET ocl_fix PROPERTY CXX_STANDARD 20)

