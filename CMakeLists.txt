cmake_minimum_required(VERSION 3.10)
project(TerrainGenerator)

# Add the source files
set(SOURCES
    src/main.cpp
)

# Add the executable
add_executable(TerrainGenerator ${SOURCES})

# Find and link against the GLFW library
find_package(glfw3 REQUIRED)
target_link_libraries(TerrainGenerator PRIVATE glfw GLESv2)

# Include the directories for GLFW headers, glad headers, and your own headers
target_include_directories(TerrainGenerator PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/KHR
)

# Set the include directories for glad
target_include_directories(TerrainGenerator PRIVATE
    SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/glad
)

# Set C++ standard to C++11
target_compile_features(TerrainGenerator PRIVATE cxx_std_11)

