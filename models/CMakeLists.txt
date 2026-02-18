cmake_minimum_required(VERSION 3.16)
project(models)
add_library(models STATIC src/Match.cpp src/Player.cpp)
target_include_directories(models PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)