cmake_minimum_required(VERSION 3.10)
project(FileCompressor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Find required packages
find_package(Boost REQUIRED)

# Set default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Different configurations
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -Wall -Wextra")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -DNDEBUG")
endif()

# Build main executable (Huffman tree implementation)
add_executable(myapp main.cpp src/Huffman.cpp src/Decompressor.cpp)
target_include_directories(myapp PRIVATE include)
target_link_libraries(myapp ${Boost_LIBRARIES})

# Include Boost headers
if(Boost_FOUND)
    target_include_directories(myapp PRIVATE ${Boost_INCLUDE_DIRS})
    message(STATUS "Boost found: ${Boost_VERSION}")
    message(STATUS "Boost include dirs: ${Boost_INCLUDE_DIRS}")
else()
    message(FATAL_ERROR "Boost not found! Please install boost development libraries.")
endif()



# Copy test file to build directory
configure_file(${CMAKE_SOURCE_DIR}/test.txt ${CMAKE_BINARY_DIR}/test.txt COPYONLY)