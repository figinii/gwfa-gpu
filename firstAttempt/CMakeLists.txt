cmake_minimum_required (VERSION 3.20...3.31)
project (firstAttempt CXX)

message(STATUS cmakeDir: ${CMAKE_SOURCE_DIR})
include_directories(
  ${CMAKE_SOURCE_DIR}/source
  ${CMAKE_SOURCE_DIR}/include
)

# find_package(CUDA REQUIRED)

add_executable (firstAttempt source/main.cpp)

target_link_libraries (firstAttempt)