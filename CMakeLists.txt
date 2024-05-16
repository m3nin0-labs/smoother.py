cmake_minimum_required(VERSION 3.15...3.26)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-O3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

project(_smoother)

# C++ files
include_directories("${CMAKE_SOURCE_DIR}/src")

file (GLOB SOURCE_FILES "src/*.cpp")
file (GLOB HEADER_FILES "src/carma/*.h" "src/carma/carma/*.h")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES} ${HEADER_FILES} )

# Python
find_package(Python COMPONENTS Interpreter Development.Module REQUIRED)

# Pybind11
find_package(pybind11 CONFIG REQUIRED)
pybind11_add_module(_smoother ${SOURCE_FILES})

# Armadillo
find_library(ARMADILLO_LIB armadillo HINTS /usr/local/lib/ REQUIRED)
target_link_libraries(_smoother PUBLIC ${ARMADILLO_LIB})

target_compile_definitions(_smoother PRIVATE VERSION_INFO=${PROJECT_VERSION})
install(TARGETS _smoother LIBRARY DESTINATION .)
