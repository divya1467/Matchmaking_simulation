project(core)

set(SOURCES
   src/Matchmaker.cpp
   src/ThreadPool.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    models
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_link_libraries(${PROJECT_NAME}_run {PROJECT_NAME})
