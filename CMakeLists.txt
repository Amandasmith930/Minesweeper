#cmake_minimum_required(VERSION 3.21)
#project(minesweeper)
#
#set(CMAKE_CXX_STANDARD 14)
#
#add_executable(minesweeper main.cpp)


cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(minesweeper)

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(Minesweeper main.cpp textures.cpp textures.h board.cpp board.h Random.cpp Random.h)
target_link_libraries(Minesweeper sfml-graphics sfml-audio)
