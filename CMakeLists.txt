cmake_minimum_required (VERSION 2.8.9)


set(CMAKE_CXX_COMPILER clang++)
add_definitions(-std=gnu++1z)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(Reflection)

include_directories("./include")
include_directories("./test")

file(GLOB src_list "./include/*.cpp" "./include/*.h")
file(GLOB src_list "./test/*.cpp" "./test/*.h")
file(GLOB src_list "./src/*.cpp" "./src/*.h")

add_executable(Reflection ${src_list})
