cmake_minimum_required(VERSION 3.0.0)
project(people_detection)

set(CMAKE_SOURCE_DIR "${CMAKE_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/cmake")
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")
set(BIN_NAME "detection")

find_library(OpenCV REQUIRED)
find_library(Darknet REQUIRED)

set(
  SRC 
    ${PROJECT_SOURCE_DIR}/src/detection.cpp	
)
include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${OpenCV_INCLUDE_DIR}
  ${Darknet_INCLUDE_DIR}
)

set(OPT_FLAGS "-Ofast")

set(
  CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -std=c++11 -march=native ${OPT_FLAGS}"
)

add_executable(
  ${BIN_NAME} ${SRC}
)

target_link_libraries(
  ${BIN_NAME} 
    ${OpenCV_LIBRARIES}
    ${Darknet_LIBRARIES}
)
