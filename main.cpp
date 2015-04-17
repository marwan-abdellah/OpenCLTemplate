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

struct Image
{
    std::vector<char> pixel;
    int width, height;
};

Image LoadImage (const char* path)
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

    const Image img = { data, width, height };
    return img;
}

void SaveImage (const Image& img, const char* path)
{
    std::ofstream out (path, std::ios::binary);

    out << "P6\n";
    out << img.width << " " << img.height << "\n";
    out << "255\n";
    out.write (img.pixel.data (), img.pixel.size ());
}

Image RGBtoRGBA (const Image& input)
{
    Image result;
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

Image RGBAtoRGB (const Image& input)
{
    Image result;
    result.width = input.width;
    result.height = input.height;

    for (std::size_t i = 0; i < input.pixel.size (); i += 4) {
        result.pixel.push_back (input.pixel [i + 0]);
        result.pixel.push_back (input.pixel [i + 1]);
        result.pixel.push_back (input.pixel [i + 2]);
    }

    return result;
}

cl_program CreateProgram (const std::string& source,
                          cl_context context)
{
    // http://www.khronos.org/registry/cl/sdk/1.1/docs/man/xhtml/clCreateProgramWithSource.html
    size_t lengths [1] = { source.size () };
    const char* sources [1] = { source.data () };

    cl_int error = 0;
    cl_program program = clCreateProgramWithSource (context, 1, sources, lengths, &error);
    clCheckError( error );

    return program;
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

    // Create a program from source
    std::cout << "Creating a program from source" << std::endl;
    cl_program program = CreateProgram (clKernels::loadKernel("kernels/image.cl"),
                                        context);

    clCheckError (clBuildProgram (program, ex_hardwareInfo->getDeviceCount (), ex_hardwareInfo->getDeviceIds (),
                                  "-D FILTER_SIZE=1", nullptr, nullptr));

    // http://www.khronos.org/registry/cl/sdk/1.1/docs/man/xhtml/clCreateKernel.html
    cl_kernel kernel = clCreateKernel (program, "Filter", &error);
    clCheckError (error);

    // OpenCL only supports RGBA, so we need to convert here
    const auto image = RGBtoRGBA (LoadImage ("test.ppm"));

    // http://www.khronos.org/registry/cl/sdk/1.1/docs/man/xhtml/clCreateImage2D.html
    static const cl_image_format format = { CL_RGBA, CL_UNORM_INT8 };
    cl_mem inputImage = clCreateImage2D (context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, &format,
                                         image.width, image.height, 0,
                                         // This is a bug in the spec
                                         const_cast<char*> (image.pixel.data ()),
                                         &error);
    clCheckError (error);

    cl_mem outputImage = clCreateImage2D (context, CL_MEM_WRITE_ONLY, &format,
                                          image.width, image.height, 0,
                                          nullptr, &error);
    clCheckError (error);

    // Create a buffer for the filter weights
    // http://www.khronos.org/registry/cl/sdk/1.1/docs/man/xhtml/clCreateBuffer.html
    cl_mem filterWeightsBuffer = clCreateBuffer (context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                                 sizeof (float) * 9, filter, &error);
    clCheckError (error);

    // Setup the kernel arguments
    clSetKernelArg (kernel, 0, sizeof (cl_mem), &inputImage);
    clSetKernelArg (kernel, 1, sizeof (cl_mem), &filterWeightsBuffer);
    clSetKernelArg (kernel, 2, sizeof (cl_mem), &outputImage);

    // http://www.khronos.org/registry/cl/sdk/1.1/docs/man/xhtml/clCreateCommandQueue.html
    cl_command_queue queue = clCreateCommandQueue (context, ex_hardwareInfo->getDeviceIds ()[0],
            0, &error);
    clCheckError (error);

    // Run the processing
    // http://www.khronos.org/registry/cl/sdk/1.1/docs/man/xhtml/clEnqueueNDRangeKernel.html
    std::size_t offset [3] = { 0 };
    std::size_t size [3] = { image.width, image.height, 1 };
    clCheckError (clEnqueueNDRangeKernel (queue, kernel, 2, offset, size, nullptr,
                                          0, nullptr, nullptr));

    // Prepare the result image, set to black
    Image result = image;
    std::fill (result.pixel.begin (), result.pixel.end (), 0);

    // Get the result back to the host
    std::size_t origin [3] = { 0 };
    std::size_t region [3] = { result.width, result.height, 1 };
    clEnqueueReadImage (queue, outputImage, CL_TRUE,
                        origin, region, 0, 0,
                        result.pixel.data (), 0, nullptr, nullptr);

    SaveImage (RGBAtoRGB (result), "output.ppm");

    clReleaseMemObject (outputImage);
    clReleaseMemObject (filterWeightsBuffer);
    clReleaseMemObject (inputImage);

    clReleaseCommandQueue (queue);

    clReleaseKernel (kernel);
    clReleaseProgram (program);

    clReleaseContext (context);
}
