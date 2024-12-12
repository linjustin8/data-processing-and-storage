cmake_minimum_required(VERSION 3.14)
project(data-processing-and-storage)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(inMemoryDB src/inMemoryDB.cpp)
add_executable(data_processing_test test.cpp)

target_link_libraries(
  data_processing_test  # Use the chosen target name here
  GTest::gtest_main
  inMemoryDB
)

include(GoogleTest)
gtest_discover_tests(data_processing_test)