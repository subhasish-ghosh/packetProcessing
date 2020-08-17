//
// Created by subhasish on 03/08/2020.
//

#ifndef CODINGTEST_CDP_BATTERYLOGGER_H
#define CODINGTEST_CDP_BATTERYLOGGER_H

#include <cstdarg>
#include <cstdio>
#include <iostream>
#include <sstream>
#include "CDP_Platform.h"

class CDP_BatteryLogger {
public:

    template<typename... Args>
    void cdp_err(Args &&... args) {
        if (CDP_BatteryLogger::getLogLevel() >= CDP_LOGGER_LEVEL_ERROR) {
            std::stringstream stream;
            (stream << ... << args);
            std::cout << "ERR:" << stream.str() << '\n';
        }
    }

    template<typename ...Args>
    void cdp_info(Args &&... args) {
        if (CDP_BatteryLogger::getLogLevel() >= CDP_LOGGER_LEVEL_INFO) {
            std::stringstream stream;
            (stream << ... << args);
            std::cout << "INFO: " << stream.str() << '\n';
        }
    }

    template<typename ...Args>
    void cdp_dbg(Args &&... args) {
        if (CDP_BatteryLogger::getLogLevel() >= CDP_LOGGER_LEVEL_DBG) {
            std::stringstream stream;
            (stream << ... << args);
            std::cout << "DBG: " << stream.str() << '\n';
        }
    }

    static void setLogLevel(int logLevel);

    static int getLogLevel();

    enum CDP_LoggerLevel: uint8_t {
        CDP_LOGGER_LEVEL_ERROR,
        CDP_LOGGER_LEVEL_INFO,
        CDP_LOGGER_LEVEL_DBG
    };

private:
    static int logLevel;
};


#endif //CODINGTEST_CDP_BATTERYLOGGER_H
