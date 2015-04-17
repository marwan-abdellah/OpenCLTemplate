#include "clHardware.h"
#include "Logger.h"

/**
 * @brief clHardware::clHardware
 */
clHardware::clHardware() { }


/**
 * @brief clHardware::scanHardware
 */
void clHardware::scanHardware()
{
    BEGIN();

    // Get the number of supported platforms in the system
    clGetPlatformIDs( 0, NULL, &_platformCount );

    if ( _platformCount == 0 )
        LOG_ERROR( "NO OpenCL hardware platform were found" );
    else
        LOG_INFO_ARGS( "FOUND [%d] platform(s)",
                       _platformCount );

    // Get the platform IDs
    _platformIds = new cl_platform_id[_platformCount];
    clGetPlatformIDs( _platformCount, _platformIds, NULL );

    for ( uint_fast32_t i = 0; i < _platformCount; ++i )
    {
        clPlatform platform(clGetPlatformName(_platformIds[i]), _platformIds[i]);
        _platformList.push_back (platform);
    }

    // Get the number of supported OpenCL-capable devices in the system
    clGetDeviceIDs (_platformIds[0], CL_DEVICE_TYPE_ALL, 0, NULL,
            &_deviceCount);

    if (_deviceCount == 0)
        LOG_ERROR( "NO OpenCL devices were found" );
    else
        LOG_INFO_ARGS( "FOUND [%d] OpenCL-capable devices(s)", _deviceCount );

    _deviceIds = new cl_device_id[_deviceCount];
    clGetDeviceIDs (_platformIds[0], CL_DEVICE_TYPE_ALL, _deviceCount,
            _deviceIds, NULL);

    for ( uint_fast32_t i = 0; i < _deviceCount; ++i )
    {
        clDevice device(clGetDeviceName(_deviceIds[i]), _deviceIds[i]);
        _deviceList.push_back (device);
    }

    END();
}


/**
 * @brief clHardware::getHardwareId
 * @return
 */
std::string clHardware::getHardwareId(void) const
{
    return _hardwareID;
}


/**
 * @brief clHardware::getPlatformCount
 * @return
 */
uint32_t clHardware::getPlatformCount(void) const
{
    return _platformCount;
}


/**
 * @brief clHardware::getDeviceCount
 * @return
 */
uint32_t clHardware::getDeviceCount(void) const
{
    return _deviceCount;
}


/**
 * @brief clHardware::getPlatformList
 * @return
 */
const std::vector<clPlatform>& clHardware::getPlatformList(void) const
{
    return _platformList;
}

/**
 * @brief clHardware::getDeviceList
 * @return
 */
const std::vector<clDevice>& clHardware::getDeviceList(void) const
{
    return _deviceList;
}


/**
 * @brief clHardware::getPlatformIds
 * @return
 */
cl_platform_id* clHardware::getPlatformIds(void) const
{
    return _platformIds;
}


/**
 * @brief clHardware::getDeviceIds
 * @return
 */
cl_device_id* clHardware::getDeviceIds(void) const
{
    return _deviceIds;
}


/**
 * @brief clHardware::~clHardware
 */
clHardware::~clHardware() { }

