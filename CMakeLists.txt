cmake_minimum_required(VERSION 3.10)
project(app)

set(CMAKE_CXX_STANDARD 17)

# Find wxWidgets and cpr
find_package(wxWidgets REQUIRED)
find_package(cpr CONFIG REQUIRED)

# Setup wxWidgets
include(${wxWidgets_USE_FILE})

include_directories(include)

# Add executable with WIN32 to avoid console window
add_executable(app WIN32 
    src/main.cpp
    src/Panel.cpp
    src/WindowMain.cpp
    src/PanelStart.cpp
)

# Link libraries
target_link_libraries(app PRIVATE cpr::cpr ${wxWidgets_LIBRARIES})
