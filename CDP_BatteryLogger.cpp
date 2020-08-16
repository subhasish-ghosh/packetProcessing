//
// Created by subhasish on 03/08/2020.
//

#include "CDP_BatteryLogger.h"

#if defined(_DEBUG)
int CDP_BatteryLogger::logLevel = CDP_LOGGER_LEVEL_DBG;
#else
int CDP_BatteryLogger::logLevel = CDP_LOGGER_LEVEL_INFO;
#endif
void CDP_BatteryLogger::setLogLevel(int logLevel) {
    CDP_BatteryLogger::logLevel = logLevel;
}

int CDP_BatteryLogger::getLogLevel() {
    return logLevel;
}