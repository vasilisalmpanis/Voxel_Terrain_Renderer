cmake_minimum_required(VERSION 3.10)
project(TerrainGenerator)

# Add the source files
set(SOURCES
    src/main.cpp
    glad/glad.c
)

# Add the executable
add_executable(TerrainGenerator ${SOURCES})

# Find and link against the GLFW library
find_package(glfw3 REQUIRED)
target_link_libraries(TerrainGenerator PRIVATE glfw)

# Include the directories for GLFW headers
target_include_directories(TerrainGenerator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/glad)
target_include_directories(TerrainGenerator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(include)
target_include_directories(TerrainGenerator PRIVATE ${GLFW_INCLUDE_DIRS})

# Set C++ standard to C++11
target_compile_features(TerrainGenerator PRIVATE cxx_std_11)

