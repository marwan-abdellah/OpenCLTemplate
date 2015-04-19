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
    static void checkError( const std::string FILE_NAME,
                            const int LINE,
                            const std::string FUNCTION,
                            cl_int errorId );

    ~clUtilities();
};



/** \brief Error checking function */
#define clCheckError( ERROR_ID )                                               \
    clUtilities::checkError( __FILE__, __LINE__, __FUNCTION__, ERROR_ID )

/** \brief Get the name of the platform for a given ID */
#define clGetPlatformName( P_ID ) clUtilities::getPlatformName( P_ID )

/** \brief Get the name of the device for a given ID */
#define clGetDeviceName( D_ID ) clUtilities::getDeviceName( D_ID )

#endif // CLUTILITIES_H
