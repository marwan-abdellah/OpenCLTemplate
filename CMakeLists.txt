################################################################################
# Copyright (C) 2015  Marwan Abdellah <abdellah.marwan@gmail.com>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
################################################################################


CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(OpenclTemplate)

# Add the CMake directory
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Find the OpenCL package and installation directories
FIND_PACKAGE(OpenCL REQUIRED)
INCLUDE_DIRECTORIES(${OPENCL_INCLUDE_DIR})

# Adding the source files to the CMake source tree
SET(SRC_FILES
    clUtilities.cpp
    clContext.cpp
    ApplicationData.cpp
    Logger.cpp
    clHardware.cpp
    Image.cpp
    clKernels.cpp
    ImageUtilities.cpp
)

# Adding the header files to the CMake source tree
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
    ImageUtilities.h
)

# Application entry point
SET(ENTRY_FILE RunApplication.cpp)

# Create the executable
ADD_EXECUTABLE(example ${SRC_FILES} ${HDR_FILES} ${ENTRY_FILE})

# Linking against the OpenCL libraries
TARGET_LINK_LIBRARIES(example ${OPENCL_LIBRARY})
