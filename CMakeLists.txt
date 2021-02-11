cmake_minimum_required(VERSION 3.17)
project(coursework)

set(CMAKE_CXX_STANDARD 20)

add_executable(coursework main.cpp Field.h Field.cpp Cell.h MyField.h EnemyField.h Ship.h Ship.cpp Cell.cpp Configuration.h Player.h Player.cpp Game.h Game.cpp Computer.h Computer.cpp)