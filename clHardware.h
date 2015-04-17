#ifndef CLHARDWARE_H
#define CLHARDWARE_H

#include "clUtilities.h"
#include "clPlatform.hpp"
#include "clDevice.hpp"
#include <vector>
#include <string>

class clHardware
{
public:
    clHardware();
    ~clHardware();

    /**
     * @brief _scanHardware
     * Scans the undelying architecture and configuration of the systemxw
     */
    void scanHardware( void );

    /**
     * @brief getHardwareId
     * @return
     */
    std::string getHardwareId(void) const;

    /**
     * @brief getPlatformCount
     * @return
     */
    uint32_t getPlatformCount(void) const;

    /**
     * @brief getDeviceCount
     * @return
     */
    uint32_t getDeviceCount(void) const;

    /**
     * @brief getPlatformList
     * @return
     */
    const std::vector<clPlatform>& getPlatformList(void) const;

    /**
     * @brief getPlatformIds
     * @return
     */
    cl_platform_id* getPlatformIds(void) const;

    /**
     * @brief getDeviceList
     * @return
     */
    const std::vector<clDevice>& getDeviceList(void) const;

    /**
     * @brief getDeviceIds
     * @return
     */
    cl_device_id* getDeviceIds(void) const;

private:
    /** @brief An ID for the hardware device that triggers the scanning
     * operation */
    std::string _hardwareID;

    /** @brief Number of platforms available in the eco-system*/
    uint32_t _platformCount;

    /** @brief Number of devices on the scanned system */
    uint32_t _deviceCount;

    /** @brief A list containing all the IDs of the detected platforms */
    std::vector<clPlatform> _platformList;

    /** @brief A list of IDs for the supported platforms in the system */
    cl_platform_id* _platformIds;

    /** @brief A list containing all the IDs of the detected CL-based devices */
    std::vector<clDevice> _deviceList;

     /** @brief A list of IDs for the device supported by the system */
    cl_device_id* _deviceIds;
};

#endif // CLHARDWARE_H
