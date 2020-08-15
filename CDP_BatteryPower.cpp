//
// Created by subhasish on 13/08/2020.
//

#include <netinet/in.h>
#include "CDP_BatteryPower.h"

void CDP_BatteryPower::step(std::vector<uint8_t> & data) {

    format = (CDP_PacketFormat_t *) (&data[0]);
    format->time = be32toh(format->time);
    format->volt = be32toh(format->volt);
    format->current = be64toh(format->current);

    cdp_dbg("time: ", uint32_t(format->time), " volt: ", uint32_t(format->volt), " current: ", uint64_t(format->current));
}

std::string CDP_BatteryPower::get_name(void) {
    return name;
}

CDP_BatteryPower::CDP_BatteryPacketsType CDP_BatteryPower::get_type(void) {
    return type;
}

ssize_t CDP_BatteryPower::get_dataLen(void) {
    return datalen;
}

CDP_BatteryPackets *CDP_BatteryPower::getObj(CDP_BatteryPackets::CDP_BatteryPacketsType_t typelocal) {
    try {
        if (type == typelocal) {
            if (false == objInit) {
                cdpBatteryPower = new CDP_BatteryPower();
                objInit = true;
                return cdpBatteryPower;
            } else {
                return cdpBatteryPower;
            }
        } else {
            return nullptr;
        }
    } catch (...) {

    }
    return nullptr;
}

bool CDP_BatteryPower::objInit = false;
CDP_BatteryPower *CDP_BatteryPower::cdpBatteryPower = nullptr;
CDP_BatteryPower::CDP_PacketFormat_t *CDP_BatteryPower::format = nullptr;

CDP_BatteryPower::CDP_BatteryPower() {}

CDP_BatteryPower::CDP_BatteryPower(const CDP_BatteryPower &) {}