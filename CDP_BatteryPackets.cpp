/**
 * @file CDP_BatteryPackets.cpp
 * @brief Battery Packet Class
 * @author Subhasish Ghosh
 */

#include "CDP_BatteryPackets.h"
#include "CDP_BatteryPower.h"
#include "CDP_BatteryStatus.h"

CDP_BatteryPackets *CDP_BatteryPackets::default_PktHandler(CDP_BatteryPacketsType_t &t) {

    throw ("Invalid Packet Type");
    return nullptr;
}

/**
 * @var getPacketObjMap
 * @brief This map contains entries for specialised packet processing classes.
 * @details The map is of the form <CDP_BatteryPacketsType_t, getPacketObjFuncPtr_t>.
 * The function pointer is used to retrieve a specialised packet processing object.
 * Add a new entry here for newly added packet types and implement the class getObj.
 * To add a new packet processing engine:
 * 1. Define a new Packet Type in CDP_BatteryPackets.h
 * 2. Define a Packet Processing Class (refer: CDP_BatteryStatus.h/cpp as an example)
 * 3. Add the class entry in the array getPacketObjMap (found in CDP_BatteryPackets.cpp)
 */
std::map<CDP_BatteryPackets::CDP_BatteryPacketsType_t, CDP_BatteryPackets::getPacketObjFuncPtr_t> getPacketObjMap = {
        std::make_pair(CDP_BatteryPackets::CDP_BatteryPacketsType::CDP_PACKETSTYPE_BATTERYPOWER,
                       CDP_BatteryPower::getObj),
        std::make_pair(CDP_BatteryPackets::CDP_BatteryPacketsType::CDP_PACKETSTYPE_BATTERYSTATUS,
                       CDP_BatteryStatus::getObj),

        std::make_pair(CDP_BatteryPackets::CDP_BatteryPacketsType::CDP_PACKETTYPE_MAX,
                       CDP_BatteryPackets::default_PktHandler) // terminator: add new class above this
};