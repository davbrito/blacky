cmake_minimum_required(VERSION 3.10)

# set the project name
project(blacky VERSION 0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wall -Werror")

set(BUILD_FOLDER "./build")
set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(APPS_DIR "${PROJECT_SOURCE_DIR}/apps")
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/includes")

file(GLOB SOURCE_FILES "${SOURCE_DIR}/*.cpp")
file(GLOB HEADER_FILES "${SOURCE_DIR}/*.h")

# add the executable
add_executable(blacky-app src/main.cpp)
                    

add_library(blacky-lib ${SOURCE_FILES})

find_package(fmt REQUIRED)
find_package(Boost REQUIRED COMPONENTS iostreams)

target_include_directories(blacky-lib PUBLIC ${INCLUDE_DIR})
target_link_libraries(blacky-app PUBLIC blacky-lib fmt::fmt)
target_link_libraries(blacky-lib PUBLIC fmt::fmt Boost::iostreams)
