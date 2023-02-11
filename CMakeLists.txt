cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

# Set project name and version
project(Typy VERSION 0.1)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

# Enable debug symbols by default
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug
          CACHE STRING
          "Choose the type of build (Debug or Release)" FORCE)
endif()

# Set option to control setting the resource path variable
option(USE_INSTALL_RESOURCE_PATH "Set resource path to install location" OFF)

if(NOT USE_INSTALL_RESOURCE_PATH)
  set(RESOURCE_PATH "${PROJECT_SOURCE_DIR}/resources/")
else()
  set(RESOURCE_PATH "${CMAKE_INSTALL_PREFIX}/share/${CMAKE_PROJECT_NAME}/resources/")
endif()

# Generate config.h
configure_file(include/config.h.in config.h)

# Find SFML shared libraries
find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

# Compile executable
add_executable(Typy src/Game.cpp src/main.cpp)

# Set include directory search paths
target_include_directories(Typy PUBLIC ${PROJECT_BINARY_DIR} include/)

# Set executable RPATH
set_target_properties(Typy
        PROPERTIES
        INSTALL_RPATH
        "/usr/local/lib"
        )

# Link executable to required SFML modules
target_link_libraries(Typy sfml-graphics sfml-audio)

# install executable
install(TARGETS Typy DESTINATION bin)

# install resources
install(DIRECTORY resources DESTINATION /share/${CMAKE_PROJECT_NAME})