cmake_minimum_required(VERSION 3.0.0)
project(SunlightHours VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)

#if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
#  set(CMAKE_TOOLCHAIN_FILE Platform/windows.cmake)
#elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
#  set(CMAKE_TOOLCHAIN_FILE Platform/linux.cmake)
#elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
#  set(CMAKE_TOOLCHAIN_FILE Platform/osx.cmake)
#endif()

if(NOT BOOST_ROOT)
  message(FATAL_ERROR "Run cmake -DBOOST_ROOT=<boost_path>")
endif()


set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.69.0 REQUIRED) 
if(NOT Boost_FOUND)
  message(FATAL_ERROR "BOOST Not Found or older than minimal version")
endif()


#include(CTest)
#enable_testing()

include_directories(include)
file(GLOB_RECURSE HEADER_FILES include/public/*.h)
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

add_definitions(-DBOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE)
add_subdirectory(Utils)
add_subdirectory(Parser)
add_subdirectory(Robot)


add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC sunlighthours)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/public)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

#used for create the binary package after installation into program files
#install(TARGETS cleaning_robot DESTINATION bin)