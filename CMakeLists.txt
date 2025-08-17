cmake_minimum_required(VERSION 4.00)
project (systemized)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add_executable(${PROJECT_NAME} src/main.cpp )

add_subdirectory(libraries/libremidi)

# Include all headers in include/ automatically
include_directories(${PROJECT_SOURCE_DIR}/include)

# Collect all .cpp files in src/ automatically
file(GLOB_RECURSE ALL_SOURCES "src/*.cpp")

# Create executable from all sources
add_executable(${PROJECT_NAME} ${ALL_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE libremidi)