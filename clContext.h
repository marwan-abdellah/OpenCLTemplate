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

#ifndef CLCONTEXT_H
#define CLCONTEXT_H

#include "clHeaders.h"

class clContext
{
public:

    /**
     * @brief getContextId
     * Gets the ID of the context.
     * @return
     * The ID of the context
     */
    cl_context getContextId(void) const;

    /**
     * @brief getContextProperties
     * Gets the properties of the context.
     * @return
     * A list of properties of the device
     */
    cl_context_properties getContextProperties(void) const;

private:
    /** @brief The ID of the OpenCL context */
    cl_context _contextId;

    /** @brief The properties of the OpenCL context */
    cl_context_properties _contextProp;


};

#endif // CLCONTEXT_H
