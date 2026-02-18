cmake_minimum_required(VERSION 3.16)
project(GameServer
    VERSION 1.0
    LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(models)
add_subdirectory(core)
add_subdirectory(app)