cmake_minimum_required(VERSION 3.16)
project(sts C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCES "src/*")

add_executable(sts ${SOURCES})

target_include_directories(sts PRIVATE 
    include
)