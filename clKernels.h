#ifndef CLKERNELS_H
#define CLKERNELS_H

#include "clHeaders.h"
#include <string>

class clKernels
{
public:

    /**
     * @brief loadKernel
     * @param kernelPath
     * @return
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
