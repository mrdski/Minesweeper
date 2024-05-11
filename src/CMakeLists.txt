cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Project3)

## If you want to link SFML statically
#set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
#set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")
set(SFML_DIR "/opt/SFML")
#set(SFML_DIR "/opt/homebrew/opt/sfml/lib/cmake/SFML")#set(SFML_DIR "/opt/SFML")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(Project3 main.cpp Board.cpp Board.h Tile.cpp Tile.h Random.cpp Random.h HelperMethods.cpp HelperMethods.h)
target_link_libraries(Project3 sfml-graphics sfml-audio sfml-window)