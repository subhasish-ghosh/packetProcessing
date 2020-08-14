//
// Created by subhasish on 13/08/2020.
//

#ifndef CODINGTEST_CDP_BATTERYPOWER_H
#define CODINGTEST_CDP_BATTERYPOWER_H


#include "CDP_BatteryLogger.h"
#include "CDP_BatteryPackets.h"

class CDP_BatteryPower : public CDP_BatteryPackets {
public:

    template<typename ...Args>
    void cdp_dbg(Args &&... args) {
        if (CDP_BatteryLogger::getLogLevel() >= CDP_BatteryLogger::CDP_LOGGER_LEVEL_DBG) {
            std::stringstream stream;
            (stream << ... << args);
            std::cout << "CDP_BatteryPower: " << stream.str() << '\n';
        }
    }

    template<typename ...Args>
    void cdp_info(Args &&... args) {
        if (CDP_BatteryLogger::getLogLevel() >= CDP_BatteryLogger::CDP_LOGGER_LEVEL_INFO) {
            std::stringstream stream;
            (stream << ... << args);
            std::cout << "S;" << stream.str() << '\n';
        }
    }

    void step(std::vector<uint8_t>);

    static CDP_BatteryPackets *getObj(CDP_BatteryPackets::CDP_BatteryPacketsType_t type);

    CDP_BatteryPacketsType get_type(void);

    ssize_t get_dataLen(void);

private:
    static const CDP_BatteryPacketsType type = CDP_PACKETSTYPE_BATTERYPOWER;
    static const ssize_t datalen = 16;
    static bool objInit;
    static CDP_BatteryPower *cdpBatteryPower;

    CDP_BatteryPower();

    CDP_BatteryPower(const CDP_BatteryPower &);

    CDP_BatteryPower &operator=(const CDP_BatteryPower &);
};


#endif //CODINGTEST_CDP_BATTERYPOWER_H
