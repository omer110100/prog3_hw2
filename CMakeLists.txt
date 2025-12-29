cmake_minimum_required(VERSION 3.16)
project(DungeonCrawler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(DungeonCrawler
    src/main.cpp
    src/Utils.cpp
    src/Item.cpp
    src/Monster.cpp
    src/Room.cpp
    src/Character.cpp
    src/Dungeon.cpp
    src/Game.cpp
)

target_include_directories(DungeonCrawler PRIVATE src)

if (MSVC)
  target_compile_options(DungeonCrawler PRIVATE /W4)
else()
  target_compile_options(DungeonCrawler PRIVATE -Wall -Wextra -Wpedantic)
endif()
