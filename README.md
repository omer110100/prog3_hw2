# Dungeon Crawler – Omer Labinsky

## Description
This project implements a command-driven dungeon crawler game in C++.

The game loads commands from an input file, executes them sequentially,
and writes the results along with the final character statistics to an output file.
The implementation follows the interface and structure required by the
course-provided main.cpp.

## Project Structure
DungeonCrawler/
├─ src/                 # Source files (.cpp / .h)
├─ input.txt            # Input commands
├─ output.txt           # Program output
├─ CMakeLists.txt
└─ README.md

## Build Instructions
The project uses CMake.

cmake -S . -B build  
cmake --build build

## Run
After building, run the executable from the project root:

build/DungeonCrawler.exe

The program:
- Reads commands from input.txt
- Writes the game output and final statistics to output.txt

## Notes
- The project is compatible with the course-provided main.cpp.
- Output format strictly matches the specification.
- No interactive input is required; all commands are file-based.
