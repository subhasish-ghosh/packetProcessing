/**
 * @file CDP_BatteryFactory.h
 * @brief Battery Factory Class
 * @author Subhasish Ghosh
 */

#ifndef CODINGTEST_CDP_BATTERYFACTORY_H
#define CODINGTEST_CDP_BATTERYFACTORY_H

#include "CDP_BatteryPackets.h"
#include "CDP_BatteryPower.h"
#include "CDP_BatteryStatus.h"

/**
 * @class CDP_BatteryFactory
 * @brief The Battery Monitor Factory Class
 */
class CDP_BatteryFactory : public CDP_BatteryLogger {

public:
/**
 * @fn CDP_BatteryPackets * getPacketObj(CDP_BatteryPackets::CDP_BatteryPacketsType_t type)
 * @param type
 * @return CDP_BatteryPackets *
 * @brief Returns an object of the specialised packet type class
 */
    static CDP_BatteryPackets *getPacketObj(CDP_BatteryPackets::CDP_BatteryPacketsType_t type);
};

#endif //CODINGTEST_CDP_BATTERYFACTORY_H
