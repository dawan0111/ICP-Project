cmake_minimum_required(VERSION 3.21)

set(PACKAGE_NAME SIMPLE_ICP)
set(PACKAGE_VERSION 0.0.1)

project(${PACKAGE_NAME} VERSION ${PACKAGE_VERSION} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(${PACKAGE_NAME}_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(${PACKAGE_NAME}_MODULE_PATH "${${PACKAGE_NAME}_PATH}/module")
set(${PACKAGE_NAME}_THIRDPARTY_PATH "${${PACKAGE_NAME}_PATH}/thirdparty")

add_subdirectory(${${PACKAGE_NAME}_MODULE_PATH})
add_subdirectory(${${PACKAGE_NAME}_THIRDPARTY_PATH})

include(${CMAKE_SOURCE_DIR}/cmake/find_matplotlib.cmake)

add_executable(SVD_EXAMPLE src/svd_example.cpp)

target_link_libraries(SVD_EXAMPLE PRIVATE
    ICP
    matplotlib_cpp::matplotlib_cpp
)