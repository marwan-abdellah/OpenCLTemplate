CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(OpenclTemplate)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

FIND_PACKAGE(OpenCL REQUIRED)
INCLUDE_DIRECTORIES(${OPENCL_INCLUDE_DIR})

SET(SRC_FILES
    clUtilities.cpp
    clContext.cpp
    ApplicationData.cpp
    Logger.cpp
    clHardware.cpp
    Image.cpp
    clKernels.cpp
)

SET(HDR_FILES
    clUtilities.h
    clHeaders.h
    clContext.h
    ApplicationData.h
    ApplicationData.hpp
    Externs.hpp
    Logger.h
    clHardware.h
    clPlatform.hpp
    clDevice.hpp
    Image.h
    clKernels.h
)

SET(ENTRY_FILE main.cpp)

ADD_EXECUTABLE(example ${SRC_FILES} ${HDR_FILES} ${ENTRY_FILE})
TARGET_LINK_LIBRARIES(example ${OPENCL_LIBRARY})
