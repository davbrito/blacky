cmake_minimum_required(VERSION 3.10)

# set the project name
project(blacky VERSION 0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wall -Werror")

set(BUILD_FOLDER "./build")
set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(APPS_DIR "${PROJECT_SOURCE_DIR}/apps")
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/includes")
set(VENDOR_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor") 

file(GLOB_RECURSE SOURCE_FILES "${SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE HEADER_FILES "${SOURCE_DIR}/*.h")


# add the executable
add_executable(blacky-cli "${APPS_DIR}/main.cpp")
# add_executable(blacky-gui "${APPS_DIR}/main-gui.cpp")
                    

add_library(blacky-lib ${SOURCE_FILES})

find_package(fmt REQUIRED)
find_package(Boost REQUIRED COMPONENTS iostreams)
find_package(Microsoft.GSL REQUIRED)

target_include_directories(blacky-lib PUBLIC ${INCLUDE_DIR}) 
target_include_directories(blacky-cli PUBLIC ${INCLUDE_DIR})
 
target_link_libraries(blacky-cli PUBLIC blacky-lib fmt::fmt Boost::iostreams Microsoft.GSL::GSL)
target_link_libraries(blacky-lib PUBLIC fmt::fmt Boost::iostreams Microsoft.GSL::GSL)
