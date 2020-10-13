cmake_minimum_required(VERSION 3.17)
project(Lex)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES "*.cpp")

add_executable(LEX ${SOURCES})