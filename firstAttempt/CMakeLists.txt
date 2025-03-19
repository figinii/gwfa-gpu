cmake_minimum_required (VERSION 3.20...3.31)
project (firstAttempt CXX)

# require seqan3 with a version between >=3.0.0 and <4.0.0
list (APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/../seqan3/cmake")
find_package (seqan3 3.0 REQUIRED)

message(STATUS cmakeDir: ${CMAKE_SOURCE_DIR})
include_directories(
  ${CMAKE_SOURCE_DIR}/source
  ${CMAKE_SOURCE_DIR}/include
)

# find_package(CUDA REQUIRED)


add_executable (firstAttempt source/main.cpp)

target_link_libraries (firstAttempt seqan3::seqan3)