/**
 * @file CDP_BatteryPower.h
 * @brief Battery Power Class
 * @author Subhasish Ghosh
 */

#ifndef CODINGTEST_CDP_BATTERYPOWER_H
#define CODINGTEST_CDP_BATTERYPOWER_H

#include "CDP_BatteryLogger.h"
#include "CDP_BatteryPackets.h"

/**
 * @class CDP_BatteryPower
 * @brief The Singleton Battery Power Class
 */
class CDP_BatteryPower : public CDP_BatteryPackets {
public:

    /**
    * @fn cdp_dbg(Args &&... args)
    * @tparam Args
    * @param args
    * @brief Class specific override for cdp_dbg
    * @returns void
    */
    template<typename ...Args>
    void cdp_dbg(Args &&... args) {
        if (CDP_BatteryLogger::getLogLevel() >= CDP_BatteryLogger::CDP_LOGGER_LEVEL_DBG) {
            std::stringstream stream;
            (stream << ... << args);
            std::cout << "CDP_BatteryPower: " << stream.str() << '\n';
        }
    }

    /**
    * @fn cdp_info(Args &&... args)
    * @tparam Args
    * @param args
    * @brief Class specific override for cdp_info
    * @returns void
    */
    template<typename ...Args>
    void cdp_info(Args &&... args) {
        if (CDP_BatteryLogger::getLogLevel() >= CDP_BatteryLogger::CDP_LOGGER_LEVEL_INFO) {
            std::stringstream stream;
            (stream << ... << args);
            std::cout << "S;" << stream.str() << '\n';
        }
    }

    /**
     * @fn step(std::vector<uint8_t> &)
     * @brief This function is used to cycle the class state machine once
     * @param data packet to be processed
     * @returns void
     */
    void step(std::vector<uint8_t> &);

    /**
     * @fn CDP_BatteryPackets *getObj(CDP_BatteryPackets::CDP_BatteryPacketsType_t &type)
     * @brief This function is used to retrieve a Singleton object of the class
     * @param type is used to verify the correct packet type
     * @returns CDP_BatteryPackets *
     */
    static CDP_BatteryPackets *getObj(CDP_BatteryPackets::CDP_BatteryPacketsType_t &type);

    /**
     * @fn CDP_BatteryPacketsType_t get_type(void)
     * @brief This function is used to retrieve the packet type of the class
     * @param void
     * @returns CDP_BatteryPacketsType_t
     */
    CDP_BatteryPacketsType_t get_type(void);

    /**
     * @fn ssize_t get_dataLen(void)
     * @brief This function is used to retrieve the data pkt len of the class
     * @param void
     * @returns ssize_t
     */
    ssize_t get_dataLen(void);

    /**
     * @fn std::string get_name(void)
     * @brief This function is used to retrieve the data name of the class
     * @param void
     * @returns std::string
     */
    std::string get_name(void);

    /**
     * @fn bool get_error(void)
     * @brief This function is used to retrieve the error occurred in the class
     * @param void
     * @returns bool
     */
    bool get_error(void);

private:
    /**
     * @var type
     * @brief This variable is the packet type of the class
     */
    inline static const CDP_BatteryPacketsType_t type = CDP_BatteryPackets::CDP_BatteryPacketsType::CDP_PACKETSTYPE_BATTERYPOWER;
    /**
     * @var datalen
     * @brief This variable is the packet dataLen of the class
     */
    inline static const ssize_t datalen = 16;
    /**
     * @var name
     * @brief This variable is the packet string name of the class
     */
    inline static const std::string name = "Battery Power";
    /**
     * @var objInit
     * @brief This variable is used to check if the Singleton class is already initialised
     */
    inline static bool objInit = false;
    /**
     * @var stateErrorDetected
     * @brief This variable is used to check if the Singleton class is having any state machine errors
     */
    inline static bool stateErrorDetected = false;
    /**
     * @var cdpBatteryPower
     * @brief This variable is the Singleton Class Object
     */
    inline static CDP_BatteryPower *cdpBatteryPower = nullptr;
    /**
     * @struct CDP_PacketFormat_t
     * @brief This structure is to define the class data format
     */
    typedef PACK (
            struct {
                uint32_t time;
                uint32_t volt;
                uint64_t current;
            }) CDP_PacketFormat_t;
    /**
     * @var format
     * @brief The class data format variable
     */
    inline static CDP_PacketFormat_t *format = nullptr;
    /**
     * @var prevPowerStateDBounce
     * @brief This variable stores a previous <TimeStamp, State> pair to calculate signal debounce
     */
    inline static std::pair prevPowerStateDBounce = std::make_pair<uint32_t, uint32_t>(0, 0);
    /**
     * @var prevPowerStateCommit
     * @brief This variable stores a previous <TimeStamp, State> pair accepted after signal debounce
     */
    inline static std::pair prevPowerStateCommit = std::make_pair<uint32_t, uint32_t>(0, 0);
    /**
     * @var currPowerStateCommit
     * @brief This variable stores a current <TimeStamp, State> pair accepted after signal debounce
     */
    inline static std::pair currPowerStateCommit = std::make_pair<uint32_t, uint32_t>(0, 0);
    /**
     * @var mwattStateTable
     * @brief This variable stores power state ranges as <MinPower, MaxPower> pairs
     */
    inline static std::array mwattStateTable = {std::make_pair<uint64_t, uint64_t>(0, 200),
                                                std::make_pair<uint64_t, uint64_t>(300, 450),
                                                std::make_pair<uint64_t, uint64_t>(550, 650),
                                                std::make_pair<uint64_t, uint64_t>(800, 1200)};
    /**
     * @var stateTable
     * @brief This variable stores power state transitions ranges as <FromState, ToState, Name> tuples
     */
    inline static std::array stateTable = {std::make_tuple<uint32_t, uint32_t>(0, 1, "Starting"),
                                           std::make_tuple<uint32_t, uint32_t>(1, 2, "Warm up"),
                                           std::make_tuple<uint32_t, uint32_t>(2, 3, "Main Session"),
                                           std::make_tuple<uint32_t, uint32_t>(3, 2, "Cool down"),
                                           std::make_tuple<uint32_t, uint32_t>(2, 0, "Complete")};

    CDP_BatteryPower();

    CDP_BatteryPower(const CDP_BatteryPower &);

    CDP_BatteryPower &operator=(const CDP_BatteryPower &);
};

/**
 * @def CDP_BATTERYPOWER_DEBOUNCE_MS
 * @brief Macro defining the debounce signal timing in milli-seconds
 */
#define CDP_BATTERYPOWER_DEBOUNCE_MS    10

#endif //CODINGTEST_CDP_BATTERYPOWER_H
