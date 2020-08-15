//
// Created by subhasish on 13/08/2020.
//

#include <netinet/in.h>
#include <chrono>
#include "CDP_BatteryStatus.h"

void CDP_BatteryStatus::step(std::vector<uint8_t> &data) {

    format = (CDP_PacketFormat_t *) (&data[0]);
    format->time = be32toh(format->time);
    cdp_dbg("time: ", uint32_t(format->time), " status: ", uint32_t(format->battStatus));

    cdp_info(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::milliseconds(format->time)).count(), ";",
             state[format->battStatus]);
}

std::string CDP_BatteryStatus::get_name(void) {
    return name;
}

CDP_BatteryStatus::CDP_BatteryPacketsType CDP_BatteryStatus::get_type(void) {
    return type;
}

ssize_t CDP_BatteryStatus::get_dataLen(void) {
    return datalen;
}

CDP_BatteryPackets *CDP_BatteryStatus::getObj(CDP_BatteryPackets::CDP_BatteryPacketsType_t &typelocal) {
    if (type == typelocal) {
        if (false == objInit) {
            cdpBatteryStatus = new CDP_BatteryStatus();
            objInit = true;
            return cdpBatteryStatus;
        } else {
            return cdpBatteryStatus;
        }
    } else {
        return nullptr;
    }
    return nullptr;
}

bool CDP_BatteryStatus::objInit = false;
CDP_BatteryStatus::CDP_PacketFormat_t *CDP_BatteryStatus::format = nullptr;
CDP_BatteryStatus *CDP_BatteryStatus::cdpBatteryStatus = nullptr;

CDP_BatteryStatus::CDP_BatteryStatus() {}

CDP_BatteryStatus::CDP_BatteryStatus(const CDP_BatteryStatus &) {}