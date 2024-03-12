cmake_minimum_required(VERSION 3.12)
project(linkshortener)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    main.cpp
    ShortenedLink.cpp
    LinkShortenerService.cpp
)

add_executable(linkshortener ${SOURCES})