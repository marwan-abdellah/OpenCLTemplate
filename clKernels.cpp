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

#include "clKernels.h"
#include "clUtilities.h"
#include "Logger.h"
#include <fstream>


/**
 * @brief clKernels::loadKernel
 * Loads a kernel from a file and returns it into a string.
 * @param kernelPath The path of the kernel.
 * @return
 * A string rpresenting the kernel.
 */
std::string clKernels::loadKernel(const char* kernelPath)
{
    BEGIN();
    LOG_INFO_ARGS("Loading the kernel [%s]", kernelPath);

    std::ifstream stream(kernelPath);
    std::string kernelString((std::istreambuf_iterator<char>(stream)),
                             std::istreambuf_iterator<char> ());

    END();
    return kernelString;
}


/**
 * @brief clKernels::createProgramFromKernelSource
 * @param kernelSource
 * @param context
 * @param deviceIds
 * @param deviceCount
 * @return
 */
cl_program clKernels::createProgramFromKernelSource
(const std::string& kernelSource, cl_context context,
 cl_device_id* deviceIds, int32_t deviceCount)
{
    BEGIN();

    // Get the size of the kernel string
    size_t lengths [1] = { kernelSource.size () };

    // Retrieve the text included in the kernel string line by line
    const char* sources [1] = { kernelSource.data () };

    // Create the OpenCL program from the source
    LOG_INFO("Creating the program from source");
    cl_int errorId = 0;
    cl_program program = clCreateProgramWithSource
            (context,
             1,
             sources,
             lengths,
             &errorId);
    clCheckError(errorId);

    LOG_INFO("Compiling the program");
    errorId = clBuildProgram (program,
                              deviceCount,
                              deviceIds,
                              "-D FILTER_SIZE=1",
                              NULL,
                              NULL);
    clCheckError(errorId);

    END();

    return program;
}


/**
 * @brief clKernels::createKernelFromProgram
 * @param program
 * @param function
 * @return
 */
cl_kernel clKernels::createKernelFromProgram(const cl_program &program,
                                             const std::string function)
{
    BEGIN();

    LOG_INFO_ARGS("Creating a kernel for the function %s", function.c_str());
    cl_int errorId = 0;
    cl_kernel kernel = clCreateKernel(program, function.c_str(), &errorId);
    clCheckError(errorId);

    END();

    return kernel;
}
