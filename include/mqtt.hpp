#ifndef MQTTCONTROLLER_HPP
#define MQTTCONTROLLER_HPP

#include "common/common_libraries.hpp"
#include <PubSubClient.h>
#include "gsm_7600.hpp"

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

class MQTT {
public:
    MQTT(TinyGsmClient *client);
    void connect();
    static void callback(char* topic, byte* payload, unsigned int length);
    void set_callback(std::function<void(char*, byte*, unsigned int)> func);
    void publish_telemetry(const char* topic, const char* message);
    void publish_status(const char* message);
    void publish_gps(const char* message);
    void publish_satellites(const char* message);
    void publish_test(const char* message);
    void publish_can_frame_0(const char* message);
    void publish_can_frame_1(const char* message);
    void publish_can_frame_2(const char* message);
    void publish(const char* topic, const char* message);
    PubSubClient* get_client();
    void set_modem_client(TinyGsmClient* client) { _modem_client = client; _client.setClient(*client); }
    void loop();
    void set_mutex(SemaphoreHandle_t mutex) { _mutex = mutex; }

    const char* test_topic = "G24/telemetry/test";
    const char* status_topic = "G24/telemetry/status";
    const char* gps_topic = "G24/telemetry/gps";
    const char* satellites_topic = "G24/telemetry/gps/satelites";
    const char* can_frame_0_topic = "G24/telemetry/can/frame_0";
    const char* can_frame_1_topic = "G24/telemetry/can/frame_1";
    const char* can_frame_2_topic = "G24/telemetry/can/frame_2";

private:
    const char* _mqtt_server = "broker.hivemq.com";
    const int _mqtt_port = 1883;
    TinyGsmClient* _modem_client;
    PubSubClient _client;
    SemaphoreHandle_t _mutex;
};

#endif