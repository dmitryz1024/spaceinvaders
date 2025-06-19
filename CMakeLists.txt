cmake_minimum_required(VERSION 3.10)
project(SpaceInvaders)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories("./include") 
link_directories("./lib")

add_executable(SpaceInvaders
    src/main.cpp
    src/Entity.cpp
    src/Player.cpp
    src/Enemy.cpp
    src/Bullet.cpp
    src/Explosion.cpp
    src/Game.cpp
)

target_link_libraries(SpaceInvaders pdcurses)