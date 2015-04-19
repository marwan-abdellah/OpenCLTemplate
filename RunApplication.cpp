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

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "clHeaders.h"
#include "clUtilities.h"
#include "ApplicationData.h"
#include "Externs.hpp"
#include "clKernels.h"
#include "Image.h"
#include "ImageUtilities.h"

ApplicationData* appData;

/**
 * @brief runApplication
 * Run the OpenCL application.
 * @param argc Argument count
 * @param argv Argument list
 * @return
 */
int runApplication (int argc, char** argv)
{
    // Reporting for any error in the application
    cl_int error = CL_SUCCESS;

    // Create the application data object that contains all the info. of the
    // application
    appData = new ApplicationData(argc, argv);
    LOG_INFO_ARGS("Running %s", argv[0]);

    // Scan the hardware to return a list with all the available devices on it
    ex_hardwareInfo = new clHardware();
    ex_hardwareInfo->scanHardware ();

    // Properties of the OpenCL context
    const cl_context_properties contextProperties [] =
    {
        CL_CONTEXT_PLATFORM,
        reinterpret_cast<cl_context_properties>
        (ex_hardwareInfo->getPlatformIds()[0]),
        0, 0
    };

    // Creating an OpenCL context
    cl_context context = clCreateContext(contextProperties,
                                         ex_hardwareInfo->getDeviceCount(),
                                         ex_hardwareInfo->getDeviceIds(),
                                         NULL,
                                         NULL,
                                         &error);
    clCheckError (error);

    // Creating a dummy blurring filter to be applied to the input image
    // and normalize it
    LOG_DEBUG("Creating the filter kernel");
    float filter [] = { 1, 2, 1, 2, 4, 2, 1, 2, 1 };
    for (int i = 0; i < 9; ++i) filter[i] /= 16.0f;

    // Load a kernel source from the file
    LOG_DEBUG("Loading and compiling the kernel");
    std::string kernelSource = clKernels::loadKernel("kernels/image.cl");

    cl_program program = clKernels::createProgramFromKernelSource
            (kernelSource, context, ex_hardwareInfo->getDeviceIds(),
             ex_hardwareInfo->getDeviceCount());

    cl_kernel kernel = clKernels::createKernelFromProgram(program, "Filter");

    // Loading and initializing the image data
    // The image must be converted to an RGBA format to be processed
    LOG_DEBUG("Loading an input image and converting it to RGBA");
    Image* loadedImage = new Image("test.ppm");
    Image* loadedImageRGBA = ImageUtilities::convertRGBtoRGBA(loadedImage);

    // Image format
    static const cl_image_format format = { CL_RGBA, CL_UNORM_INT8 };

    LOG_INFO("Device image --- input image");
    cl_mem inputImage = clCreateImage2D
            (context,
             CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
             &format,
             loadedImageRGBA->getWidth(),
             loadedImageRGBA->getHeight(),
             0,
             const_cast<char*>(loadedImageRGBA->getPixels()->data()),
             &error);
    clCheckError(error);

    LOG_INFO("Device image --- output image");
    cl_mem outputImage = clCreateImage2D
            (context,
             CL_MEM_WRITE_ONLY,
             &format,
             loadedImageRGBA->getWidth(),
             loadedImageRGBA->getHeight(),
             0,
             NULL,
             &error);
    clCheckError (error);

    // Create a buffer for the filter weights
    LOG_DEBUG("Creating a buffer with the filter values");
    cl_mem filterWeightsBuffer = clCreateBuffer
            (context,
             CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
             sizeof (float) * 9,
             filter,
             &error);
    clCheckError (error);

    // Setup the kernel arguments
    // < kernel, argument order, data size, argument >
    LOG_DEBUG("Binding the parameters of the kernel");
    clSetKernelArg(kernel, 0, sizeof (cl_mem), &inputImage);
    clSetKernelArg(kernel, 1, sizeof (cl_mem), &filterWeightsBuffer);
    clSetKernelArg(kernel, 2, sizeof (cl_mem), &outputImage);

    // Create the command queue
    LOG_DEBUG("Creating the command queue");
    cl_command_queue queue = clCreateCommandQueue
            (context,
             ex_hardwareInfo->getDeviceIds()[0],
            0,
            &error);
    clCheckError (error);

    // Run the processing
    LOG_DEBUG("Run the processing");
    std::size_t offset [3] = { 0 };
    std::size_t size [3] = { loadedImageRGBA->getWidth(),
                             loadedImageRGBA->getHeight(),
                             1 };
    LOG_DEBUG("Adding the kernel to the processing queue");
    error = clEnqueueNDRangeKernel(queue,   // Command queue
                                   kernel,  // Kernel
                                   2,       // Work load dimension(s)
                                   offset,  // Global work offset
                                   size,    // Global work size
                                   NULL,    // Local work size
                                   0,       // Number of events in waiting list
                                   NULL,    // Event waiting list
                                   NULL);   // Event
    clCheckError (error);

    // Prepare the result image, set to black
    // Creating the output image with empty data
    Image* resultingImageRGBA =
            new Image(loadedImageRGBA->getWidth(),
                      loadedImageRGBA->getHeight(),
                      loadedImageRGBA->getColorDepth(),
                      loadedImageRGBA->getNumberOfColorComponents(),
                      loadedImageRGBA->getName());
    std::vector<char>* resultData = resultingImageRGBA->getPixels();
    std::fill(resultData->begin(), resultData->end(), 0);

    // Get the result back to the host
    std::size_t origin [3] = { 0 };
    std::size_t region [3] = { resultingImageRGBA->getWidth(),
                               resultingImageRGBA->getHeight(),
                               1 };
    clEnqueueReadImage(queue,
                       outputImage,
                       CL_TRUE,
                       origin,
                       region,
                       0,
                       0,
                       resultingImageRGBA->getPixels()->data(),
                       0,
                       NULL,
                       NULL);

    // Converting the RGBA image into an RGB one to write it to disk.
    LOG_DEBUG("Writing the final image");
    Image* resultingImage = ImageUtilities::convertRGBAtoRGB(resultingImageRGBA);
    resultingImage->savePPMImage("Output.ppm");

    // Cleaning the buffers in stepby step way
    LOG_DEBUG("Cleaning the application data");
    clReleaseMemObject(outputImage);
    clReleaseMemObject(filterWeightsBuffer);
    clReleaseMemObject(inputImage);
    clReleaseCommandQueue(queue);
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseContext(context);
}

/**
 * @brief main
 * Application entry point.
 * @param argc Argument count
 * @param argv Argument list
 * @return
 */
int main(int argc, char** argv) { return runApplication(argc, argv); }
