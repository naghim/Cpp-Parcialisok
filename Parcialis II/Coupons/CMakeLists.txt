cmake_minimum_required(VERSION 3.12)
project(couponcode)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    main.cpp
    CouponCode.cpp
    RedeemService.cpp
)

add_executable(couponcode ${SOURCES})