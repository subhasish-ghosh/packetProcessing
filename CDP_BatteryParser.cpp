//
// Created by subhasish on 03/08/2020.
//

#include "CDP_BatteryParser.h"
#include "CDP_BatteryPackets.h"
#include "CDP_BatteryFactory.h"

void CDP_BatteryParser::run(std::string fileName) {
    CDP_BatteryParser obj;
    std::ifstream fp;

    try {
        fp.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fp.open(fileName.c_str(), std::ios::binary);
    }
    catch (...) {
        obj.cdp_err("CDP_BatteryParser: File Open Error");
        throw;
    }
    obj.cdp_dbg("File Open Successful");

    try {
        while (fp.peek() != EOF) {
            std::vector<uint8_t> data;
            uint8_t type = 0;
            uint32_t errsum = 0;

            data.clear();

            fp.read(reinterpret_cast<char *> (&type), sizeof(type));

            /* Call specific packet type processor */
            CDP_BatteryPackets *batObj = CDP_BatteryFactory::getPacketObj(
                    reinterpret_cast<CDP_BatteryPackets::CDP_BatteryPacketsType_t &>(type));
            errsum = type;

            /* Determine packet len and read data */
            if (nullptr != batObj) {

                ssize_t len = batObj->get_dataLen();
                if (len > CDP_PACKETLEN_MAX) {
                    throw ("Packet Length too long");
                }

                int i = 0;
                for (i = 0; (i < len) && (fp.peek() != EOF); i++) {
                    uint8_t dat = 0;
                    fp.read(reinterpret_cast<char *> (&dat), sizeof(dat));
                    data.push_back(dat);
                    errsum += dat;
                }

                if (i != len) {
                    throw ("Invalid EOF");
                } else {
                    /* Check any error */
                    uint8_t errval = 0;
                    fp.read(reinterpret_cast<char *> (&errval), sizeof(errval));

                    errsum = errsum % (UINT8_MAX + 1); //TODO:: need to check why without +1 it worked sometimes
                    if (errsum != errval) {
                        obj.cdp_err("Packet Data Error..Ignoring, Type: ", batObj->get_name(), " expected: ",
                                    std::uppercase, std::hex, std::showbase, uint32_t(errsum), " received err: ",
                                    uint32_t(errval));
                        continue;
                    } else {
                        obj.cdp_dbg("Packet Receive Success, Type: ", batObj->get_name(), " received err: ",
                                    std::uppercase, std::hex, std::showbase, uint32_t(errval));
                    }
                }

            } else {
                throw ("Bad Battery Object");
            }

            batObj->step(data);
        }
        for(int iterTypes = 0; iterTypes < CDP_BatteryPackets::CDP_PACKETTYPE_MAX; iterTypes++) {
            CDP_BatteryPackets *batObjErr = CDP_BatteryFactory::getPacketObj(
                    reinterpret_cast<CDP_BatteryPackets::CDP_BatteryPacketsType_t &>(iterTypes));

            if(nullptr != batObjErr) {
                if(batObjErr->get_error()) {
                    obj.cdp_err(batObjErr->get_name(), ": Warning: System Errors Detected!!. System state data unreliable");
                }
            }
        }
    } catch (const char* str) {
        obj.cdp_err("CDP_BatteryParser: ", str);
        throw;
    } catch (std::exception &e) {
        obj.cdp_err("CDP_BatteryParser: ", e.what());
        throw;
    } catch (...) {
        obj.cdp_err("CDP_BatteryParser: failed due to unknown reasons");
        throw;
    }

    obj.cdp_dbg("Parser ended successfully");
}
