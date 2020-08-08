project(api)

#set(NAMESPACE api)

SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} ${BOOST_ROOT})
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${BOOST_ROOT}/lib")

file(GLOB_RECURSE HEADER_FILES include/public/*.h)
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

source_group("Interface Headers" FILES ${HEADER_FILES}) 
source_group("Source Files" FILES ${SOURCE_FILES})

add_library(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

#tell to the compiler to use CXX for linking the library
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX) 

add_library(${NAMESPACE}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/public ../Utils/include ${Boost_INCLUDE_DIRS})
#target_link_libraries(${PROJECT_NAME} PRIVATE )
target_link_libraries(${PROJECT_NAME} PUBLIC city parser)