cmake_minimum_required(VERSION 3.0)
project(five C)

set(CMAKE_C_STANDARD 99)

add_compile_options(-O3 -Wall -Wextra -Wshadow -Wpointer-arith -Wcast-qual -Winline -Wunreachable-code)
add_executable(five five.c bot.c game.c acm.c)
