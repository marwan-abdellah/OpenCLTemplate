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

ApplicationData* appData;

struct MyImage
{
    std::vector<char> pixel;
    int width, height;
};

MyImage LoadImage (const char* path)
{
    std::ifstream in (path, std::ios::binary);

    std::string s;
    in >> s;

    if (s != "P6") {
        exit (1);
    }

    // Skip comments
    for (;;) {
        getline (in, s);

        if (s.empty ()) {
            continue;
        }

        if (s [0] != '#') {
            break;
        }
    }

    std::stringstream str (s);
    int width, height, maxColor;
    str >> width >> height;
    in >> maxColor;

    if (maxColor != 255) {
        exit (1);
    }

    {
        // Skip until end of line
        std::string tmp;
        getline(in, tmp);
    }

    std::vector<char> data (width * height * 3);
    in.read (reinterpret_cast<char*> (data.data ()), data.size ());

    const MyImage img = { data, width, height };
    return img;
}

void SaveImage (const MyImage& img, const char* path)
{
    std::ofstream out (path, std::ios::binary);

    out << "P6\n";
    out << img.width << " " << img.height << "\n";
    out << "255\n";
    out.write (img.pixel.data (), img.pixel.size ());
}

MyImage RGBtoRGBA (const MyImage& input)
{
    MyImage result;
    result.width = input.width;
    result.height = input.height;

    for (std::size_t i = 0; i < input.pixel.size (); i += 3) {
        result.pixel.push_back (input.pixel [i + 0]);
        result.pixel.push_back (input.pixel [i + 1]);
        result.pixel.push_back (input.pixel [i + 2]);
        result.pixel.push_back (0);
    }

    return result;
}

MyImage RGBAtoRGB (const MyImage& input)
{
    MyImage result;
    result.width = input.width;
    result.height = input.height;

    for (std::size_t i = 0; i < input.pixel.size (); i += 4) {
        result.pixel.push_back (input.pixel [i + 0]);
        result.pixel.push_back (input.pixel [i + 1]);
        result.pixel.push_back (input.pixel [i + 2]);
    }

    return result;
}


int main (int argc, char** argv)
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
    cl_context context = clCreateContext (contextProperties, ex_hardwareInfo->getDeviceCount (),
                                          ex_hardwareInfo->getDeviceIds(), NULL, NULL, &error);
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


    // OpenCL only supports RGBA, so we need to convert here
    const auto image = RGBtoRGBA (LoadImage ("test.ppm"));



    // Image format
    static const cl_image_format format = { CL_RGBA, CL_UNORM_INT8 };

    // Create a 2D image on the device
    cl_mem inputImage = clCreateImage2D
            (context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, &format,
             image.width, image.height, 0, // This is a bug in the spec
             const_cast<char*> (image.pixel.data ()), &error);
    clCheckError (error);

    cl_mem outputImage = clCreateImage2D
            (context, CL_MEM_WRITE_ONLY, &format, image.width, image.height, 0,
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
    std::size_t size [3] = { image.width, image.height, 1 };
    error = clEnqueueNDRangeKernel(queue, kernel, 2, offset, size, NULL,
                                   0, NULL, NULL);
    clCheckError (errno);

    // Prepare the result image, set to black
    MyImage result = image;
    std::fill(result.pixel.begin (), result.pixel.end (), 0);

    // Get the result back to the host
    std::size_t origin [3] = { 0 };
    std::size_t region [3] = { result.width, result.height, 1 };
    clEnqueueReadImage (queue, outputImage, CL_TRUE,
                        origin, region, 0, 0,
                        result.pixel.data (), 0, NULL, NULL);

    SaveImage (RGBAtoRGB (result), "output.ppm");

    clReleaseMemObject (outputImage);
    clReleaseMemObject (filterWeightsBuffer);
    clReleaseMemObject (inputImage);
    clReleaseCommandQueue (queue);
    clReleaseKernel (kernel);
    clReleaseProgram (program);

    clReleaseContext (context);
}
