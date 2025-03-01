cmake_minimum_required(VERSION 3.10)
project(PixelFlowGL)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Include directories
include_directories(include)

# Add source files
set(SOURCES
    src/main.cpp
    src/objreader.cpp
)

# Add header files (optional, but useful for IDEs)
set(HEADERS
    include/objreader.h
    include/face.h
    include/model.h
    include/vertex.h
)

# Find GLFW
find_package(glfw3 REQUIRED)
find_package(GLUT REQUIRED)
find_library(GLU_LIBRARY GLU)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(${PROJECT_NAME} OpenGL::GL glfw GLUT::GLUT ${GLU_LIBRARY})