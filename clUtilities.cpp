/*
 * Copyright (C) 2015 Marwan Abdellah <abdellah.marwan@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 */

#include "clUtilities.h"
#include "Externs.hpp"
#include "ColorDefines.h"
#include <iostream>


/**
 * @brief clUtilities::clUtilities
 */
clUtilities::clUtilities()
{
    LOG_DEBUG_VERBOSE( "clUtilities" );

    LOG_DEBUG_VERBOSE_OK( "clUtilities" );
}


/**
 * @brief clUtilities::getPlatformName
 * Query the platform and return its name.
 * @param platformId ID of the hardware platform.
 * @return The name of the requested platform for a given ID.
 *
 */

std::string clUtilities::getPlatformName( cl_platform_id platformId )
{
    LOG_DEBUG_VERBOSE( "getPlatformName" );

    // Get the size of the platform name string
    size_t size = 0;
    clGetPlatformInfo( platformId, CL_PLATFORM_NAME, 0, NULL, &size );

    // Get the actual platform name
    std::string platformName;
    platformName.resize( size );
    clGetPlatformInfo( platformId, CL_PLATFORM_NAME, size,
                       const_cast<char*> ( platformName.data() ), NULL );

    LOG_DEBUG_VERBOSE_OK( "getPlatformName" );

    return platformName;
}


/**
 * @brief clUtilities::getDeviceName
 * @param platformId
 * @return
 */
std::string clUtilities::getDeviceName( cl_device_id platformId )
{
    LOG_DEBUG_VERBOSE( "getDeviceName" );

    // Get the size of the device name string
    size_t size = 0;
    clGetDeviceInfo (platformId, CL_DEVICE_NAME, 0, NULL, &size);

    // Get the actual device name
    std::string deviceName;
    deviceName.resize( size );
    clGetDeviceInfo( platformId, CL_DEVICE_NAME, size,
                     const_cast<char*> ( deviceName.data() ), NULL );

    LOG_DEBUG_VERBOSE_OK( "getDeviceName" );

    return deviceName;
}


/**
 * @brief clUtilities::checkError
 * @param errorId
 */
void clUtilities::checkError( const std::string FILE_NAME,
                              const int LINE,
                              const std::string FUNCTION,
                              cl_int errorId )
{
    LOG_DEBUG_VERBOSE( "checkError" );

    if (errorId != CL_SUCCESS)
    {
        printf( STD_RED "[%d]" STD_RESET                        // Process Id
                STD_CYAN " %s :" STD_RESET                      // File name
                STD_GREEN "[%d]\n" STD_RESET                    // Code line
                STD_MAGENTA "\t* %s" STD_RESET                  // Function name
                STD_BOLDRED " OpenCL Error [%d] \n" STD_RESET,  // Message
                (int) getpid(),                                 // Process Id
                FILE_NAME.c_str(),                              // File name
                LINE,                                           // Code line
                FUNCTION.c_str(),                               // Error Id
                errorId );

        LOG_ERROR("OpenCL Error");
    }

    LOG_DEBUG_VERBOSE_OK( "checkError" );
}



clUtilities::~clUtilities()
{
    LOG_DEBUG_VERBOSE( "~clUtilities" );

    LOG_DEBUG_VERBOSE_OK( "~clUtilities" );
}

