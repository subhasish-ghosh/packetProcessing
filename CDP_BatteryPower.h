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

    void step(std::vector<uint8_t> &);

    static CDP_BatteryPackets *getObj(CDP_BatteryPackets::CDP_BatteryPacketsType_t &type);

    CDP_BatteryPacketsType get_type(void);

    ssize_t get_dataLen(void);

    std::string get_name(void);

    bool get_error(void);

private:
    inline static const CDP_BatteryPacketsType type = CDP_PACKETSTYPE_BATTERYPOWER;
    inline static const ssize_t datalen = 16;
    inline static const std::string name = "Battery Power";
    inline static bool objInit = false;
    inline static bool stateErrorDetected = false;
    inline static CDP_BatteryPower *cdpBatteryPower = nullptr;
    typedef struct {
        uint32_t time;
        uint32_t volt;
        uint64_t current;
    } __attribute__((packed)) CDP_PacketFormat_t;
    inline static CDP_PacketFormat_t *format = nullptr;
    inline static uint32_t prevPowerState = 0;
    inline static std::array mwattStateTable = {std::make_pair<uint64_t>(0, 200),
                                                std::make_pair<uint64_t>(300, 450),
                                                std::make_pair<uint64_t>(550, 650),
                                                std::make_pair<uint64_t>(800, 1200)};

    inline static std::array stateTable = {std::make_tuple(0, 1,"Starting"),
                                           std::make_tuple(1, 2,"Warm up"),
                                           std::make_tuple(2, 3,"Main Session"),
                                           std::make_tuple(3, 2,"Cool down"),
                                           std::make_tuple(2, 0,"Complete")};
    CDP_BatteryPower();

    CDP_BatteryPower(const CDP_BatteryPower &);

    CDP_BatteryPower &operator=(const CDP_BatteryPower &);
};


#endif //CODINGTEST_CDP_BATTERYPOWER_H
