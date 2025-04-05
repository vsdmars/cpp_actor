cmake_minimum_required(VERSION 4.00)

# set the project name / version
project(CPP_ACTOR VERSION ${CPP_ACTOR_VERSION} LANGUAGES CXX)

add_executable(cppactor ${CMAKE_SOURCE_DIR}/src/main.cc)

# enable unit test
# https://stackoverflow.com/a/30264765
enable_testing()

# setup version
include("cmakeFiles/version.cmake")

# unit test and benchmark binary
# add_subdirectory(test)

# setup compile options
include("cmakeFiles/compile.cmake")

# setup create directories properties
include("cmakeFiles/create_dir.cmake")

