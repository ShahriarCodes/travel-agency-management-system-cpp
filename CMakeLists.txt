cmake_minimum_required(VERSION 3.19)
project(Travel_agency_project)

set(CMAKE_CXX_STANDARD 14)

add_executable(Travel_agency_project main.cpp)
add_executable(test test.cpp generateID.cpp)
#add_executable(genID generateID.cpp)