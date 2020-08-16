//
// Created by subhasish on 14/08/2020.
//

#include "CDP_BatteryPackets.h"
#include "CDP_BatteryPower.h"
#include "CDP_BatteryStatus.h"

CDP_BatteryPackets* CDP_BatteryPackets::default_PktHandler(CDP_BatteryPacketsType_t& t) {

    throw("Invalid Packet Type");
    return nullptr;
}

std::map<CDP_BatteryPackets::CDP_BatteryPacketsType_t, CDP_BatteryPackets::getPacketObjFuncPtr_t> getPacketObjMap = {
        std::make_pair(CDP_BatteryPackets::CDP_BatteryPacketsType::CDP_PACKETSTYPE_BATTERYPOWER, CDP_BatteryPower::getObj),
        std::make_pair(CDP_BatteryPackets::CDP_BatteryPacketsType::CDP_PACKETSTYPE_BATTERYSTATUS, CDP_BatteryStatus::getObj),

        std::make_pair(CDP_BatteryPackets::CDP_BatteryPacketsType::CDP_PACKETTYPE_MAX, CDP_BatteryPackets::default_PktHandler) // terminator: add new class above this
};