cmake_minimum_required(VERSION 3.12)
project(game)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    main.cpp
    game.cpp
    user.cpp
)

add_executable(game ${SOURCES})