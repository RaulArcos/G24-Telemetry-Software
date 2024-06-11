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
    void test(int i, int j);
    void send_gps_data(float lat, float lng, float speed);
    void send_satellites_data(int satellites);

private:
    MQTTController *_mqtt_controller;
    PubSubClient * _mqttClient;
};

#endif