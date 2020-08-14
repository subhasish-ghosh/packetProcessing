//
// Created by subhasish on 13/08/2020.
//

#include "CDP_BatteryPower.h"

void CDP_BatteryPower::step(std::vector<uint8_t> & data) {

}

std::string CDP_BatteryPower::get_name(void) {
    return name;
}

CDP_BatteryPower::CDP_BatteryPacketsType CDP_BatteryPower::get_type(void) {
    return CDP_BatteryPower::type;
}

ssize_t CDP_BatteryPower::get_dataLen(void) {
    return CDP_BatteryPower::datalen;
}

CDP_BatteryPackets *CDP_BatteryPower::getObj(CDP_BatteryPackets::CDP_BatteryPacketsType_t type) {
    try {
        if (CDP_BatteryPower::type == type) {
            if (false == CDP_BatteryPower::objInit) {
                CDP_BatteryPower::cdpBatteryPower = new CDP_BatteryPower();
                CDP_BatteryPower::objInit = true;
                return CDP_BatteryPower::cdpBatteryPower;
            } else {
                return CDP_BatteryPower::cdpBatteryPower;
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

CDP_BatteryPower::CDP_BatteryPower() {}

CDP_BatteryPower::CDP_BatteryPower(const CDP_BatteryPower &) {}