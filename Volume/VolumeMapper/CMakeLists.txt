CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(VolumeMapper)
FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})
ADD_EXECUTABLE(VolumeMapper VolumeMapper.cpp)
TARGET_LINK_LIBRARIES(VolumeMapper ${VTK_LIBRARIES})
