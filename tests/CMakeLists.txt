cmake_minimum_required(VERSION 3.20)
project(jpo_lab_tests)

set(CMAKE_CXX_STANDARD 20)

# GoogleTest via FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

# Only compile JSONTools.cpp
add_executable(JSONToolsTest
  ../src/JSONTools.cpp
  JSONToolsTest.cpp
)

# Include your headers from ../include
target_include_directories(JSONToolsTest PRIVATE ../include)

# nlohmann_json
find_package(nlohmann_json REQUIRED)
target_link_libraries(JSONToolsTest PRIVATE
  gtest
  gtest_main
  nlohmann_json::nlohmann_json
)

# Enable CTest integration
enable_testing()
add_test(NAME JSONToolsTest COMMAND JSONToolsTest)
