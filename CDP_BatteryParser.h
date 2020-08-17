/**
 * @file CDP_BatteryParser.h
 * @brief Battery Parser Class
 * @author Subhasish Ghosh
 */
#ifndef CODINGTEST_CDP_BATTERYPARSER_H
#define CODINGTEST_CDP_BATTERYPARSER_H


#include <iostream>
#include <fstream>
#include "CDP_BatteryLogger.h"

/**
 * @def CDP_PACKETLEN_MAX
 * @brief This macro is used to limit the max packet length
 */
#define CDP_PACKETLEN_MAX   (UINT32_MAX/UINT8_MAX)

/**
 * @class CDP_BatteryParser
 * @brief The Battery Packets Parsing Class
 * @details This class is used to retrieve the data from a stream and check for packet type and errors. If no errors are
 * found, it forwards the packet to the specialised packet processing class.
 */
class CDP_BatteryParser : public CDP_BatteryLogger {

public:
    /**
    * @fn cdp_dbg(Args &&... args)
    * @tparam Args
    * @param args
    * @brief Class specific override for cdp_dbg
    * @returns void
    */
    template<typename ...Args>
    void cdp_dbg(Args &&... args) {
        if (CDP_BatteryLogger::getLogLevel() >= CDP_LOGGER_LEVEL_DBG) {
            std::stringstream stream;
            (stream << ... << args);
            std::cout << "CDP_BatteryParser: " << stream.str() << '\n';
        }
    }

    /**
     * @fn void run(const std::string  &fileName)
     * @param fileName
     * @returns void
     * @brief This function is used to execute the packet processing engine until end-of-file or any processing errors.
     */
    static void run(const std::string &fileName);
};


#endif //CODINGTEST_CDP_BATTERYPARSER_H
