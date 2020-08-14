//
// Created by subhasish on 13/08/2020.
//

#ifndef CODINGTEST_CDP_BATTERYSTATUS_H
#define CODINGTEST_CDP_BATTERYSTATUS_H


#include "CDP_BatteryLogger.h"
#include "CDP_BatteryPackets.h"

class CDP_BatteryStatus : public CDP_BatteryPackets {
public:

    template<typename ...Args>
    void cdp_dbg(Args &&... args) {
        if (CDP_BatteryLogger::getLogLevel() >= CDP_LOGGER_LEVEL_DBG) {
            std::stringstream stream;
            (stream << ... << args);
            std::cout << "CDP_BatteryStatus: " << stream.str() << '\n';
        }
    }

    template<typename ...Args>
    void cdp_info(Args &&... args) {
        if (CDP_BatteryLogger::getLogLevel() >= CDP_LOGGER_LEVEL_INFO) {
            std::stringstream stream;
            (stream << ... << args);
            std::cout << "B;" << stream.str() << '\n';
        }
    }

    void step(std::vector<uint8_t>);

    static CDP_BatteryPackets *getObj(CDP_BatteryPackets::CDP_BatteryPacketsType_t type);

    CDP_BatteryPacketsType get_type(void);

    ssize_t get_dataLen(void);

private:
    static const CDP_BatteryPacketsType type = CDP_PACKETSTYPE_BATTERYSTATUS;
    static const ssize_t datalen = 5;
    static bool objInit;
    static CDP_BatteryStatus *cdpBatteryStatus;

    CDP_BatteryStatus();

    CDP_BatteryStatus(const CDP_BatteryStatus &);

    CDP_BatteryStatus &operator=(const CDP_BatteryStatus &);
};


#endif //CODINGTEST_CDP_BATTERYSTATUS_H
