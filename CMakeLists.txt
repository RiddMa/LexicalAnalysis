cmake_minimum_required(VERSION 3.17)
project(Lex)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES "*.cpp" "*/*.cpp" "*.h" "*/*.h")

add_executable(LEX ${SOURCES})