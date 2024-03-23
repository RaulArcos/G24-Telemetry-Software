#ifndef G24_TELEMETRY_DATA_HPP
#define G24_TELEMETRY_DATA_HPP

/**
 * @file g24_telemetry_data.hpp
 * @brief This file contains the definition of the G24TelemetryData struct.
*/

struct G24TelemetryData{
    unsigned int RPM = 0;
    double TPS = 0;
    double MAP = 0;
    double IAT = 0;
    double BAT = 0;
    double ECT = 0;
};
#endif