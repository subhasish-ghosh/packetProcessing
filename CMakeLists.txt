cmake_minimum_required(VERSION 3.16)
project(CodingTest)

set(CMAKE_CXX_STANDARD 17)

add_executable(CodingTest CDP_BatteryMonitor.cpp CDP_Platform.h CDP_BatteryParser.cpp CDP_BatteryParser.h CDP_BatteryLogger.cpp CDP_BatteryLogger.h CDP_BatteryStatus.cpp CDP_BatteryStatus.h CDP_BatteryPower.cpp CDP_BatteryPower.h CDP_BatteryPackets.h CDP_BatteryFactory.cpp CDP_BatteryFactory.h CDP_BatteryPackets.cpp)