#ifndef DATAPROCESSOR_HPP
#define DATAPROCESSOR_HPP

#include "common/common_libraries.hpp"
#include "common/g24_telemetry_data.hpp"
#include "common/topics.hpp"
#include "mqtt.hpp"

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

class DataProcessor {
public:
    DataProcessor() = default;
    char* process(std::vector<float> data);
    void set_mqtt_controller(MQTT *mqtt);
    void test(int i, int j);
    void send_gps_data(float lat, float lng, float speed);
    void send_satellites_data(int satellites);
    void send_frame_0(int rpmh, int rpml, int tpsh, int tpsl, int brkh, int brkl, int gear);
    void send_frame_1(int lfws, int rfws, int lrws, int rrws, int maph, int mapl, int ect);
    void send_frame_2(int lambh, int lambl, int lamth, int lamtl, int bvolth, int bvoltl, int iat);
    void set_mutex(SemaphoreHandle_t mutex) { _mutex = mutex; }
    void send_data(const char* topic, StaticJsonDocument<200>& doc);


private:
    MQTT *_mqtt_controller;
    PubSubClient * _mqttClient;
    SemaphoreHandle_t _mutex;
};

#endif