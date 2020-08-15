//
// Created by subhasish on 13/08/2020.
//

#include <netinet/in.h>
#include <chrono>
#include <algorithm>
#include "CDP_BatteryPower.h"

void CDP_BatteryPower::step(std::vector<uint8_t> &data) {

    try {
        format = (CDP_PacketFormat_t *) (&data[0]);
        format->time = be32toh(format->time);
        format->volt = be32toh(format->volt);
        format->current = be64toh(format->current);

        cdp_dbg("time: ", uint32_t(format->time), " volt: ", uint32_t(format->volt), " current: ",
                uint64_t(format->current));

        if ((format->current > mwattStateTable[mwattStateTable.size() - 1].second) && format->volt) {
            cdp_err("Invalid power state due to high current..Ignoring");
            stateErrorDetected = true;
            return;
        }

        if ((format->volt > mwattStateTable[mwattStateTable.size() - 1].second) && format->current) {
            cdp_err("Invalid power state due to high voltage..Ignoring");
            stateErrorDetected = true;
            return;
        }

        uint64_t mWatt = format->current * format->volt;
        int currPowerState = 0;
        for (currPowerState = 0; currPowerState < mwattStateTable.size(); currPowerState++) {
            if (mWatt == std::clamp<uint64_t>(mWatt, mwattStateTable[currPowerState].first,
                                              mwattStateTable[currPowerState].second)) {
                break;
            }
        }

        if (currPowerState >= mwattStateTable.size()) {
            cdp_err("Invalid power state..Ignoring");
            stateErrorDetected = true;
            return;
        }

        if (prevPowerState != currPowerState) {
            int itrState = 0;
            for (itrState = 0; itrState < stateTable.size(); itrState++) {
                if ((prevPowerState == std::get<0>(stateTable[itrState])) &&
                    (currPowerState == std::get<1>(stateTable[itrState]))) {
                    cdp_info(std::chrono::duration_cast<std::chrono::seconds>(
                            std::chrono::milliseconds(format->time)).count(), ";",
                             prevPowerState, '-', currPowerState);
                    prevPowerState = currPowerState;
                    break;
                }
            }

            if (itrState >= stateTable.size()) {
                cdp_err("Invalid power state transition<", prevPowerState, '-', currPowerState, ">", "..Ignoring");
                stateErrorDetected = true;
                return;
            }
        }
    } catch (const char *str) {
        cdp_err("CDP_BatteryPower::step ", str);
        throw;
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

bool CDP_BatteryPower::get_error(void) {
    return stateErrorDetected;
}
CDP_BatteryPower::CDP_BatteryPower() {}

CDP_BatteryPower::CDP_BatteryPower(const CDP_BatteryPower &) {}