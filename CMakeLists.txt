cmake_minimum_required(VERSION 3.12) # version can be different

set(GOOGLETEST_VERSION 1.15.2)

project(my_cpp_project) #name of your project

enable_testing() #to  discover tests in test explorer 

add_subdirectory(googletest) # add googletest subdirectory

include_directories(googletest/include) # this is so we can #include <gtest/gtest.h>

add_executable(mytests mytests.cpp) # add this executable

target_link_libraries(mytests PRIVATE gtest) # link google test to this executable

include(GoogleTest)
gtest_discover_tests(mytests) # discovers tests by asking the compiled test executable to enumerate its tests