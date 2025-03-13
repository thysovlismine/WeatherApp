cmake_minimum_required(VERSION 3.10)
project(WxRestClient)

set(CMAKE_CXX_STANDARD 17)

# Find wxWidgets and cpr
find_package(wxWidgets REQUIRED)
find_package(cpr CONFIG REQUIRED)

# Setup wxWidgets
include(${wxWidgets_USE_FILE})

# Add executable with WIN32 to avoid console window
add_executable(WxRestClient WIN32 main.cpp)

# Link libraries
target_link_libraries(WxRestClient PRIVATE cpr::cpr ${wxWidgets_LIBRARIES})
