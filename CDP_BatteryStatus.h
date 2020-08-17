/**
 * @file CDP_BatteryStatus.h
 * @brief Battery Status Class
 * @author Subhasish Ghosh
 */
#ifndef CODINGTEST_CDP_BATTERYSTATUS_H
#define CODINGTEST_CDP_BATTERYSTATUS_H


#include "CDP_BatteryLogger.h"
#include "CDP_BatteryPackets.h"

/**
 * @class CDP_BatteryStatus
 * @brief The Singleton Battery Status Class
 */
class CDP_BatteryStatus : public CDP_BatteryPackets {
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
        if (CDP_BatteryLogger::getLogLevel() >= CDP_LOGGER_LEVEL_DBG) {
            std::stringstream stream;
            (stream << ... << args);
            std::cout << "CDP_BatteryStatus: " << stream.str() << '\n';
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
        if (CDP_BatteryLogger::getLogLevel() >= CDP_LOGGER_LEVEL_INFO) {
            std::stringstream stream;
            (stream << ... << args);
            std::cout << "B;" << stream.str() << '\n';
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
    inline static const CDP_BatteryPacketsType_t type = CDP_BatteryPackets::CDP_BatteryPacketsType::CDP_PACKETSTYPE_BATTERYSTATUS;
    /**
     * @var datalen
     * @brief This variable is the packet dataLen of the class
     */
    inline static const ssize_t datalen = 5;
    /**
     * @var name
     * @brief This variable is the packet string name of the class
     */
    inline static const std::string name = "Battery Status";
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
     * @var cdpBatteryStatus
     * @brief This variable is the Singleton Class Object
     */
    inline static CDP_BatteryStatus *cdpBatteryStatus = nullptr;
    /**
     * @struct CDP_PacketFormat_t
     * @brief This structure is to define the class data format
     */
    typedef PACK (struct {
                      uint32_t time;
                      uint8_t battStatus;
                  }) CDP_PacketFormat_t;
    /**
     * @var format
     * @brief The class data format variable
     */
    inline static CDP_PacketFormat_t *format = nullptr;
    /**
     * @var strbattStatus
     * @brief The class data state variable
     */
    inline static const std::array strbattStatus = {"VLOW",
                                                    "LOW",
                                                    "MED",
                                                    "HIGH"};

    CDP_BatteryStatus();

    CDP_BatteryStatus(const CDP_BatteryStatus &);

    CDP_BatteryStatus &operator=(const CDP_BatteryStatus &);
};


#endif //CODINGTEST_CDP_BATTERYSTATUS_H
