#ifndef CLUTILITIES_H
#define CLUTILITIES_H

#include "clHeaders.h"
#include <string>

class clUtilities
{
public:
    clUtilities();

    /**
     * @brief getPlatformName
     * @param platformId
     * @return
     */
    static std::string getPlatformName( cl_platform_id platformId );

    /**
     * @brief getDeviceName
     * @param platformId
     * @return
     */
    static std::string getDeviceName( cl_device_id platformId );

    /**
     * @brief checkError
     * @param errorId
     */
    static void checkError( cl_int errorId );

    ~clUtilities();
};

#define clCheckError( ERROR_ID ) clUtilities::checkError( ERROR_ID )
#define clGetPlatformName( P_ID ) clUtilities::getPlatformName( P_ID )
#define clGetDeviceName( P_ID ) clUtilities::getDeviceName( P_ID )

#endif // CLUTILITIES_H
