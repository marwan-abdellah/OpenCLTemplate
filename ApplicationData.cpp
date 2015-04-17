#include "ApplicationData.h"
#include "ApplicationData.hpp"
#include "Logger.h"


/**
 * @brief ApplicationData::ApplicationData
 * @param argc
 * @param argv
 */
ApplicationData::ApplicationData( const int argc, char *argv[] )
{
    // Create a new logger to trace the application
    ex_logger = new Logger();
}


/**
 * @brief ApplicationData::Log
 * @return
 */
Logger* ApplicationData::Log( void )
{
    return ex_logger;
}


/**
 * @brief ApplicationData::~ApplicationData
 */
ApplicationData::~ApplicationData()
{

}

