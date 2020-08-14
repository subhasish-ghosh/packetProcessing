//
// Created by subhasish on 14/08/2020.
//

#include <map>
#include "CDP_BatteryPackets.h"
#include "CDP_BatteryPower.h"
#include "CDP_BatteryStatus.h"

std::map<CDP_BatteryPackets::CDP_BatteryPacketsType_t, CDP_BatteryPackets::getPacketObjFuncPtr_t> getPacketObjMap = {
        std::make_pair(CDP_BatteryPackets::CDP_PACKETSTYPE_BATTERYPOWER, CDP_BatteryPower::getObj),
        std::make_pair(CDP_BatteryPackets::CDP_PACKETSTYPE_BATTERYSTATUS, CDP_BatteryStatus::getObj),

        std::make_pair(CDP_BatteryPackets::CDP_PACKETTYPE_MAX, nullptr) // terminator: add new class above this
};