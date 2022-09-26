cmake_minimum_required(VERSION 3.24.1)

project(Snake)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
add_executable(${PROJECT_NAME} snake.cpp)
target_link_libraries(${PROJECT_NAME} sfml-graphics)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/arial.ttf ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)