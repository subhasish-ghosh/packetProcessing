/**
 * @file CDP_BatteryLogger.h
 * @brief Battery Logger Class
 * @author Subhasish Ghosh
 */

#ifndef CODINGTEST_CDP_BATTERYLOGGER_H
#define CODINGTEST_CDP_BATTERYLOGGER_H

#include <cstdarg>
#include <cstdio>
#include <iostream>
#include <sstream>
#include "CDP_Platform.h"

/**
 * @class CDP_BatteryLogger
 * @brief The Battery Monitor Logging Class
 * @details The class can be implemented to log into an xml file if required. Currently, it implements
 * as stdout logging. The member functions can be overridden to class specific requirements. The logging can be compiled
 * in debug mode (_DEBUG) to retrieve debug logging.
 */
class CDP_BatteryLogger {
public:

    /**
    * @fn cdp_dbg(Args &&... args)
    * @tparam Args
    * @param args
    * @brief This function is used for debug level logging
    * @returns void
    */
    template<typename... Args>
    void cdp_err(Args &&... args) {
        if (CDP_BatteryLogger::getLogLevel() >= CDP_LOGGER_LEVEL_ERROR) {
            std::stringstream stream;
            (stream << ... << args);
            std::cout << "ERR:" << stream.str() << '\n';
        }
    }

    /**
    * @fn cdp_info(Args &&... args)
    * @tparam Args
    * @param args
    * @brief This function is used for information level logging
    * @returns void
    */
    template<typename ...Args>
    void cdp_info(Args &&... args) {
        if (CDP_BatteryLogger::getLogLevel() >= CDP_LOGGER_LEVEL_INFO) {
            std::stringstream stream;
            (stream << ... << args);
            std::cout << "INFO: " << stream.str() << '\n';
        }
    }

    /**
    * @fn cdp_dbg(Args &&... args)
    * @tparam Args
    * @param args
    * @brief This function is used for error level logging
    * @returns void
    */
    template<typename ...Args>
    void cdp_dbg(Args &&... args) {
        if (CDP_BatteryLogger::getLogLevel() >= CDP_LOGGER_LEVEL_DBG) {
            std::stringstream stream;
            (stream << ... << args);
            std::cout << "DBG: " << stream.str() << '\n';
        }
    }

    /**
     * @fn void setLogLevel(int logLevel)
     * @param logLevel
     * @returns void
     * @brief This function is used to set the log level dynamically
     */
    static void setLogLevel(int logLevel);

    /**
     * @fn int getLogLevel()
     * @param void
     * @returns int
     * @brief This function is used to get the log level dynamically
     */
    static int getLogLevel();

    /**
     * @enum CDP_LoggerLevel
     * @brief This defines the various logging levels available
     */
    enum CDP_LoggerLevel : uint8_t {
        CDP_LOGGER_LEVEL_ERROR,
        CDP_LOGGER_LEVEL_INFO,
        CDP_LOGGER_LEVEL_DBG
    };

private:
/**
 * @var logLevel
 * @brief Current log level
 */
    static int logLevel;
};


#endif //CODINGTEST_CDP_BATTERYLOGGER_H
