
## Specify mininum version of CMAKE
cmake_minimum_required(VERSION 2.16)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS ON)
## Project's Name
project(HW_RDT)


set(SOURCE_FILES main.cpp )

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)

