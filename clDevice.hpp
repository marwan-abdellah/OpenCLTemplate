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

#ifndef CLDEVICE_HPP
#define CLDEVICE_HPP

#include "clHardware.h"
#include <string>

class clDevice
{
public:
    /**
     * @brief clDevice
     * @param name
     * @param id
     */
    clDevice( const std::string name, const cl_device_id id ) :
        _name(name), _id(id) { }

    /**
     * @brief getName
     * Gets the name of the device.
     * @return
     * The name of the device.
     */
    std::string getName( void ) const { return _name; }

    /**
     * @brief getId
     * Gets the ID of the device.
     * @return
     * The ID of the device.
     */
    cl_device_id getId( void ) const { return _id; }

private:

    /** @brief The name of device */
    const std::string _name;

    /** @brief The ID of the device */
    const cl_device_id _id;
};

#endif // CLDEVICE_HPP

