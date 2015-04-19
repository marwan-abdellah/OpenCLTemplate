#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#include <string>
#include <unistd.h>
#include <iostream>

enum LOG_LEVEL
{
    LEVEL_INFO,
    LEVEL_INFO_OK,
    LEVEL_WARNING,
    LEVEL_BEGIN,
    LEVEL_END,
    LEVEL_DEBUG,
    LEVEL_DEBUG_OK,
    LEVEL_DEBUG_GL,
    LEVEL_DEBUG_GL_OK,
    LEVEL_ERROR,
    LEVEL_PROFILE_CPU,
    LEVEL_PROFILE_GPU
};

enum GPU_PROFILE_OPTION
{
    DISPLAY_PROFILE,
    LOG_PROFILE
};


/**
 * @brief The Logger class
 */
class Logger
{
public:

    /**
     * @brief Logger
     */
    Logger();
    ~Logger();

    /**
     * @brief Log
     * @param FILE
     * @param LINE
     * @param FUNCTION
     * @param fmt
     */
    void Log(const LOG_LEVEL, const std::string FILE, const int LINE,
             const std::string FUNCTION, const char *fmt, ...);

private:

    /** \brief File stream or std stream */
    FILE* logFilePtr_;
};

/**
 * @brief GetApplicationLogger
 * @return
 */
Logger* GetApplicationLogger(void);

/** \brief Log run time application information with out extra arguments */
#define LOG_INFO( FMT_MESSAGE )                                                 \
    GetApplicationLogger()->Log                                                 \
    (LEVEL_INFO, __FILE__, __LINE__, __FUNCTION__, FMT_MESSAGE)


/** \brief Log run time application information */
#define LOG_INFO_ARGS( FMT_MESSAGE, ... )                                       \
    GetApplicationLogger()->Log                                                 \
    (LEVEL_INFO, __FILE__, __LINE__, __FUNCTION__, FMT_MESSAGE, __VA_ARGS__)


/** \brief Log debugging information with out extra arguments */
#define LOG_DEBUG( FMT_MESSAGE, ... )                                           \
    GetApplicationLogger()->Log                                                 \
    (LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, FMT_MESSAGE)


/** \brief Log debugging information */
#define LOG_DEBUG_ARGS( FMT_MESSAGE, ... )                                      \
    GetApplicationLogger()->Log                                                 \
    (LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, FMT_MESSAGE, __VA_ARGS__)


/** \brief Log [OK] debugging information with out extra arguments */
#define LOG_DEBUG_OK( FMT_MESSAGE, ... )                                       \
    GetApplicationLogger()->Log                                                \
    (LEVEL_DEBUG_OK, __FILE__, __LINE__, __FUNCTION__, FMT_MESSAGE)


#ifdef DEBUG_VERBOSE
/** \brief Log debugging information with out extra arguments */
#define LOG_DEBUG_VERBOSE( FMT_MESSAGE, ... )                                           \
    GetApplicationLogger()->Log                                                 \
    (LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, FMT_MESSAGE)
#else
#define LOG_DEBUG_VERBOSE( FMT_MESSAGE, ... ) ( NULL )
#endif


#ifdef DEBUG_VERBOSE
/** \brief Log [OK] debugging information with out extra arguments */
#define LOG_DEBUG_OK( FMT_MESSAGE, ... )                                           \
    GetApplicationLogger()->Log                                                 \
    (LEVEL_DEBUG_VERBOSE_OK, __FILE__, __LINE__, __FUNCTION__, FMT_MESSAGE)
#else
#define LOG_DEBUG_VERBOSE_OK( FMT_MESSAGE, ... ) ( NULL )
#endif


#ifdef DEBUG_OPENGL_LOOP
/** \brief Log debugging information for OpenGL loop with out extra arguments */
#define LOG_DEBUG_RENDERING_LOOP( FMT_MESSAGE )                                 \
    GetApplicationLogger()->Log                                                 \
    (LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, FMT_MESSAGE)
#else
#define LOG_DEBUG_RENDERING_LOOP( FMT_MESSAGE ) (NULL)
#endif


#ifdef DEBUG_OPENGL_LOOP
/** \brief Log debugging information for OpenGL */
#define LOG_DEBUG_RENDERING_LOOP_ARGS( FMT_MESSAGE, ... )                       \
    GetApplicationLogger()->Log                                                 \
    (LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, FMT_MESSAGE, __VA_ARGS__)
#else
#define LOG_DEBUG_RENDERING_LOOP_ARGS( FMT_MESSAGE, ... ) (NULL)
#endif


/** \brief Log warning messages with out extra arguments */
#define LOG_WARN( FMT_MESSAGE )                                                 \
    GetApplicationLogger()->Log                                                 \
    (LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, FMT_MESSAGE)


/** \brief Log warning messages */
#define LOG_WARN_ARGS( FMT_MESSAGE, ... )                                       \
    GetApplicationLogger()->Log                                                 \
    (LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, FMT_MESSAGE, __VA_ARGS__)


/** \brief Log error messages with out extra arguments */
#define LOG_ERROR( FMT_MESSAGE )                                                \
    GetApplicationLogger()->Log                                                 \
    (LEVEL_ERROR, __FILE__, __LINE__, __FUNCTION__, FMT_MESSAGE)


/** \brief Log timer value with extra arguments */
#define LOG_CPU_TIME_PROFILE( FMT_MESSAGE, ... )                                \
    GetApplicationLogger()->Log                                                 \
    (LEVEL_PROFILE_CPU, __FILE__, __LINE__, __FUNCTION__, FMT_MESSAGE, __VA_ARGS__)


/** \brief Log timer value with extra arguments */
#define LOG_GPU_TIME_PROFILE( FMT_MESSAGE, ... )                                \
    GetApplicationLogger()->Log                                                 \
    (LEVEL_PROFILE_GPU, __FILE__, __LINE__, __FUNCTION__, FMT_MESSAGE, __VA_ARGS__)


/** \brief Log error messages */
#define LOG_ERROR_ARGS( FMT_MESSAGE, ... )                                      \
    GetApplicationLogger()->Log                                                 \
    (LEVEL_ERROR, __FILE__, __LINE__, __FUNCTION__, FMT_MESSAGE, __VA_ARGS__)


/** \brief Log debugging information */
#define BEGIN()                                               \
    GetApplicationLogger()->Log                                                 \
    (LEVEL_BEGIN, __FILE__, __LINE__, __FUNCTION__, __FUNCTION__)

/** \brief Log debugging information */
#define END()                                      \
    GetApplicationLogger()->Log                                                 \
    (LEVEL_END, __FILE__, __LINE__, __FUNCTION__, __FUNCTION__)


#define LOG_EXIT()                                                              \
    std::cout << "Exitting ... " << std::endl;                                                    \
    exit(0);

#endif
