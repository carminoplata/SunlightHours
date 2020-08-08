# SunlightHours

## Requirements
Install:
* Boost: required minimum version 1.69.0
* CMake: required minimum version 3.0.0
* C++14
* Make
* If you're running on Windows Platform, MinGW  and Visual Studio are required.

## How to build and run

### Windows 
1. Go to cleaning_robot folder
2. Run `cmake -s . -B <output_folder_build> -DBOOST_ROOT=<boost_path>` Ex. `cmake -s . -B build -DBOOST_ROOT=C:\Users\CarmineSacco\Projects\Libraries\boost ` 
3. Go to build folder. It will contains all Visual Studio projects 
4. Open cleaning_robot.sln or cleaning_robot.vproj
5. Build in Release mode
6. For running:
   * open command line into cleaning_robot/build/Release folder 
   * Run `.\cleaning_robot <source_file> <result_file>

### Linux/MacOS
1. Open command line
2. Go to cleaning_robot
3. Run `cmake -s . -B <output_folder_build> -DBOOST_ROOT=<boost_path>` Ex. `cmake -s . -B build -DBOOST_ROOT=/usr/lib/boost `
4. Go to build folder
5. Run `make`: it will create the executable file "cleaning_robot" inside build folder
6. Run `./sunlighthours <source_file> <result_file>`
