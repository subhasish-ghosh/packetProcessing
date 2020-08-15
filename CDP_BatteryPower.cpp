//
// Created by subhasish on 13/08/2020.
//

#include <netinet/in.h>
#include <chrono>
#include "CDP_BatteryPower.h"

void CDP_BatteryPower::step(std::vector<uint8_t> &data) {

    try {
        format = (CDP_PacketFormat_t *) (&data[0]);
        format->time = be32toh(format->time);
        format->volt = be32toh(format->volt);
        format->current = be64toh(format->current);

        cdp_dbg("time: ", uint32_t(format->time), " volt: ", uint32_t(format->volt), " current: ",
                uint64_t(format->current));

        /*cdp_info(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::milliseconds(format->time)).count(), ";",
                 strbattStatus[format->battStatus]);*/
    } catch (std::exception &e) {
        cdp_err("CDP_BatteryPower::step ", e.what());
        throw;
    } catch (...) {
        cdp_err("CDP_BatteryPower::step failed due to unknown reasons");
        throw;
    }
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

CDP_BatteryPackets *CDP_BatteryPower::getObj(CDP_BatteryPackets::CDP_BatteryPacketsType_t &typelocal) {
    CDP_BatteryLogger log;
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
    } catch (std::exception &e) {
        log.cdp_err("CDP_BatteryPower::getObj ", e.what());
        throw;
    } catch (...) {
        log.cdp_err("CDP_BatteryPower::getObj failed due to unknown reasons");
        throw;
    }
}

bool CDP_BatteryPower::objInit = false;
CDP_BatteryPower *CDP_BatteryPower::cdpBatteryPower = nullptr;
CDP_BatteryPower::CDP_PacketFormat_t *CDP_BatteryPower::format = nullptr;

CDP_BatteryPower::CDP_BatteryPower() {}

CDP_BatteryPower::CDP_BatteryPower(const CDP_BatteryPower &) {}