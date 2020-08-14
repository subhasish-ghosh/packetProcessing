//
// Created by subhasish on 03/08/2020.
//

#include "CDP_BatteryParser.h"
#include "CDP_BatteryPackets.h"
#include "CDP_BatteryFactory.h"

void CDP_BatteryParser::run(std::string fileName) {
    CDP_BatteryParser obj = CDP_BatteryParser();
    std::ifstream fp;

    try {
        fp.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fp.open(fileName.c_str(), std::ios::binary);
    }
    catch (...) {
        obj.cdp_err("File Open Error");
        throw;
    }
    obj.cdp_dbg("File Open Successful");

    while (1) { // Until File EOF
        std::vector<uint8_t> data;

        /* Determine packet type and check any error */

        /* Call specific packet type processor */
        CDP_BatteryPackets *batObj = CDP_BatteryFactory::getPacketObj(CDP_BatteryPackets::CDP_PACKETSTYPE_BATTERYPOWER);

        batObj->step(data);
    }
}
