//
// Created by subhasish on 13/08/2020.
//

#include "CDP_BatteryPower.h"

void CDP_BatteryPower::step(std::vector<uint8_t> &data) {

    try {
        format = (CDP_PacketFormat_t *) (&data[0]);
        format->time = cdp_ntohl(format->time);
        format->volt = cdp_ntohl(format->volt);
        format->current = cdp_ntohll(format->current);

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

        static std::pair currPowerState = std::make_pair<uint32_t, uint32_t>(0, 0);
        currPowerState.second = 0;
        currPowerState.first = format->time;
        /* Search for a legal state */
        for (currPowerState.second = 0; currPowerState.second < mwattStateTable.size(); currPowerState.second++) {
            if (mWatt == std::clamp<uint64_t>(mWatt, mwattStateTable[currPowerState.second].first,
                                              mwattStateTable[currPowerState.second].second)) {
                break;
            }
        }

        /* If current state is illegal, then ignore */
        if (currPowerState.second >= mwattStateTable.size()) {
            cdp_err("Invalid power state..Ignoring");
            stateErrorDetected = true;
            return;
        }

        /* Check Debounce */
        if(currPowerState.second != prevPowerStateCommit.second) {
            if(currPowerState.second != prevPowerStateDBounce.second) {
                prevPowerStateDBounce = currPowerState;
            } else {
                if ((currPowerState.first - prevPowerStateDBounce.first) >= 10) {
                    currPowerStateCommit = prevPowerStateDBounce;
                }
            }
        }

        /* Search for legal state transition */
        if (prevPowerStateCommit.second != currPowerStateCommit.second) {
            uint32_t itrState = 0;
            for (itrState = 0; itrState < stateTable.size(); itrState++) {
                if ((prevPowerStateCommit.second == std::get<0>(stateTable[itrState])) &&
                    (currPowerStateCommit.second == std::get<1>(stateTable[itrState]))) {
                    cdp_info(std::chrono::duration_cast<std::chrono::seconds>(
                            std::chrono::milliseconds(currPowerStateCommit.first)).count(), ";",
                             prevPowerStateCommit.second, '-', currPowerStateCommit.second);
                    prevPowerStateCommit = currPowerStateCommit;
                    break;
                }
            }

            /* If state transition is illegal, then ignore */
            if (itrState >= stateTable.size()) {
                cdp_err("Invalid power state transition<", prevPowerStateCommit.second, '-', currPowerStateCommit.second, ">",
                        "..Ignoring");
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

CDP_BatteryPower::CDP_BatteryPacketsType_t CDP_BatteryPower::get_type(void) {
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