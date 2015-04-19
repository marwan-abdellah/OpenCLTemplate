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

    /**
     * @brief _scanHardware
     * Scans the undelying architecture and configuration of the system.
     */
    void scanHardware( void );

    /**
     * @brief getHardwareId
     * Gets the ID of the hardware.
     * @return
     * The ID of the hardware.
     */
    std::string getHardwareId(void) const;

    /**
     * @brief getPlatformCount
     * Gets the count of platforms in the system.
     * @return
     * The count of platforms in the system.
     */
    uint32_t getPlatformCount(void) const;

    /**
     * @brief getDeviceCount
     * Gets the number of the devices in the system.
     * @return
     * The number of the devices in the system.
     */
    uint32_t getDeviceCount(void) const;

    /**
     * @brief getPlatformList
     * Gets a list of all the platforms in the system.
     * @return
     * A list of all the platforms in the system.
     */
    const std::vector<clPlatform>& getPlatformList(void) const;

    /**
     * @brief getPlatformIds
     * Gets a list of the IDs of the platforms in the system.
     * @return
     * A list of the IDs of the platforms in the system.
     */
    cl_platform_id* getPlatformIds(void) const;

    /**
     * @brief getDeviceList
     * Gets a list of the IDs of the devices in the system.
     * @return
     * A list of the IDs of the devices in the system.
     */
    const std::vector<clDevice>& getDeviceList(void) const;

    /**
     * @brief getDeviceIds
     * Gets a list of the IDs of the devices in the system.
     * @return
     * A list of the IDs of the devices in the system.
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
