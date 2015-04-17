#include "clKernels.h"
#include "clUtilities.h"
#include "Logger.h"
#include <fstream>


/**
 * @brief clKernels::loadKernel
 * @param kernelPath
 * @return
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
