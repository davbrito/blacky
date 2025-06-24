cmake_minimum_required(VERSION 3.10)

# set the project name
project(blacky VERSION 0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wall -Werror")

#find_package(range-v3 REQUIRED)
#find_package(Boost REQUIRED)

# add the executable
add_executable(blacky src/main.cpp)

add_library(blackylib src/blacky.cpp src/Mazo.cpp src/Jugador.cpp src/Carta.cpp src/tools.cpp)

target_link_libraries(blacky PUBLIC blackylib)

#target_link_libraries(Tutorial PRIVATE
#                           range-v3
#                           ${Boost_LIBRARIES}
#)

target_include_directories(blacky PUBLIC  "${PROJECT_BINARY_DIR}"
                                            "${PROJECT_SOURCE_DIR}"
)
