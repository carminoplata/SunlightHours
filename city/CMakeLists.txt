project(city)

#set(NAMESPACE cit)

file(GLOB_RECURSE HEADER_FILES include/public/*.h)
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

source_group("Interface Headers" FILES ${HEADER_FILES}) 
source_group("Source Files" FILES ${SOURCE_FILES})

add_library(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

#tell to the compiler to use CXX for linking the library
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX) 

#add_library(${NAMESPACE}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/public ${Boost_INCLUDE_DIRS})