
#include "CDP_BatteryParser.h"

int main(int argc, char **argv) {
    CDP_BatteryLogger logger;

    if (argc < 2) {
        logger.cdp_err("Main: Invalid or no file provided");
        return -1;
    }

    try {
        CDP_BatteryParser::run(argv[1]);
    } catch (...) {
        logger.cdp_err("Main: Parser Failed to run");
        return -1;
    }

    return 0;
}