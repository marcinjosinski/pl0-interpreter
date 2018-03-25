cmake_minimum_required(VERSION 3.2)
project(PL0_INTERPRETER VERSION 0.1 LANGUAGES CXX)

option(BUILD_TESTING "Build the unit tests" OFF)

add_subdirectory(src)
add_subdirectory(third_party EXCLUDE_FROM_ALL)
if(BUILD_TESTING)
  add_subdirectory(tests)
endif()
