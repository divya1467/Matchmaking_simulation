cmake_minimum_required(VERSION 3.16)
project(core)
add_library(core STATIC src/MatchMaker.cpp src/ThreadPool.cpp src/PlayerManager.cpp src/PlayerSimulator.cpp)
target_include_directories(core PUBLIC include)
target_link_libraries(core PUBLIC models)

find_package(Threads REQUIRED)
target_link_libraries(core PUBLIC Threads::Threads)
