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
   * Run `.\sunlighthours <json_file>`

### Linux/MacOS
1. Open command line
2. Go to cleaning_robot
3. Run `cmake -s . -B <output_folder_build> -DBOOST_ROOT=<boost_path>` Ex. `cmake -s . -B build -DBOOST_ROOT=/usr/lib/boost `
4. Go to build folder
5. Run `make install`: it will create the executable file "sunlighthours" inside bin/osx (for OSX platform) or insde bin/linux (for Unix platform) folder. You can use the same command for windows. The executable file will be into bin/windows
6. Run `./sunlighthours <json_file>`

### Tests

Inside the folder there are 3 json files:

1. test.json: it defines the city like the describe example in pdf.
2. bad_forma1.json: it defines a city with character values for apartment_height field
3. bad_forma2.json: it defines a city with character values for apartments_count field
4. bad_forma3.json: it defines a city with character values for distance field

### Limitations

The application will work only under the following consideration:

1. Day of interest: Winter Solstice (22nd December)
2. Sunrise: 8:14 / Sunset: 17:25
3. Sunlight hours are observed at each hour => sun is moved by 15° degrees each hour. (The sun's 'movement is illusory. The Earth is moving by 15° degrees)
