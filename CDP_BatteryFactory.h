//
// Created by subhasish on 13/08/2020.
//

#ifndef CODINGTEST_CDP_BATTERYFACTORY_H
#define CODINGTEST_CDP_BATTERYFACTORY_H

#include "CDP_BatteryPackets.h"
#include "CDP_BatteryPower.h"
#include "CDP_BatteryStatus.h"

class CDP_BatteryFactory: public CDP_BatteryLogger {

public:
    static CDP_BatteryPackets * getPacketObj(CDP_BatteryPackets::CDP_BatteryPacketsType_t &type);
};

#endif //CODINGTEST_CDP_BATTERYFACTORY_H
