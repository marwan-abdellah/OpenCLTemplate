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

#ifndef CLUTILITIES_H
#define CLUTILITIES_H

#include "clHeaders.h"
#include <string>

class clUtilities
{
public:
    clUtilities();

    /**
     * @brief getPlatformName
     * @param platformId
     * @return
     */
    static std::string getPlatformName( cl_platform_id platformId );

    /**
     * @brief getDeviceName
     * @param platformId
     * @return
     */
    static std::string getDeviceName( cl_device_id platformId );

    /**
     * @brief checkError
     * @param errorId
     */
    static void checkError( const std::string FILE_NAME,
                            const int LINE,
                            const std::string FUNCTION,
                            cl_int errorId );

    ~clUtilities();
};



/** \brief Error checking function */
#define clCheckError( ERROR_ID )                                               \
    clUtilities::checkError( __FILE__, __LINE__, __FUNCTION__, ERROR_ID )

/** \brief Get the name of the platform for a given ID */
#define clGetPlatformName( P_ID ) clUtilities::getPlatformName( P_ID )

/** \brief Get the name of the device for a given ID */
#define clGetDeviceName( D_ID ) clUtilities::getDeviceName( D_ID )

#endif // CLUTILITIES_H
