cmake_minimum_required(VERSION 3.20)
project(2DGameCPP)

set(CMAKE_CXX_STANDARD 23)

add_executable(2DGameCPP main.cpp player/Player.h player/Score.h player/Projectile.h environment/EnvironmentItem.h)
if (NOT TARGET raylib)
    find_package(raylib 2.5.0 REQUIRED)
endif()
target_link_libraries(${PROJECT_NAME} raylib)