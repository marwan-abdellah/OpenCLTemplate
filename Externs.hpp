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

#ifndef EXTERNS_HPP
#define EXTERNS_HPP

#include "ApplicationData.h"
#include "Logger.h"
#include "clHardware.h"

/** @brief Application data structure shared among all the project files */
extern ApplicationData* appData;

/** \brief  Application logging system */
extern Logger* ex_logger;

/** \brief Application logging system */
extern clHardware* ex_hardwareInfo;

#endif // EXTERNS_HPP

