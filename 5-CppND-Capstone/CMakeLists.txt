cmake_minimum_required(VERSION 3.7)
project(capstone)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp*" )

add_executable(capstone ${SOURCES})

set_property(TARGET capstone PROPERTY CXX_STANDART 17)
target_compile_options(capstone INTERFACE -Wall -Wextra)
