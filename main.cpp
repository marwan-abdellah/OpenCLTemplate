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

    // Create the application data object that contains all the info. of the
    // application
    appData = new ApplicationData(argc, argv);

    LOG_INFO_ARGS("Running %s", argv[0]);

    // Scan the hardware to return a list with all the available devices on it
    ex_hardwareInfo = new clHardware();
    ex_hardwareInfo->scanHardware ();


    const cl_context_properties contextProperties [] =
    {
        CL_CONTEXT_PLATFORM,
        reinterpret_cast<cl_context_properties>
        (ex_hardwareInfo->getPlatformIds()[0]),
        0, 0
    };

    cl_int error = CL_SUCCESS;
    cl_context context = clCreateContext(contextProperties,
                                         ex_hardwareInfo->getDeviceCount (),
                                         ex_hardwareInfo->getDeviceIds(),
                                         NULL, NULL, &error);
    clCheckError (error);

    // Simple Gaussian blur filter
    float filter [] = {
        1, 2, 1,
        2, 4, 2,
        1, 2, 1
    };

    // Normalize the filter
    for (int i = 0; i < 9; ++i) {
        filter [i] /= 16.0f;
    }

    // Load a kernel source from the file
    std::string kernelSource = clKernels::loadKernel("kernels/image.cl");

    // Create a program from source and compile it
    cl_program program = clKernels::createProgramFromKernelSource
            (kernelSource, context, ex_hardwareInfo->getDeviceIds(),
             ex_hardwareInfo->getDeviceCount());

    // Compiling the kernel for a specific function from the loaded program
    cl_kernel kernel = clKernels::createKernelFromProgram(program, "Filter");

    Image* inImage = new Image("test.ppm");
    Image* image = ImageUtilities::convertRGBtoRGBA(inImage);

    LOG_INFO("Setting the image format");

    // Image format
    static const cl_image_format format = { CL_RGBA, CL_UNORM_INT8 };

    LOG_INFO("Allocating the input image on the device");
    cl_mem inputImage = clCreateImage2D
            (context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, &format,
             image->getWidth(),
              image->getHeight(),
             0, // This is a bug in the spec
             const_cast<char*>(image->getPixels()->data()),
             &error);
    clCheckError(error);

    LOG_INFO("Allocating the output image on the device");
    cl_mem outputImage = clCreateImage2D
            (context, CL_MEM_WRITE_ONLY, &format,
             image->getWidth(), image->getHeight(), 0,
             NULL, &error);
    clCheckError (error);

    // Create a buffer for the filter weights
    cl_mem filterWeightsBuffer = clCreateBuffer
            (context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
             sizeof (float) * 9, filter, &error);
    clCheckError (error);

    // Setup the kernel arguments
    clSetKernelArg(kernel, 0, sizeof (cl_mem), &inputImage);
    clSetKernelArg(kernel, 1, sizeof (cl_mem), &filterWeightsBuffer);
    clSetKernelArg(kernel, 2, sizeof (cl_mem), &outputImage);

    // Create the command queue
    cl_command_queue queue = clCreateCommandQueue
            (context, ex_hardwareInfo->getDeviceIds()[0], 0, &error);
    clCheckError (error);

    // Run the processing
    std::size_t offset [3] = { 0 };
    std::size_t size [3] = { image->getWidth(), image->getHeight(), 1 };
    printf("%d %d \n", image->getWidth(), image->getHeight());
    error = clEnqueueNDRangeKernel(queue, kernel, 2, offset, size, NULL,
                                   0, NULL, NULL);
    clCheckError (error);

    // Prepare the result image, set to black
    Image* result = new Image(image->getWidth(),
                              image->getHeight(),
                              image->getColorDepth(),
                              image->getNumberOfColorComponents(),
                              image->getName());
    std::vector<char>* resultData = result->getPixels();
    std::fill(resultData->begin(), resultData->end(), 0);

    // Get the result back to the host
    std::size_t origin [3] = { 0 };
    std::size_t region [3] = { result->getWidth(), result->getHeight(), 1 };
    clEnqueueReadImage (queue, outputImage, CL_TRUE,
                        origin, region, 0, 0,
                        result->getPixels()->data(), 0, NULL, NULL);

    Image* converted = ImageUtilities::convertRGBAtoRGB(result);
    converted->savePPMImage("Output.ppm");
    inImage->savePPMImage("InputImage.ppm");

    ImageUtilities::convertRGBAtoRGB(ImageUtilities::convertRGBtoRGBA(inImage))->savePPMImage("Check.ppm");

    clReleaseMemObject (outputImage);
    clReleaseMemObject (filterWeightsBuffer);
    clReleaseMemObject (inputImage);
    clReleaseCommandQueue (queue);
    clReleaseKernel (kernel);
    clReleaseProgram (program);

    clReleaseContext (context);
}

/**
 * @brief main
 * Application entry point.
 * @param argc Argument count
 * @param argv Argument list
 * @return
 */
int main(int argc, char** argv) { return runApplication(argc, argv); }
