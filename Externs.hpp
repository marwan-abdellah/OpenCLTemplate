#ifndef EXTERNS_HPP
#define EXTERNS_HPP

#include "ApplicationData.h"
#include "Logger.h"
#include "clHardware.h"

/** @brief Application data structure shared among all the project files */
extern ApplicationData* appData;

/** \brief  Application logging system */
extern Logger* ex_logger;

/** \brief Application logging system */
extern clHardware* ex_hardwareInfo;

#endif // EXTERNS_HPP

