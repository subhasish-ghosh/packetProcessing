//
// Created by subhasish on 03/08/2020.
//

#include "CDP_BatteryLogger.h"

int CDP_BatteryLogger::logLevel = CDP_LOGGER_LEVEL_INFO;

void CDP_BatteryLogger::setLogLevel(int logLevel) {
    CDP_BatteryLogger::logLevel = logLevel;
}

int CDP_BatteryLogger::getLogLevel() {
    return logLevel;
}