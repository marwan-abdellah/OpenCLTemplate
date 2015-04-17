#include "Logger.h"
#include "ColorDefines.h"
#include "Externs.hpp"
#include <stdio.h>

#define TIME_STAMP_CHAR_LENGTH 128
#define PROFILE_LINE \
    "***************************************************************************\n"

/**
 * @brief Logger::Logger
 */
Logger::Logger()
{
    // Print to the std screen
    logFilePtr_ = stdout;
}

/**
 * @brief Logger::Log
 * @param logLevel
 * @param FILE
 * @param LINE
 * @param FUNCTION
 * @param fmt
 */
void Logger::Log( const LOG_LEVEL logLevel,
                  const std::string FILE,
                  const int LINE,
                  const std::string FUNCTION,
                  const char *fmt = "", ... )
{
    // Variable arguments information
    va_list argumentList;

    // Lof message
    char logMessage[1024];

    // Get the arguments and add them to the buffer
    va_start(argumentList, fmt);
    vsnprintf(logMessage, sizeof(logMessage), fmt, argumentList);

    // Get the time now
    time_t timeNow = time(NULL);

    // Time stamp string
    char timeStamp[TIME_STAMP_CHAR_LENGTH];

    // Format the time string and get the local time
    strftime(timeStamp, sizeof(timeStamp),
             (char *)"%D.%M.%Y, %H:%M:%S", localtime(&timeNow));

    switch (logLevel) {
    case LEVEL_INFO:
        // Print the string to the stream
        fprintf(this->logFilePtr_,
                STD_RED "[%d]" STD_RESET            // Process Id
                STD_YELLOW "[%s]" STD_RESET         // Time stamp
                STD_CYAN " %s :" STD_RESET          // File name
                STD_GREEN "[%d]\n" STD_RESET        // Code line
                STD_MAGENTA "\t* %s" STD_RESET      // Function name
                STD_BOLDRED " %s \n" STD_RESET,     // Message
                (int) getpid(),                     // Process Id
                timeStamp,                          // Time stamp
                FILE.c_str(),                       // File name
                LINE,                               // Code line
                FUNCTION.c_str(),                   // Function name
                logMessage);                        // Message
        break;

    case LEVEL_WARNING:
        // Print the string to the stream
        fprintf(this->logFilePtr_,
                STD_RED "[%d]" STD_RESET            // Process Id
                STD_YELLOW "[%s]" STD_RESET         // Time stamp
                STD_CYAN " %s :" STD_RESET          // File name
                STD_GREEN "[%d]\n" STD_RESET        // Code line
                STD_MAGENTA "\t* %s" STD_RESET      // Function name
                STD_BOLDRED " %s \n" STD_RESET,     // Message
                (int) getpid(),                     // Process Id
                timeStamp,                          // Time stamp
                FILE.c_str(),                       // File name
                LINE,                               // Code line
                FUNCTION.c_str(),                   // Function name
                logMessage);                        // Message
        break;

    case LEVEL_DEBUG:
        // Print the string to the stream
        fprintf(this->logFilePtr_,
                STD_RED "[%d]" STD_RESET            // Process Id
                STD_YELLOW "[%s]" STD_RESET         // Time stamp
                STD_CYAN " %s :" STD_RESET          // File name
                STD_GREEN "[%d]\n" STD_RESET        // Code line
                STD_MAGENTA "\t* %s" STD_RESET      // Function name
                STD_BOLDRED " %s \n" STD_RESET,     // Message
                (int) getpid(),                     // Process Id
                timeStamp,                          // Time stamp
                FILE.c_str(),                       // File name
                LINE,                               // Code line
                FUNCTION.c_str(),                   // Function name
                logMessage);                        // Message
        break;

    case LEVEL_DEBUG_OK:
        // Print the string to the stream
        fprintf(this->logFilePtr_,
                STD_RED "[%d]" STD_RESET            // Process Id
                STD_YELLOW "[%s]" STD_RESET         // Time stamp
                STD_CYAN " %s :" STD_RESET          // File name
                STD_GREEN "[%d]\n" STD_RESET        // Code line
                STD_MAGENTA "\t* %s" STD_RESET      // Function name
                STD_BOLDRED " [OK] %s \n" STD_RESET,// Message
                (int) getpid(),                     // Process Id
                timeStamp,                          // Time stamp
                FILE.c_str(),                       // File name
                LINE,                               // Code line
                FUNCTION.c_str(),                   // Function name
                logMessage);                        // Message
        break;

    case LEVEL_BEGIN:
        // Print the string to the stream
        fprintf(this->logFilePtr_,
                STD_RED "[%d]" STD_RESET                // Process Id
                STD_YELLOW "[%s]" STD_RESET             // Time stamp
                STD_CYAN " %s :" STD_RESET              // File name
                STD_GREEN "[%d]\n" STD_RESET            // Code line
                STD_MAGENTA "\t* %s" STD_RESET          // Function name
                STD_BOLDRED " [BEGIN] %s \n" STD_RESET, // Message
                (int) getpid(),                         // Process Id
                timeStamp,                              // Time stamp
                FILE.c_str(),                           // File name
                LINE,                                   // Code line
                FUNCTION.c_str(),                       // Function name
                logMessage);                            // Message
        break;

    case LEVEL_END:
        // Print the string to the stream
        fprintf(this->logFilePtr_,
                STD_RED "[%d]" STD_RESET                // Process Id
                STD_YELLOW "[%s]" STD_RESET             // Time stamp
                STD_CYAN " %s :" STD_RESET              // File name
                STD_GREEN "[%d]\n" STD_RESET            // Code line
                STD_MAGENTA "\t* %s" STD_RESET          // Function name
                STD_BOLDRED " [END] %s \n" STD_RESET,     // Message
                (int) getpid(),                         // Process Id
                timeStamp,                              // Time stamp
                FILE.c_str(),                           // File name
                LINE,                                   // Code line
                FUNCTION.c_str(),                       // Function name
                logMessage);                            // Message
        break;

    case LEVEL_DEBUG_GL:
        // Print the string to the stream
        fprintf(this->logFilePtr_,
                STD_RED "[%d]" STD_RESET            // Process Id
                STD_YELLOW "[%s]" STD_RESET         // Time stamp
                STD_CYAN " %s :" STD_RESET          // File name
                STD_GREEN "[%d]\n" STD_RESET        // Code line
                STD_MAGENTA "\t* %s" STD_RESET      // Function name
                STD_BOLDRED " %s \n" STD_RESET,     // Message
                (int) getpid(),                     // Process Id
                timeStamp,                          // Time stamp
                FILE.c_str(),                       // File name
                LINE,                               // Code line
                FUNCTION.c_str(),                   // Function name
                logMessage);                        // Message
        break;

    case LEVEL_PROFILE_CPU: {
        // Print the string to the stream
        fprintf(this->logFilePtr_, STD_BOLDYELLOW PROFILE_LINE STD_RESET);
        fprintf(this->logFilePtr_,
                STD_YELLOW "[CPU Profiler: %s] \n" STD_RESET    // Time stamp
                STD_BOLDYELLOW "%s \n" STD_RESET,               // Message
                timeStamp,                                      // Time stamp
                logMessage);                                    // Message
        fprintf(this->logFilePtr_, STD_BOLDYELLOW PROFILE_LINE STD_RESET);
    }   break;

    case LEVEL_PROFILE_GPU: {
        // Print the string to the stream
        fprintf(this->logFilePtr_, STD_BOLDYELLOW PROFILE_LINE STD_RESET);
        fprintf(this->logFilePtr_,
                STD_YELLOW "[GPU Profiler: %s] \n" STD_RESET    // Time stamp
                STD_BOLDYELLOW "%s \n" STD_RESET,               // Message
                timeStamp,                                      // Time stamp
                logMessage);                                    // Message
        fprintf(this->logFilePtr_, STD_BOLDYELLOW PROFILE_LINE STD_RESET);
    }   break;

    case LEVEL_ERROR:
        // Print the string to the stream
        fprintf(this->logFilePtr_,
                STD_BOLDRED "[%d]" STD_RESET        // Process Id
                STD_BOLDRED "[%s]" STD_RESET        // Time stamp
                STD_BOLDRED " %s :" STD_RESET       // File name
                STD_BOLDRED "[%d]\n" STD_RESET      // Code line
                STD_BOLDRED "\t* %s" STD_RESET      // Function name
                STD_BOLDRED " %s \n" STD_RESET,     // Message
                (int) getpid(),                     // Process Id
                timeStamp,                          // Time stamp
                FILE.c_str(),                       // File name
                LINE,                               // Code line
                FUNCTION.c_str(),                   // Function name
                logMessage);                        // Message

        // Exit the application.
        LOG_EXIT();
        break;

    default:
        break;
    }

    // Done
    va_end(argumentList);
}

/**
 * @brief Logger::~Logger
 */
Logger::~Logger()
{
    LOG_DEBUG("Destructing the logger");

    fclose(logFilePtr_);
}

/**
 * @brief GetApplicationLogger
 * @return
 */
Logger* GetApplicationLogger()
{
    return appData->Log();
}
