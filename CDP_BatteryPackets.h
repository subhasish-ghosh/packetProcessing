/**
 * @file CDP_BatteryPackets.h
 * @brief Battery Packets Class
 * @author Subhasish Ghosh
 */

#ifndef CODINGTEST_CDP_BATTERYPACKETS_H
#define CODINGTEST_CDP_BATTERYPACKETS_H

#include <vector>
#include <map>
#include "CDP_BatteryLogger.h"

/**
 * @class CDP_BatteryPackets
 * @brief The Battery Packets Processing Class
 * @details This class is used to retrieve specialised packet processing object
 * To add a new packet processing engine:
 * 1. Define a new Packet Type in CDP_BatteryPackets.h
 * 2. Define a Packet Processing Class (refer: CDP_BatteryStatus.h/cpp as an example)
 * 3. Add the class entry in the array getPacketObjMap (found in CDP_BatteryPackets.cpp)
 */
class CDP_BatteryPackets : public CDP_BatteryLogger {
public:

    /**
     * @enum CDP_BatteryPacketsType
     * @brief Use this enum to add new packet processing class.
     * @details Ensure no duplicate packet types are present. Preserve the Min & Max enums i.e add new types
     * between the Min and Max packet types.
     */
    typedef enum CDP_BatteryPacketsType : uint8_t {
        CDP_PACKETTYPE_MIN,
        CDP_PACKETSTYPE_BATTERYPOWER = CDP_PACKETTYPE_MIN,
        CDP_PACKETSTYPE_BATTERYSTATUS,
        CDP_PACKETTYPE_MAX,
    } CDP_BatteryPacketsType_t;

    /**
     * @typedef getPacketObjFuncPtr_t
     * @brief Function Pointer typedef to handle packet specific object allocation
     */
    typedef CDP_BatteryPackets *(*getPacketObjFuncPtr_t)(CDP_BatteryPacketsType_t &);

    /**
     * @fn step(std::vector<uint8_t> &)
     * @brief This function is used to cycle the class state machine once
     * @param data packet to be processed
     * @returns void
     */
    virtual void step(std::vector<uint8_t> &) = 0;

    /**
     * @fn CDP_BatteryPacketsType_t get_type(void)
     * @brief This function is used to retrieve the packet type of the class
     * @param void
     * @returns CDP_BatteryPacketsType_t
     */
    virtual CDP_BatteryPacketsType_t get_type(void) = 0;

    /**
     * @fn ssize_t get_dataLen(void)
     * @brief This function is used to retrieve the data pkt len of the class
     * @param void
     * @returns ssize_t
     */
    virtual ssize_t get_dataLen(void) = 0;

    /**
     * @fn std::string get_name(void)
     * @brief This function is used to retrieve the data name of the class
     * @param void
     * @returns std::string
     */
    virtual std::string get_name(void) = 0;

    /**
     * @fn bool get_error(void)
     * @brief This function is used to retrieve the error occurred in the class
     * @param void
     * @returns bool
     */
    virtual bool get_error(void) = 0;

    /**
     * @fn CDP_BatteryPackets* default_PktHandler(CDP_BatteryPacketsType_t&)
     * @brief This is an default function for error handling
     * @param type
     * @returns CDP_BatteryPackets*
     */
    static CDP_BatteryPackets *default_PktHandler(CDP_BatteryPacketsType_t &);

private:

};

extern std::map<CDP_BatteryPackets::CDP_BatteryPacketsType_t, CDP_BatteryPackets::getPacketObjFuncPtr_t> getPacketObjMap;


#endif //CODINGTEST_CDP_BATTERYPACKETS_H
