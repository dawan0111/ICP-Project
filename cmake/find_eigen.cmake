message(STATUS "Start Finding Eigen3.")

find_package(Eigen3 HINTS ${CMAKE_SOURCE_DIR}/thirdparty/eigen3/install/share/eigen3/cmake)

if(Eigen3_FOUND)
message(STATUS "Found: Eigen3 - ${EIGEN3_INCLUDE_DIRS}")

include_directories(${EIGEN3_INCLUDE_DIRS})
set(EIGEN3_LIBS Eigen3::Eigen)
endif()

message(STATUS "Finish Finding OpenCV.\n")