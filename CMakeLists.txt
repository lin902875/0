cmake_minimum_required(VERSION 3.20)
project(ValorantESP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenCV
find_package(OpenCV REQUIRED)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${OpenCV_INCLUDE_DIRS})

# Source files
set(SOURCES
    src/main.cpp
    src/esp.cpp
    src/overlay.cpp
    src/math.cpp
)

set(HEADERS
    include/esp.h
    include/overlay.h
    include/math.h
    include/config.h
)

# Create executable
add_executable(ValorantESP ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(ValorantESP PRIVATE ${OpenCV_LIBS})

# Output directory
set_target_properties(ValorantESP PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
