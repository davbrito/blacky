#!/bin/bash
# show commands
# set -e

# Define help message
show_help() {
  echo """
  Commands
  ---------------------------------------------------------
  install       : install conan dependancies 
  build         : build the app 
  """
}

build(){
    # mkdir -p build && cd build
    # cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
    # cmake --build .
    cmake --preset conan-release
    cmake  --build --preset conan-release
}

case "$1" in

  install )
    conan install . --profile:all=./profiles/default -b build_type=Release "${@:2}"
  ;;

  build )
    build "${@:2}"
  ;;

    run )
        ./build/Release/blacky-app
    ;;

    brun )
        build "${@:2}" && ./build/Release/blacky-app
    ;;

  * )
    show_help
  ;;

esac