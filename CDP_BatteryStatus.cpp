//
// Created by subhasish on 13/08/2020.
//

#include "CDP_BatteryStatus.h"

void CDP_BatteryStatus::step(std::vector<uint8_t> &data) {

}

std::string CDP_BatteryStatus::get_name(void) {
    return name;
}

CDP_BatteryStatus::CDP_BatteryPacketsType CDP_BatteryStatus::get_type(void) {
    return CDP_BatteryStatus::type;
}

ssize_t CDP_BatteryStatus::get_dataLen(void) {
    return CDP_BatteryStatus::datalen;
}

CDP_BatteryPackets *CDP_BatteryStatus::getObj(CDP_BatteryPackets::CDP_BatteryPacketsType_t type) {
    if (CDP_BatteryStatus::type == type) {
        if (false == CDP_BatteryStatus::objInit) {
            CDP_BatteryStatus::cdpBatteryStatus = new CDP_BatteryStatus();
            CDP_BatteryStatus::objInit = true;
            return CDP_BatteryStatus::cdpBatteryStatus;
        } else {
            return CDP_BatteryStatus::cdpBatteryStatus;
        }
    } else {
        return nullptr;
    }
    return nullptr;
}

bool CDP_BatteryStatus::objInit = false;
CDP_BatteryStatus *CDP_BatteryStatus::cdpBatteryStatus = nullptr;

CDP_BatteryStatus::CDP_BatteryStatus() {}

CDP_BatteryStatus::CDP_BatteryStatus(const CDP_BatteryStatus &) {}