cmake_minimum_required(VERSION 3.21)

set(LIBRARY_NAME ICP)
set(LIBRARY_VERSION 0.0.1)

project(${LIBRARY_NAME} VERSION ${LIBRARY_VERSION} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(${LIBRARY_NAME}_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(${LIBRARY_NAME}_SOURCE_PATH "${${LIBRARY_NAME}_PATH}/src")
set(${LIBRARY_NAME}_INCLUDE_PATH "${${LIBRARY_NAME}_PATH}/include")

include(${CMAKE_SOURCE_DIR}/cmake/find_eigen.cmake)

set(${LIBRARY_NAME}_SOURCE_FILES
  src/icp.cpp
  src/utils.cpp
)
add_library(${LIBRARY_NAME}
  ${${LIBRARY_NAME}_SOURCE_FILES}
)
target_include_directories(${LIBRARY_NAME} PUBLIC
  ${${LIBRARY_NAME}_INCLUDE_PATH}
  ${EIGEN3_INCLUDE_DIRS}
)
target_link_libraries(${LIBRARY_NAME} PRIVATE
    ${EIGEN3_LIBS}
)

target_compile_options(${LIBRARY_NAME} PRIVATE
  -Wall -Wextra -Wpedantic -Werror
)