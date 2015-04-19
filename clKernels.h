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

#ifndef CLKERNELS_H
#define CLKERNELS_H

#include "clHeaders.h"
#include <string>

class clKernels
{
public:

    /**
     * @brief loadKernel
     * Loads a kernel from a file and returns it into a string.
     * @param kernelPath The path of the kernel.
     * @return
     * A string rpresenting the kernel.
     */
    static std::string loadKernel (const char* kernelPath);

    /**
     * @brief createProgramFromKernelSource
     * @param kernelSource
     * @param context
     * @param deviceIds
     * @param deviceCount
     * @return
     */
    static cl_program createProgramFromKernelSource
    (const std::string& kernelSource, cl_context context,
     cl_device_id *deviceIds, int32_t deviceCount);

    /**
     * @brief createKernelFromProgram
     * @param program
     * @param function
     * @return
     */
    static cl_kernel createKernelFromProgram(const cl_program &program,
                                             const std::string function);
};

#endif // CLKERNELS_H
