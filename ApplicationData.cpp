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

#include "ApplicationData.h"
#include "ApplicationData.hpp"
#include "Logger.h"


/**
 * @brief ApplicationData::ApplicationData
 * Constructor
 * @param argc
 * @param argv
 */
ApplicationData::ApplicationData( const int argc, char *argv[] )
{
    // Create a new logger to trace the application
    ex_logger = new Logger();
}


/**
 * @brief ApplicationData::Log
 * Logs events into the logging system of the application.
 * @return
 */
Logger* ApplicationData::Log( void )
{
    return ex_logger;
}


/**
 * @brief ApplicationData::~ApplicationData
 */
ApplicationData::~ApplicationData()
{

}

