
# ConsoleCarRental

A console based application that allows you to enter cars and motorcycles into the system and have the systems state persist between application executions.

---

## Features

- Add vehicle (Car or Motorcycle)
- Search vehicle by ID
- Display all vehicles
- Display available vehicles only
- Rent vehicle
- Return vehicle

---

## Project Structure

project-root/
│
├── build/                     # Build output (ignored)
├── inc/                       # Header files
├── Scripts/                   # Helper scripts (e.g., build automation)
├── src/                       # Source files
|
├── .gitignore                 # Files and folders excluded from version control
├── CMakeLists.txt             # CMake build configuration
├── CMakePresets.json          # Optional CMake configuration presets
├── Cos2614_Assignment_1.pdf   # Assingment pdf
├── LICENSE.md                 # Project license
├── main.cpp                   # Application entry point
└── README.md                  # Project documentation

## Getting Started

## Requirements

Ensure the following are installed:

- [ ] C++ compiler (GCC, Clang, MSVC, etc)
- [ ] Qt 6.11.1 for specific toolchain you installed
- [ ] CMake (3.16+ recommended)
- [ ] Ninja (Any build executor that CMake supports is fine)

## Option 1: Using Qt Creator (Recommended)

Uncompress the project

1. Open Qt Creator
2. Select **File** → **Open File or Project**
3. Choose ```CMakeLists.txt```
4. Configure the project kit (Qt 6.11.1 + MinGW or your installed toolchain)
5. In **Projects** → **Run Settings**, enable:
- **Run in terminal** (Otherwise for console input/output will not work)
6. Build and run the project using the Qt Creator build/run buttons

## Option 2: Build from Terminal (CMake):

1. Traverse to your project root:
cd ProjectRoot

2. Generate Build Files

Run this from the project root (adjust paths based on your local installation)

cmake -S . -B build ^
-G "Build tool name" ^    
-DCMAKE_MAKE_PROGRAM="C:\Path\to\build\executor\program.executable_binary" ^
-DCMAKE_C_COMPILER="C:\Path\to\toolchain's\C\compiler.executable_binary" ^
-DCMAKE_CXX_COMPILER="C:\Path\to\toolchain's\C++\compiler.executable_binary" ^
-DCMAKE_PREFIX_PATH="C:\Path\to\Qt\toolChainUsed"

For example, Mine for Windows operating system with mingw64 toolchain is:

cmake -S . -B build ^
-G "Ninja" ^
-DCMAKE_MAKE_PROGRAM="C:\ninja\ninja.exe" ^
-DCMAKE_C_COMPILER="C:\msys64\mingw64\bin\gcc.exe" ^
-DCMAKE_CXX_COMPILER="C:\msys64\mingw64\bin\g++.exe" ^
-DCMAKE_PREFIX_PATH="C:\Qt\6.11.1\mingw_64" 

3. Build the Project

cmake --build build

4. Run the Application
cd build
ConsoleCarRental.exe

## Notes
- The application uses a console-based interface via QTextStream.
- Data is loaded on startup and saved on exit.
- Ensure the program is executed in a terminal for proper input handling.
- File paths are relative to the application working directory.
