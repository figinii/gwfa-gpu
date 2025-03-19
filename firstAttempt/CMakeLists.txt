cmake_minimum_required (VERSION 3.20...3.31)
project (firstAttempt CXX CUDA)

message(STATUS cmakeDir: ${CMAKE_SOURCE_DIR})
include_directories(
  ${CMAKE_SOURCE_DIR}/source
  ${CMAKE_SOURCE_DIR}/include
)

find_package(CUDA REQUIRED)
include_directories(${CUDA_INCLUDE_DIRS})
link_directories(${CUDA_TOOLKIT_ROOT_DIR}/lib64)

add_executable (firstAttempt source/main.cu)

target_link_libraries (firstAttempt ${CUDA_LIBRARIES})