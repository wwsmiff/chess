cmake_minimum_required(VERSION 3.24)
project(chess)

set(CMAKE_CXX_STANDARD 17)

add_executable(chess src/main.cpp src/board.cpp include/board.h include/types.h include/config.h src/piece.cpp include/piece.h include/position.h)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2 SDL2main SDL2_image)

