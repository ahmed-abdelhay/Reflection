cmake_minimum_required (VERSION 3.1)

project(Reflection)

set(CMAKE_CXX_STANDARD 14)

include_directories("./include")
include_directories("./test")

file(GLOB src_list "./test/*.cpp" "./test/*.h")
file(GLOB src_list "./src/*.cpp" "./src/*.h")

add_executable(Reflection ${src_list})
