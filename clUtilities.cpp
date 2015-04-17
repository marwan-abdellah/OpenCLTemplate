#include "clUtilities.h"
#include "Externs.hpp"
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
void clUtilities::checkError( cl_int errorId )
{
    LOG_DEBUG_VERBOSE( "checkError" );

    if (errorId != CL_SUCCESS) {
        std::cerr << "OpenCL call failed with an error " << errorId
                  << std::endl;
        std::exit (1);
    }

    LOG_DEBUG_VERBOSE_OK( "checkError" );
}


clUtilities::~clUtilities()
{
    LOG_DEBUG_VERBOSE( "~clUtilities" );

    LOG_DEBUG_VERBOSE_OK( "~clUtilities" );
}

