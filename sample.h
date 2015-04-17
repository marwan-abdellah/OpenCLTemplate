#ifndef SAMPLE_H
#define SAMPLE_H


cl_uint uiNumDevices;
cl_device_id* cdDevices;
cl_uint uiDeviceUsed;
cl_uint uiDevCount;
cl_context cxGPUContext;
cl_device_id device;

void x()
{
    // Get the number of GPU devices available to the platform
    ciErrNum = clGetDeviceIDs(cpPlatform, CL_DEVICE_TYPE_GPU, 0, NULL, &uiDevCount);
    // oclCheckErrorEX(ciErrNum, CL_SUCCESS, pCleanup);

    // Create the device list
    cdDevices = new cl_device_id [uiDevCount];
    ciErrNum = clGetDeviceIDs(cpPlatform, CL_DEVICE_TYPE_GPU, uiDevCount, cdDevices, NULL);
    clCheckError(ciErrNum,"Device");

    // Get device requested on command line, if any
    uiDeviceUsed = 0;
    unsigned int uiEndDev = uiDevCount - 1;
    // if(shrGetCmdLineArgumentu(argc, argv, "device", &uiDeviceUsed ))
    {
        // uiDeviceUsed = CLAMP(uiDeviceUsed, 0, uiEndDev);
        uiEndDev = uiDeviceUsed;
    }

    // Check if the requested device (or any of the devices if none requested) supports context sharing with OpenGL
    if(g_glInterop && !bQATest)
    {
        bool bSharingSupported = false;
        for(unsigned int i = uiDeviceUsed; (!bSharingSupported && (i <= uiEndDev)); ++i)
        {
            size_t extensionSize;
            ciErrNum = clGetDeviceInfo(cdDevices[i], CL_DEVICE_EXTENSIONS, 0, NULL, &extensionSize );
            // oclCheckErrorEX(ciErrNum, CL_SUCCESS, pCleanup);
            if(extensionSize > 0)
            {
                char* extensions = (char*)malloc(extensionSize);
                ciErrNum = clGetDeviceInfo(cdDevices[i], CL_DEVICE_EXTENSIONS, extensionSize, extensions, &extensionSize);
                // oclCheckErrorEX(ciErrNum, CL_SUCCESS, pCleanup);
                std::string stdDevString(extensions);
                free(extensions);

                size_t szOldPos = 0;
                size_t szSpacePos = stdDevString.find(' ', szOldPos); // extensions string is space delimited
                while (szSpacePos != stdDevString.npos)
                {
                    if( strcmp(GL_SHARING_EXTENSION, stdDevString.substr(szOldPos, szSpacePos - szOldPos).c_str()) == 0 )
                    {
                        // Device supports context sharing with OpenGL
                        uiDeviceUsed = i;
                        bSharingSupported = true;
                        break;
                    }
                    do
                    {
                        szOldPos = szSpacePos + 1;
                        szSpacePos = stdDevString.find(' ', szOldPos);
                    }
                    while (szSpacePos == szOldPos);
                }
            }
        }

        // Log CL-GL interop support and quit if not available (sample needs it)
        // shrLog("%s...\n", bSharingSupported ? "Using CL-GL Interop" : "No device found that supports CL/GL context sharing");
        // oclCheckErrorEX(bSharingSupported, true, pCleanup);

        // Define OS-specific context properties and create the OpenCL context
#if defined (__APPLE__)
        CGLContextObj kCGLContext = CGLGetCurrentContext();
        CGLShareGroupObj kCGLShareGroup = CGLGetShareGroup(kCGLContext);
        cl_context_properties props[] =
        {
            CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE, (cl_context_properties)kCGLShareGroup,
            0
        };
        cxGPUContext = clCreateContext(props, 0,0, NULL, NULL, &ciErrNum);
#else
#ifdef UNIX
        cl_context_properties props[] =
        {
            CL_GL_CONTEXT_KHR, (cl_context_properties)glXGetCurrentContext(),
            CL_GLX_DISPLAY_KHR, (cl_context_properties)glXGetCurrentDisplay(),
            CL_CONTEXT_PLATFORM, (cl_context_properties)cpPlatform,
            0
        };
        cxGPUContext = clCreateContext(props, 1, &cdDevices[uiDeviceUsed], NULL, NULL, &ciErrNum);
#else // Win32
        cl_context_properties props[] =
        {
            CL_GL_CONTEXT_KHR, (cl_context_properties)wglGetCurrentContext(),
            CL_WGL_HDC_KHR, (cl_context_properties)wglGetCurrentDC(),
            CL_CONTEXT_PLATFORM, (cl_context_properties)cpPlatform,
            0
        };
        cxGPUContext = clCreateContext(props, 1, &cdDevices[uiDeviceUsed], NULL, NULL, &ciErrNum);
#endif
#endif
    }
    else
    {
        // No GL interop
        cl_context_properties props[] = {CL_CONTEXT_PLATFORM, (cl_context_properties)cpPlatform, 0};
        cxGPUContext = clCreateContext(props, 1, &cdDevices[uiDeviceUsed], NULL, NULL, &ciErrNum);

        g_glInterop = false;
    }
    // oclCheckErrorEX(ciErrNum, CL_SUCCESS, pCleanup);
}


#endif // SAMPLE_H

