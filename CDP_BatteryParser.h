//
// Created by subhasish on 03/08/2020.
//

#ifndef CODINGTEST_CDP_BATTERYPARSER_H
#define CODINGTEST_CDP_BATTERYPARSER_H


#include <iostream>
#include <fstream>
#include "CDP_BatteryLogger.h"

class CDP_BatteryParser : public CDP_BatteryLogger {

public:

    template<typename ...Args>
    void cdp_dbg(Args &&... args) {
        if (CDP_BatteryLogger::getLogLevel() >= CDP_LOGGER_LEVEL_DBG) {
            std::stringstream stream;
            (stream << ... << args);
            std::cout << "CDP_BatteryParser: " << stream.str() << '\n';
        }
    }

    static void run(std::string fileName);
};


#endif //CODINGTEST_CDP_BATTERYPARSER_H
