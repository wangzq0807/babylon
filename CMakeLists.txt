cmake_minimum_required (VERSION 3.0)
include(precheck.cmake)

option (WITH_THREADS "Enable multithreading support" ON)

add_compile_options(-std=c++11)

add_subdirectory(paxos)

enable_testing()
