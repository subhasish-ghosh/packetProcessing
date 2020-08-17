/**
 * @file CDP_TemplatePacketEngine.cpp
 * @brief Battery Template Class
 * @author Subhasish Ghosh
 */

#include "CDP_TemplatePacketEngine.h"

void CDP_TemplatePacketEngine::step(std::vector<uint8_t> &data) {

    try {
        // extract packet data
        format = (CDP_PacketFormat_t *) (&data[0]);
        format->time = cdp_ntohl(format->time);

        cdp_dbg("time: ", uint32_t(format->time), " Data: ", uint32_t(format->battTemplateData));

    } catch (std::exception &e) {
        cdp_err("CDP_TemplatePacketEngine::step ", e.what());
        throw;
    } catch (...) {
        cdp_err("CDP_TemplatePacketEngine::step failed due to unknown reasons");
        throw;
    }
}

std::string CDP_TemplatePacketEngine::get_name(void) {
    return name;
}

CDP_TemplatePacketEngine::CDP_BatteryPacketsType_t CDP_TemplatePacketEngine::get_type(void) {
    return type;
}

ssize_t CDP_TemplatePacketEngine::get_dataLen(void) {
    return datalen;
}

CDP_BatteryPackets *CDP_TemplatePacketEngine::getObj(CDP_BatteryPackets::CDP_BatteryPacketsType_t &typelocal) {
    CDP_BatteryLogger log;
    try {

        if (type == typelocal) {
            if (false == objInit) {
                cdpBatteryTemplate = new CDP_TemplatePacketEngine();
                objInit = true;
                return cdpBatteryTemplate;
            } else {
                return cdpBatteryTemplate;
            }
        } else {
            return nullptr;
        }
    } catch (std::exception &e) {
        log.cdp_err("CDP_TemplatePacketEngine::getObj ", e.what());
        throw;
    } catch (...) {
        log.cdp_err("CDP_TemplatePacketEngine::getObj failed due to unknown reasons");
        throw;
    }
}

bool CDP_TemplatePacketEngine::get_error(void) {
    return stateErrorDetected;
}

CDP_TemplatePacketEngine::CDP_TemplatePacketEngine() {}

CDP_TemplatePacketEngine::CDP_TemplatePacketEngine(const CDP_TemplatePacketEngine &) {}