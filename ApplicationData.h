#ifndef APPLICATIONDATA_H
#define APPLICATIONDATA_H

#include "Logger.h"

class ApplicationData
{
public:

    /**
     * @brief ApplicationData
     * @param argc
     * @param argv
     */
    ApplicationData(const int argc, char *argv[]);

    /**
     * @brief Log
     * @return
     */
    Logger* Log(void);

    ~ApplicationData();
};

#endif // APPLICATIONDATA_H
