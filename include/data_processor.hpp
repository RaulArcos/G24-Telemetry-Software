#ifndef DATAPROCESSOR_HPP
#define DATAPROCESSOR_HPP

#include "common/common_libraries.hpp"
#include "common/g24_telemetry_data.hpp"
#include "mqtt_controller.hpp"

class DataProcessor {
public:
    DataProcessor() = default;
    char* process(std::vector<float> data);
    void set_mqtt_controller(MQTTController *mqtt_controller);

private:
    MQTTController *_mqtt_controller;
};

#endif