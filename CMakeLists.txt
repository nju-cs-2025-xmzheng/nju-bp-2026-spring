cmake_minimum_required(VERSION 3.16)
project(sts C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

file(GLOB_RECURSE LIB_SOURCES "src/*")
add_library(sts_lib ${LIB_SOURCES})
target_include_directories(sts_lib PUBLIC include)

add_executable(sts main.c)
target_link_libraries(sts PRIVATE sts_lib)

enable_testing()

macro(add_sts_test name src_file)
    add_executable(${name} ${src_file})
    target_link_libraries(${name} PRIVATE sts_lib)
    add_test(NAME ${name} COMMAND ${name})
endmacro()

add_sts_test(check_card tests/test_card.c)
