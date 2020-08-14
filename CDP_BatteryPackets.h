//
// Created by subhasish on 13/08/2020.
//

#ifndef CODINGTEST_CDP_BATTERYPACKETS_H
#define CODINGTEST_CDP_BATTERYPACKETS_H


#include <vector>
#include "CDP_BatteryLogger.h"

class CDP_BatteryPackets : public CDP_BatteryLogger {

public:
    /* assign packets types and avoid duplicates */
    typedef enum CDP_BatteryPacketsType {
        CDP_PACKETTYPE_MIN,
        CDP_PACKETSTYPE_BATTERYPOWER = CDP_PACKETTYPE_MIN,
        CDP_PACKETSTYPE_BATTERYSTATUS,
        CDP_PACKETTYPE_MAX,
    } CDP_BatteryPacketsType_t;

    typedef CDP_BatteryPackets *(*getPacketObjFuncPtr_t)(CDP_BatteryPackets::CDP_BatteryPacketsType);

    virtual void step(std::vector<uint8_t>) = 0;

    virtual CDP_BatteryPacketsType get_type(void) = 0;

    virtual ssize_t get_dataLen(void) = 0;
};


#endif //CODINGTEST_CDP_BATTERYPACKETS_H