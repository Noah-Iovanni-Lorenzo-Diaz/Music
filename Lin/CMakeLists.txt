cmake_minimum_required(VERSION 3.10)
project(music)

# Find SDL2
find_package(SDL2 REQUIRED)

# Include SDL2 headers
include_directories(${SDL2_INCLUDE_DIRS})

# Set the source files for your project
set(SOURCE_FILES src/music.cc)

# Create an executable
add_executable(music ${SOURCE_FILES})

# Link against SDL2 libraries
target_link_libraries(music ${SDL2_LIBRARIES})
