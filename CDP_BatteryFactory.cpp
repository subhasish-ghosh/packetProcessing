//
// Created by subhasish on 13/08/2020.
//

#include "CDP_BatteryFactory.h"

CDP_BatteryPackets *CDP_BatteryFactory::getPacketObj(CDP_BatteryPackets::CDP_BatteryPacketsType_t type) {

    CDP_BatteryLogger log;

    try {
        CDP_BatteryPackets *ObjPtr = getPacketObjMap.at(type)(type);

        if (nullptr != ObjPtr) {
            return ObjPtr;
        } else {
            throw ("getPacketObjMap.at returned null");
        }
    } catch (const char *str) {
        log.cdp_err("CDP_BatteryFactory::getPacketObj failed: ", str);
        throw;
    } catch (std::exception &e) {
        log.cdp_err("CDP_BatteryFactory::getPacketObj failed: ", e.what());
        throw;
    } catch (...) {
        log.cdp_err("CDP_BatteryFactory::getPacketObj failed due to unknown reasons");
        throw;
    }
}