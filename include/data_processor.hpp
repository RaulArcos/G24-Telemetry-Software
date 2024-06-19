#ifndef DATAPROCESSOR_HPP
#define DATAPROCESSOR_HPP

#include "common/common_libraries.hpp"
#include "common/g24_telemetry_data.hpp"
#include "mqtt_controller.hpp"

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

class DataProcessor {
public:
    DataProcessor() = default;
    char* process(std::vector<float> data);
    void set_mqtt_controller(MQTTController *mqtt_controller);
    void test(int i, int j);
    void send_gps_data(float lat, float lng, float speed);
    void send_satellites_data(int satellites);
    void send_frame1(int rpmHigh, int rpmLow, int tpsHigh, int tpsLow, int maphigh, int maplow, int d4);
    void send_frame2(int d1, int d2, int d3, int lambdatargethigh, int lambdatargetlow, int lambdahigh, int lambdalow);

private:
    MQTTController *_mqtt_controller;
    PubSubClient * _mqttClient;
    SemaphoreHandle_t _mqtt_mutex = xSemaphoreCreateMutex();
};

#endif