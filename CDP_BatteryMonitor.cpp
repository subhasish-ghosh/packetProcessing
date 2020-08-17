/**
 * @file CDP_BatteryMonitor.cpp
 * @brief Battery Monitor Application
 * @note Requires minimum c++17 to compile
 * @author Subhasish Ghosh
 */

#include "CDP_BatteryParser.h"

/**
 * @fn int main(int argc, char **argv)
 * @param argc
 * @param argv
 * @return int
 * @brief The main entry point function
 */
int main(int argc, char **argv) {
    // Create a generic logger class object
    CDP_BatteryLogger logger;

    if (argc < 2) {
        logger.cdp_err("Main: Invalid or no file provided");
        return -1;
    }

    // Run the parser
    try {
        CDP_BatteryParser::run(std::string(argv[1]));
    } catch (...) {
        logger.cdp_err("Main: Parser Failed to run");
        return -1;
    }

    return 0;
}