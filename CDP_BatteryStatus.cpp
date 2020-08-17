/**
 * @file CDP_BatteryStatus.cpp
 * @brief Battery Status Class
 * @author Subhasish Ghosh
 */

#include "CDP_BatteryStatus.h"

void CDP_BatteryStatus::step(std::vector<uint8_t> &data) {

    try {
        // extract packet data
        format = (CDP_PacketFormat_t *) (&data[0]);
        format->time = cdp_ntohl(format->time);

        cdp_dbg("time: ", uint32_t(format->time), " status: ", uint32_t(format->battStatus));

        if (format->battStatus >= strbattStatus.size()) {
            cdp_err("Invalid Battery Status Received <", uint32_t(format->battStatus), "> ..ignoring");
            stateErrorDetected = true;
            return;
        }

        cdp_info(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::milliseconds(format->time)).count(), ";",
                 strbattStatus[format->battStatus]);
    } catch (std::exception &e) {
        cdp_err("CDP_BatteryStatus::step ", e.what());
        throw;
    } catch (...) {
        cdp_err("CDP_BatteryStatus::step failed due to unknown reasons");
        throw;
    }
}

std::string CDP_BatteryStatus::get_name(void) {
    return name;
}

CDP_BatteryStatus::CDP_BatteryPacketsType_t CDP_BatteryStatus::get_type(void) {
    return type;
}

ssize_t CDP_BatteryStatus::get_dataLen(void) {
    return datalen;
}

CDP_BatteryPackets *CDP_BatteryStatus::getObj(CDP_BatteryPackets::CDP_BatteryPacketsType_t &typelocal) {
    CDP_BatteryLogger log;
    try {

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
    } catch (std::exception &e) {
        log.cdp_err("CDP_BatteryStatus::getObj ", e.what());
        throw;
    } catch (...) {
        log.cdp_err("CDP_BatteryStatus::getObj failed due to unknown reasons");
        throw;
    }
}

bool CDP_BatteryStatus::get_error(void) {
    return stateErrorDetected;
}

CDP_BatteryStatus::CDP_BatteryStatus() {}

CDP_BatteryStatus::CDP_BatteryStatus(const CDP_BatteryStatus &) {}